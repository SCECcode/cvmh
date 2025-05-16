# GNU Automake config

lib_LIBRARIES = libvxapi.a libcvmh.a
bin_PROGRAMS = vx vx_lite vx_slice run_vx.sh run_vx_lite.sh
include_HEADERS = vx_sub.h cvmh.h

# Optional cvmdst program
if VX_ENABLE_GTS
bin_PROGRAMS += cvmdst
endif

# General compiler/linker flags
AM_CFLAGS = ${CFLAGS} -Wall -O3 -std=c99 -D_LARGEFILE_SOURCE \
	-D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -fPIC
AM_LDFLAGS = ${LDFLAGS} -L../gctpc/source -lgctpc -lm

# Dist sources
libcvmh_a_SOURCES = vx_sub.c vx_io.c cvmh.c
vx_lite_cvmh_SOURCES = vx_lite_cvmh.c
vx_cvmh_SOURCES = cvmh.c vx_cvmh.c

libvxapi_a_SOURCES = vx_sub.c scec1d.c vs30_gtl.c vx_io.c utils.c 
vx_SOURCES = vx.c
vx_slice_SOURCES = vx_slice.c
vx_lite_SOURCES = vx_lite.c
run_vx_sh_SOURCES = run_vx.sh
run_vx_lite_sh_SOURCES = run_vx_lite.sh

if VX_ENABLE_GTS
cvmdst_SOURCES = cvm_dst.c
endif

all: $(bin_PROGRAMS) $(lib_LIBRARIES) libcvmh.so libvxapi.so


############################################
# Executables
############################################

libcvmh.a: vx_sub.o vx_io.o utils.o cvmh_static.o vx_sub.o scec1d.o vs30_gtl.o vx_io.o utils.o
	$(AR) rcs $@ $^

libcvmh.so: vx_sub.o vx_io.o utils.o cvmh.o vx_sub.o scec1d.o vs30_gtl.o vx_io.o utils.o
	$(CC) -shared -o libcvmh.so $^ $(AM_LDFLAGS)

vx$(EXEEXT): vx.o
	$(CC) -o $@ $^ $(AM_LDFLAGS)

vx_lite$(EXEEXT): vx_lite.o libvxapi.so
	$(CC) -o $@ $^ $(AM_LDFLAGS)

vx_slice$(EXEEXT): vx_slice.o libvxapi.so
	$(CC) -o $@ $^ $(AM_LDFLAGS)

cvmdst$(EXEEXT): cvm_dst.o
	$(CC) -o $@ $^ $(AM_LDFLAGS)

cvmh_static.o: cvmh.c
	$(CC) -o $@ -c $^ $(AM_CFLAGS)

libvxapi.a: vx_sub.o vx_io.o utils.o 
	$(AR) rcs $@ $^

libvxapi.so: vx_sub.o scec1d.o vs30_gtl.o vx_io.o utils.o 
	$(CC) -shared -o libvxapi.so $^ $(AM_LDFLAGS)


cvmh.o: cvmh.c
	$(CC) -fPIC -DDYNAMIC_LIBRARY -o $@ -c $^ $(AM_CFLAGS)

install:
	mkdir -p ${prefix}
	mkdir -p ${prefix}/lib
	mkdir -p ${prefix}/include
	mkdir -p ${prefix}/bin
	cp libcvmh.so ${prefix}/lib
	cp libcvmh.a ${prefix}/lib
	cp libvxapi.so ${prefix}/lib
	cp libvxapi.a ${prefix}/lib
	cp cvmh.h ${prefix}/include
	cp vx_lite ${prefix}/bin
	cp vx ${prefix}/bin

clean:
	rm -f *~ *.a *.o vx$(EXEEXT) vx_lite$(EXEEXT) \
	vx_slice$(EXEEXT) cvmdst$(EXEEXT)

