# GNU Automake config

dist_noinst_DATA = \
	test-8-point-vx-extract-depth.ref \
	test-8-point-vx-extract-elev.ref \
	test-8-point-vx-extract-scec.ref \
	test-extract-vxlite-depth.ref \
	test-extract-vxlite-offset.ref \
	test-extract-vxlite.ref \
	test-extract.ref


# 'export' the reference files by performing a mock install
export_datadir = $(top_builddir)/test/ref
export-data: $(dist_noinst_DATA)
	if [ "X$(top_srcdir)" != "X$(top_builddir)" ]; then for f in $(dist_noinst_DATA); do $(install_sh_DATA) $(srcdir)/$$f $(export_datadir); done; fi

clean-data:
	if [ "X$(top_srcdir)" != "X$(top_builddir)" ]; then for f in $(dist_noinst_DATA) $(noinst_TMP); do $(RM) $(RM_FLAGS) $(export_datadir)/$$f; done; fi

BUILT_SOURCES = export-data
clean-local: clean-data
