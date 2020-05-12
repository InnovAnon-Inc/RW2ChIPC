AC_INIT([librw2chipc], [0.0], [laurence.a.maddox@gmail.com])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AM_PROG_AR
LT_INIT([])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
 src/Makefile
])

AC_ARG_ENABLE([use-submodules],
    AS_HELP_STRING([--enable-use-submodules], [Enable use submodules]))
AM_CONDITIONAL([USE_SUBMODULES], [test x"$enable_use_submodules" = "xyes"])

AC_CONFIG_MACRO_DIR([m4])
#AC_CONFIG_SUBDIRS([glitter])

AC_CHECK_HEADERS([stdlib.h unistd.h sys/types.h])
AC_CHECK_HEADERS([glitter.h ezfork.h restart.h sfork.h])

AC_CHECK_LIB([stdlib],[fork],[ezfork],[restart],[sfork])

srcdir = @srcdir@
LIBRW2CHIPC_LIBADD="`PATH=$(srcdir)src:$PATH librw2chipc_config --libs`"
AC_SUBST(LIBRW2CHIPC_LIBADD)

INNOVANON_WARNINGS([])

AC_OUTPUT
