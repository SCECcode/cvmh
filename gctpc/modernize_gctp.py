from __future__ import annotations
#!/usr/bin/env python3
"""
Fast, linear-time (zero regex backtracking) K&R C to ANSI C23 converter
for fresh/original USGS GCTP / SCEC CVM-H source trees.
Modifies .c and .h files directly in place (no backup directory created or read).

python3 modernize_gctp.py .

convert the original cvmh/gctpc/source/* code to newer gcc/gfortran

"""

import glob
import os
import re
import sys

TYPE_KEYWORDS = (
    "const", "unsigned", "signed", "struct",
    "long", "short", "int", "double", "float", "char", "void",
)

HEADER_RE = re.compile(
    r"^(?P<indent>[ \t]*)"
    r"(?P<ret>(?:static\s+|extern\s+)?(?:unsigned\s+|signed\s+|long\s+|short\s+|int\s+|double\s+|float\s+|char\s+|void\s+)+)"
    r"(?P<name>[a-zA-Z_][a-zA-Z0-9_]*)\s*"
    r"\((?P<args>[^()]*)\)\s*(?P<tail>.*)$"
)


def parse_kr_declarations(decl_block: str) -> dict[str, tuple[str, str]]:
    """Parses K&R parameter declarations between `)` and `{`, handling multi-line comments."""
    param_info: dict[str, tuple[str, str]] = {}

    def strip_multiline_comment(m: re.Match) -> str:
        txt = m.group(0)
        return "\n" * txt.count("\n") if "\n" in txt else txt

    cleaned_block = re.sub(r"/\*.*?\*/", strip_multiline_comment, decl_block, flags=re.DOTALL)

    for raw_line in cleaned_block.splitlines():
        line = raw_line.strip()
        if not line:
            continue

        comment = ""
        c_idx = line.find("/*")
        if c_idx != -1:
            comment = line[c_idx:].strip()
            stmt_part = line[:c_idx].strip()
        else:
            stmt_part = line

        for stmt in stmt_part.split(";"):
            stmt = stmt.strip()
            if not stmt:
                continue

            # Function pointer array parameter e.g. `long (*for_trans[])()`
            fptr_match = re.match(
                r"^((?:const\s+|unsigned\s+|signed\s+|long\s+|short\s+|int\s+|double\s+|float\s+|char\s+|void\s+)+)"
                r"\(\s*\*\s*([a-zA-Z_][a-zA-Z0-9_]*)\s*(\[[^\]]*\])\s*\)\s*\(\s*\)$",
                stmt,
            )
            if fptr_match:
                ret_t = " ".join(fptr_match.group(1).split())
                var_name = fptr_match.group(2)
                brackets = fptr_match.group(3)
                param_info[var_name] = (
                    f"{ret_t} (*{var_name}{brackets})(double, double, double *, double *)",
                    comment,
                )
                continue

            parts = [p.strip() for p in stmt.split(",") if p.strip()]
            if not parts:
                continue

            match = re.match(
                r"^((?:const\s+|unsigned\s+|signed\s+|struct\s+\w+\s+|long\s+|short\s+|int\s+|double\s+|float\s+|char\s+|void\s+)+)(.+)$",
                parts[0],
            )
            if not match:
                continue

            base_type = " ".join(match.group(1).split())
            declarators = [match.group(2).strip()] + parts[1:]

            for decl in declarators:
                id_match = re.search(
                    r"([a-zA-Z_][a-zA-Z0-9_]*)(?:\s*\[[^\]]*\])?\s*$", decl
                )
                if id_match:
                    param_info[id_match.group(1)] = (f"{base_type} {decl}", comment)

    return param_info


