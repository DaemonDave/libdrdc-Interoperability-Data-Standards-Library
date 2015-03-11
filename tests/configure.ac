# $Id: configure.ac,v 1.16 2008/12/02 21:28:54 cvsuser Exp $
# configure.ac


AC_PREREQ(2.6)
AC_INIT([libdrdc], [[0.2-0]], [david.erickson@drdc-rddc.gc.ca])

# determine system type by conventional m4 macro
AC_CANONICAL_TARGET

# Get the date timestamp for library / documentation version control
DATE=$(date)
AC_SUBST(DATE)

AC_CONFIG_MACRO_DIR([m4])

# Library Version Master Version DO NOT TOUCH
MAJORVERSION=0
MINORVERSION=2
REVISION=0
VER='${MAJORVERSION}:${MINORVERSION}:${REVISION}'
#


# Test for target type or accept default = build || target
AC_MSG_CHECKING([Target OS type])
if test -z "$DRDC_PREFIX" ; then
  #AC_MSG_WARN([ DRDC_PREFIX was not specified])
	DRDC_PREFIX=$host_triplet
fi

# determine target operating system for library compilation
# carried out by drdc-target-prefix.m4 file in aclocal
TARGET_PREFIX

AM_INIT_AUTOMAKE([-Wall -Werror foreign])


AC_SUBST(MAJORVERSION)
AC_SUBST(MINORVERSION)
AC_SUBST(REVISION)


REL_VER=${REVISION}
LIB_VER=${MAJORVERSION}.${MINORVERSION}-${REVISION}
#          |               |                 |
#   +------+               |                 +----+
#   |                      |                      |
#  current    :         revision     :  		  		age
#   |                      |                      |
#   |                      |                      +- increment if interfaces have been added
#   |                      |                         set to zero if interfaces have been removed
#   |                      |                         or changed
#   |                      +- increment if source code has changed
#   |                         set to zero if current is incremented
#   +- increment if interfaces have been added, removed or changed
AC_SUBST(LIB_VER)
AC_SUBST(REL_VER)


# assign library prefix based on output
#
DRDC_PREFIX=libdrdc


AC_ARG_ENABLE(
[tests],
[AC_HELP_STRING([--enable-tests],[enable tests (default:false)])],
[case "${enableval}" in
      yes) enable_tests=true ;;
      no)  enable_tests=false ;;
      *) AC_MSG_ERROR([bad value ${enableval} for --enable-tests]) ;;
esac],
[enable_tests=false]
)

AM_CONDITIONAL([TESTS], [test x$enable_tests = xtrue])
AM_PROG_AR
AC_ARG_ENABLE(
[f2cblas],
[AC_HELP_STRING([--enable-f2cblas],[enable f2cblas (default:false)])],
[case "${enableval}" in
      yes) enable_f2cblas=true ;;
      no)  enable_f2cblas=false ;;
      *) AC_MSG_ERROR([bad value ${enableval} for --enable-f2cblas]) ;;
esac],
[enable_f2cblas=false]
)

AM_CONDITIONAL([F2CBLAS], [test x$enable_f2cblas = xtrue])

AC_ARG_ENABLE(
[extras],
[AC_HELP_STRING([--enable-extras],[enable extra functions (default:false)])],
[case "${enableval}" in
      yes) enable_extras=true ;;
      no)  enable_extras=false ;;
      *) AC_MSG_ERROR([bad value ${enableval} for --enable-extras]) ;;
esac],
[enable_extras=false]
)

AM_CONDITIONAL([EXTRAS], [test x$enable_extras = xtrue])

#AC_ARG_ENABLE(
#[cppwrapper],
#[AC_HELP_STRING([--enable-cppwrapper],[enable cppwrapper (default:false)])],
#[case "${enableval}" in
#      yes) enable_cppwrapper=true ;;
#      no)  enable_cppwrapper=false ;;
#      *) AC_MSG_ERROR([bad value ${enableval} for --enable-cppwrapper]) ;;
#esac],
#[enable_cppwrapper=false]
#)
#AM_CONDITIONAL([CPPWRAPPER], [test x$enable_cppwrapper = xtrue])

AC_PROG_CC_STDC
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LIBTOOL
AM_PROG_CC_C_O



case "${BUILD_TYPE}" in
     rtems)
       DRDC_PREFIX=${DRDC_PREFIX}/${target_alias}
       CC=${target_alias}-gcc
       AR=${target_alias}-ar
       AS=${target_alias}-as
       NM=${target_alias}-nm
       LD=${target_alias}-ld
       CXX=${target_alias}-g++
       OBJCOPY=${target_alias}-objcopy
       RANLIB=${target_alias}-ranlib
       export CC
       export AR
       export AS 
       export NM
       export LD
       export CXX
       export OBJCOPY
       export RANLIB          
       ;;
     gnu)
       DRDC_PREFIX=${DRDC_PREFIX}/${target_cpu}-gnu
       # Checks for programs.
       ;;
