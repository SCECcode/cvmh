# GNU Automake config

SUBDIRS = \
	inputs \
	ref

TESTS = unittest accepttest

check_PROGRAMS = unittest accepttest

unittest_SOURCES = \
	unittest.c \
	unittest_defs.c \
	test_helper.c \
	test_vx_sub.c \
	test_vx_exec.c \
	test_vx_lite_exec.c
unittest_LDADD = $(top_builddir)/src/libvxapi.la $(top_builddir)/gctpc/source/libgctpc.la

accepttest_SOURCES = \
	accepttest.c \
	unittest_defs.c \
	test_helper.c \
	test_grid.c
accepttest_LDADD = $(top_builddir)/src/libvxapi.la $(top_builddir)/gctpc/source/libgctpc.la

noinst_HEADERS = \
	test_grid.h \
	test_helper.h \
	test_vx_exec.h \
	test_vx_lite_exec.h \
	test_vx_sub.h \
	unittest_defs.h

# General compiler/linker flags
AM_CFLAGS = -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -DBIN_DIR=\"$(prefix)/bin\" -DMODEL_DIR=\"$(datadir)/model/cvmh\"
AM_CPPFLAGS =-I$(top_srcdir)/src

# Test output files
noinst_TMP = \
	test-8-point-vx-extract-elev.out \
	test-8-point-vx-lite-extract-depth.out \
	test-8-point-vx-lite-extract-elev.out \
	test-8-point-vx-lite-extract-scec.out

clean-data:
	$(RM) $(RM_FLAGS) $(noinst_TMP)
clean-local: clean-data


# End of file