def convert_kr_functions(code: str) -> tuple[str, int, dict[str, str], dict[str, str]]:
    """Line-by-line state-machine converter (O(N), zero backtracking)."""
    lines = code.splitlines(keepends=True)
    out_lines: list[str] = []
    i = 0
    n = len(lines)
    count = 0
    local_sigs: dict[str, str] = {}
    global_sigs: dict[str, str] = {}

    while i < n:
        line = lines[i]
        stripped = line.lstrip()

        first_word = stripped.split(None, 1)[0] if stripped else ""
        if first_word not in ("static", "extern") + TYPE_KEYWORDS:
            out_lines.append(line)
            i += 1
            continue

        # Gather up to 5 lines if the function signature wraps (like `gctp(...)`)
        sig_chunk = line
        end_sig_idx = i
        if "(" in line and ")" not in line:
            while end_sig_idx + 1 < min(n, i + 5):
                end_sig_idx += 1
                sig_chunk += lines[end_sig_idx]
                if ")" in lines[end_sig_idx]:
                    break

        m = HEADER_RE.match(sig_chunk.rstrip("\r\n"))
        if not m:
            out_lines.append(line)
            i += 1
            continue

        indent = m.group("indent")
        ret_type = " ".join(m.group("ret").split())
        func_name = m.group("name")
        raw_args = m.group("args").strip()
        tail = m.group("tail").strip()
        is_static = ret_type.startswith("static ")

        if not raw_args or tail.startswith(";") or tail.startswith("{"):
            out_lines.append(line)
            i += 1
            continue

        arg_names = [a.strip() for a in raw_args.split(",") if a.strip()]
        if any(not re.match(r"^[a-zA-Z_][a-zA-Z0-9_]*$", a) for a in arg_names):
            out_lines.append(line)
            i += 1
            continue

        # Case A: Same-line K&R definition
        if tail:
            brace_pos = tail.find("{")
            if brace_pos != -1:
                decl_text = tail[:brace_pos].strip()
                rest_after_brace = tail[brace_pos:]
                info_map = parse_kr_declarations(decl_text)
                if any(a in info_map for a in arg_names):
                    compact = [info_map[a][0] if a in info_map else f"int {a}" for a in arg_names]
                    sig = f"{ret_type} {func_name}({', '.join(compact)});"
                    local_sigs[func_name] = sig
                    if not is_static:
                        global_sigs[func_name] = sig
                    count += 1
                    out_lines.append(f"{indent}{ret_type} {func_name}({', '.join(compact)}) {rest_after_brace}\n")
                    i = end_sig_idx + 1
                    continue
            elif tail.endswith(";") and end_sig_idx + 1 < n and lines[end_sig_idx + 1].lstrip().startswith("{"):
                info_map = parse_kr_declarations(tail)
                if any(a in info_map for a in arg_names):
                    compact = [info_map[a][0] if a in info_map else f"int {a}" for a in arg_names]
                    sig = f"{ret_type} {func_name}({', '.join(compact)});"
                    local_sigs[func_name] = sig
                    if not is_static:
                        global_sigs[func_name] = sig
                    count += 1
                    out_lines.append(f"{indent}{ret_type} {func_name}({', '.join(compact)})\n")
                    i = end_sig_idx + 1
                    continue

        # Case B: Multi-line K&R declaration block between `)` and `{`
        j = end_sig_idx + 1
        decl_lines: list[str] = []
        found_brace = False
        while j < min(n, end_sig_idx + 80):
            s = lines[j].strip()
            if s.startswith("{"):
                found_brace = True
                break
            decl_lines.append(lines[j])
            j += 1

        if found_brace and decl_lines:
            info_map = parse_kr_declarations("".join(decl_lines))
            if any(a in info_map for a in arg_names):
                param_lines = []
                compact = []
                for idx, arg in enumerate(arg_names):
                    comma = "" if idx == len(arg_names) - 1 else ","
                    full_decl, comment = info_map.get(arg, (f"int {arg}", ""))
                    compact.append(full_decl)
                    decl_comma = f"{full_decl}{comma}"
                    if comment:
                        param_lines.append(f"{decl_comma:<32s}{comment}")
                    else:
                        param_lines.append(decl_comma)

                sig = f"{ret_type} {func_name}({', '.join(compact)});"
                local_sigs[func_name] = sig
                if not is_static:
                    global_sigs[func_name] = sig
                count += 1

                if len(arg_names) <= 2 and not any(info_map.get(a, ("", ""))[1] for a in arg_names):
                    out_lines.append(f"{indent}{ret_type} {func_name}({', '.join(compact)})\n")
                else:
                    joined = "\n".join(param_lines)
                    out_lines.append(f"{indent}{ret_type} {func_name}(\n{joined})\n")
                i = j
                continue

        out_lines.append(line)
        i += 1

    return "".join(out_lines), count, local_sigs, global_sigs