esac

#now set include directory name

libdir=$libdir/$DRDC_PREFIX
includedir=$includedir/$DRDC_PREFIX

# check for standard C headers
AC_CHECK_HEADER([math.h])
AC_CHECK_HEADER([stdio.h])
AC_CHECK_HEADER([stdlib.h])
AC_CHECK_HEADER([assert.h])

# check for kernel headers
AC_CHECK_HEADER([setjmp.h])

# configure to use ATLAS library and make all checks within.
# check for ATLAS availability of headers and functions here as a series of checks
AC_ARG_WITH([atlas], 
[AS_HELP_STRING([--with-atlas],
              [supports ATLAS Linear Algebra Suite vector and matrix multiplication])],
              [AC_CHECK_HEADER([atlas_buildinfo.h]) \
               AC_CHECK_HEADER([atlas_pthreads.h])  \
               AC_CHECK_HEADER([atlas/atlas_f77.h])
               AC_CHECK_HEADER([atlas/blas.h]) \
               AC_CHECK_HEADER([atlas/cblas.h]) \
               AC_CHECK_HEADER([atlas/atlas.h]) \
               AC_CHECK_HEADER([atlas/clapack.h]) \
               AC_CHECK_HEADER([atlas.h]) \
               AC_CHECK_LIB([atlas],[ATL_cswap],[],[echo libatlas not found] ) \
               AC_CHECK_FUNC([ATL_cswap], [AC_DEFINE([HAVE_ATL_CSWAP], [1],[Define function ATL_cswap exists.])],[] )
 ],
 [])


# alternate location

AC_CHECK_HEADER([blas.h])
AC_CHECK_HEADER([cblas.h])
AC_CHECK_HEADER([lapack.h])

# try to find libray in usual spaces
AC_CHECK_LIB([m],[fabs],[],[echo fabs not found] )

AC_CHECK_LIB([blas],[dgemm_],[],[echo blas not found] )
AC_CHECK_LIB([cblas],[cblas_xerbla],[],[echo cblas not found] )



AC_SUBST(DRDC_PREFIX)
AC_SUBST(prefix)
AC_SUBST(libdir)
AC_SUBST(includedir)
AC_SUBST(srcdir)



# output phase - puts  results into files
AC_CONFIG_HEADER(config.h)

# standard compilation directories
AC_CONFIG_FILES([
	Makefile 
	doxygen/libdrdc.cfg
	src/Makefile
	src/cexcept/Makefile
	src/coordinate/Makefile
	src/matrix_ops/Makefile
    src/homogeneous/Makefile
	src/quaternion/Makefile
	src/time_conv/Makefile
	src/unit_conv/Makefile
	src/data_conv/Makefile
	src/wrapper/Makefile
	src/sglib/Makefile
	])

# conditional compilation directories
AS_IF(
[test "$enable_f2cblas" = true ],
[
AC_CONFIG_FILES([	
	src/f2c_blas/Makefile])
])


AS_IF(
[test "$enable_extras" = true ],
[
AC_CONFIG_FILES([	
	src/extras/Makefile
	src/extras/dp46/Makefile	
	])
])


# conditional test suite 
AS_IF(
[test "$enable_tests" = true ],
[
AC_CONFIG_FILES([	
	tests/Makefile
	tests/common/Makefile
	tests/cexcept/Makefile
	tests/wrapper/Makefile
	tests/extras/Makefile
	tests/sglib/Makefile
	])
])

AM_DEP_TRACK

AC_OUTPUT

dnl AC_MSG_NOTICE(configured install directory is )
dnl AC_MSG_RESULT($DRDC_PREFIX)	 
dnl AC_MSG_RESULT($libdir)	
dnl AC_MSG_RESULT($includedir)	
dnl AC_MSG_RESULT($PACKAGE)
dnl AC_MSG_RESULT($enable_tests)
dnl echo ${PACKAGE_STRING} "library version is... " ${LIB_VER}
dnl echo ${PACKAGE_STRING} "library release is... " ${REL_VER}



dnl   LIBDRDC configuration summary
dnl   -------------------------

cat <<EOF
   LIBDRDC configuration summary
   -------------------------
   TARGET_OS                     : ${TARGET_OS}
   target_cpu                    : ${target_cpu}
   DRDC_PREFIX                   : ${DRDC_PREFIX}
   PATH                          : ${PATH}
   AM_CFLAGS                     : ${AM_CFLAGS}
   AM_LDFLAGS                    : ${AM_LDFLAGS}
   Install lib directory         : ${libdir}
   Install include directory     : ${includedir}
   Library version               : ${LIB_VER}
   Library release               : ${REL_VER}
   enable tests                  : ${enable_tests}
   enable F2CBLAS library        : ${enable_f2cblas}
   enable extras	     		 : ${enable_extras}
	 
EOF
