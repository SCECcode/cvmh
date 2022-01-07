dnl GNU Autoconf config

AC_PREREQ(2.59)
AC_INIT([cvmh], [11.9.0], [software@scec.org])
AC_CONFIG_AUX_DIR([./aux-config])
AM_INIT_AUTOMAKE(foreign tar-pax)

dnl
dnl Command line options
dnl

AC_ARG_WITH([gts],
        [AS_HELP_STRING([--with-gts],
        [build GTS based targets like cvmdst])],
        [with_gts=yes],
        [with_gts=no])
if test "$with_gts" = yes; then
   # Get GTS library and include locations
   AC_ARG_WITH([gts-incdir],
   [AS_HELP_STRING([--with-gts-incdir],
	 [directory containing the GTS header files])],
	 [with_gts_incdir="$withval"],
	 [with_gts_incdir=no])
   AC_SUBST(with_gts_incdir)
   AC_ARG_WITH([gts-libdir],
   [AS_HELP_STRING([--with-gts-libdir], [directory containing the GTS libraries])],
   [with_gts_libdir="$withval"],
   [with_gts_libdir=no])
   AC_SUBST(with_gts_libdir)
fi

dnl
dnl Command line tools
dnl

AC_PROG_CC
AC_PROG_LIBTOOL
AC_PROG_INSTALL
AC_PROG_MKDIR_P

dnl CURL (used to download model files)
AC_PATH_PROG(CURL, curl)
if test -z "$CURL" ; then
  AC_MSG_FAILURE([cannot find 'curl' program.])
  TAR=`echo "Error: curl is not installed." ; false`
fi


dnl
dnl Verify configuration
dnl
if test "$with_gts" = yes; then
  AC_PATH_PROG(PKGCONFIG, pkg-config)
  if test -z "$PKGCONFIG" ; then
    AC_MSG_FAILURE([cannot find 'pkg-config' program.])
    PKGCONFIG=`echo "Error: pkg-config is not installed." ; false`
  fi

  if test "$with_gts_incdir" != no ; then
    GTS_INCLUDES="-I$with_gts_incdir `$PKGCONFIG --cflags glib-2.0`"
  fi
  if test"$with_gts_libdir" != no ; then
    GTS_LDFLAGS="-L$with_gts_libdir -lgts `$PKGCONFIG --libs glib-2.0`"
  fi

   AC_CHECK_HEADER(gts.h, [], [AC_MSG_ERROR(["GTS header not found; use --with-gts-incdir"])], [AC_INCLUDES_DEFAULT])
   AC_CHECK_LIB(gts, gts_file_read,[AM_CONDITIONAL(VX_ENABLE_GTS, true)], [AC_MSG_ERROR(["GTS library not found; use --with-gts-libdir"])], [-lm])
  AC_SUBST(GTS_INCLUDES)
  AC_SUBST(GTS_LDFLAGS)
else
   AM_CONDITIONAL(VX_ENABLE_GTS, false)
fi

AC_CONFIG_FILES([
	Makefile
	gctpc/Makefile
	gctpc/source/Makefile
	src/Makefile
	doc/Makefile
	scripts/Makefile
	model/Makefile
	test/Makefile
	test/inputs/Makefile
	test/ref/Makefile
	])



AC_OUTPUT


dnl End of file