def upgrade_kr_forward_decls(
    code: str, local_sigs: dict[str, str], all_global_sigs: dict[str, str]
) -> tuple[str, int]:
    fwd_pattern = re.compile(
        r"^([ \t]*(?:static\s+|extern\s+)?"
        r"(?:unsigned\s+|signed\s+|long\s+|short\s+|int\s+|double\s+|float\s+|char\s+|void\s+)+"
        r"(?P<rest>\*?\s*[a-zA-Z_][a-zA-Z0-9_]*\s*\(\s*\)"
        r"(?:\s*,\s*\*?\s*[a-zA-Z_][a-zA-Z0-9_]*\s*\(\s*\))*)\s*;)",
        re.MULTILINE,
    )
    count = 0

    def replacer(match: re.Match) -> str:
        nonlocal count
        names = re.findall(r"([a-zA-Z_][a-zA-Z0-9_]*)\s*\(\s*\)", match.group("rest"))
        upgraded = []
        for name in names:
            if name in local_sigs:
                upgraded.append(local_sigs[name])
            elif name in all_global_sigs:
                upgraded.append(all_global_sigs[name])
            else:
                upgraded.append(f"/* UNKNOWN_KR_DECL: {name}() */")
        count += 1
        return "\n".join(upgraded)

    return fwd_pattern.sub(replacer, code), count


def fix_gctp_function_pointers(code: str) -> tuple[str, int]:
    fptr_pattern = re.compile(
        r"\b(long\s*\(\s*\*\s*(?:inv_trans|for_trans)\s*\[[^\]]*\]\s*\))\s*\(\s*\)"
    )
    return fptr_pattern.subn(r"\1(double, double, double *, double *)", code)


def fix_br_gctp_fortran_abi(filename: str, code: str) -> tuple[str, bool]:
    if os.path.basename(filename).lower() != "br_gctp.c":
        return code, False
    updated = code
    changed = False
    if "<stddef.h>" not in updated:
        updated = "#include <stddef.h>\n" + updated
        changed = True
    new_updated = re.sub(r"\b(?:int|long)\s+(fn27_len|fn83_len|len1|len2)\b", r"size_t \1", updated)
    if new_updated != updated:
        updated = new_updated
        changed = True
    return updated, changed


def main() -> None:
    target_dir = sys.argv[1] if len(sys.argv) > 1 else "."
    c_files = sorted(glob.glob(os.path.join(target_dir, "*.c")))
    h_files = sorted(glob.glob(os.path.join(target_dir, "*.h")))
    all_files = c_files + h_files

    if not all_files:
        print(f"No .c or .h files found in {os.path.abspath(target_dir)}")
        sys.exit(1)

    # Pass 1: Read original source files directly and convert K&R definitions
    staged: dict[str, tuple[str, str, int, dict[str, str]]] = {}
    all_global_sigs: dict[str, str] = {}

    for filepath in all_files:
        with open(filepath, "r", encoding="latin1") as f:
            original = f.read()
        if filepath.lower().endswith(".c"):
            converted, n_funcs, local_sigs, global_sigs = convert_kr_functions(original)
            all_global_sigs.update(global_sigs)
            staged[filepath] = (original, converted, n_funcs, local_sigs)
        else:
            staged[filepath] = (original, original, 0, {})

    # Pass 2: Upgrade forward declarations, fix function pointers, and write in-place
    total_funcs = total_decls = total_fptrs = modified_files = 0
    for filepath in all_files:
        original, code, n_funcs, local_sigs = staged[filepath]
        if not filepath.lower().endswith(".h"):
            code, n_decls = upgrade_kr_forward_decls(code, local_sigs, all_global_sigs)
        else:
            n_decls = 0
        code, n_fptrs = fix_gctp_function_pointers(code)
        code, abi_fixed = fix_br_gctp_fortran_abi(filepath, code)

        if code != original:
            with open(filepath, "w", encoding="latin1") as f:
                f.write(code)
            modified_files += 1
            total_funcs += n_funcs
            total_decls += n_decls
            total_fptrs += n_fptrs
            abi_note = " [+Fortran size_t ABI]" if abi_fixed else ""
            fptr_note = f" | fptrs: {n_fptrs}" if n_fptrs else ""
            print(
                f"Updated {os.path.basename(filepath):15s} | "
                f"K&R defs: {n_funcs:2d} | K&R decls: {n_decls:2d}{fptr_note}{abi_note}"
            )

    print("-" * 72)
    print(f"Done! Modified {modified_files}/{len(all_files)} files (.c and .h).")
    print(f"Total K&R function definitions converted : {total_funcs}")
    print(f"Total K&R forward declarations upgraded  : {total_decls}")
    print(f"Total function pointer arrays updated    : {total_fptrs}")


if __name__ == "__main__":
    main()

