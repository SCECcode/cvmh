# GNU Automake config

# General compiler flags
AM_CFLAGS = -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64

bin_PROGRAMS = vx vx_lite vx_slice

pkginclude_HEADERS = \
	coor_para.h \
	cproj.h \
	params.h \
	proj.h \
	scec1d.h \
	utils.h \
	voxet.h \
	vs30_gtl.h \
	vx_io.h \
	vx_sub.h

lib_LTLIBRARIES = libvxapi.la

libvxapi_la_SOURCES = \
	vx_sub.c \
	scec1d.c \
	vs30_gtl.c \
	vx_io.c \
	utils.c

libvxapi_la_LIBADD = $(abs_top_builddir)/gctpc/source/libgctpc.la

vx_SOURCES = vx.c
vx_LDADD = libvxapi.la $(abs_top_builddir)/gctpc/source/libgctpc.la

vx_lite_SOURCES = vx_lite.c
vx_lite_LDADD = libvxapi.la $(abs_top_builddir)/gctpc/source/libgctpc.la

vx_slice_SOURCES = vx_slice.c
vx_slice_LDADD = libvxapi.la $(abs_top_builddir)/gctpc/source/libgctpc.la

# Optional cvmdst program
if VX_ENABLE_GTS
bin_PROGRAMS += cvmdst
cvmdst_SOURCES = cvm_dst.c
cvmdst_LDADD = $(abs_top_builddir)/gctpc/source/libgctpc.la
cvmdst_LDFLAGS = $(GTS_LDFLAGS)
endif


# End of file
