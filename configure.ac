
dnl --------------------------------
dnl Initialization macros.
dnl --------------------------------

AC_INIT([anthidium], [0.1], [dwhite@olp.net])
AM_CONFIG_HEADER(config.h)

sinclude(m4/dbm.m4)

dnl -----------------------------------------------
dnl Package name and version number (user defined)
dnl -----------------------------------------------

GENERIC_LIBRARY_NAME=eocene

#release versioning
GENERIC_MAJOR_VERSION=1
GENERIC_MINOR_VERSION=0
GENERIC_MICRO_VERSION=0

#API version (often = GENERIC_MAJOR_VERSION.GENERIC_MINOR_VERSION)
GENERIC_API_VERSION=1.0
AC_SUBST(GENERIC_API_VERSION)

#shared library versioning
GENERIC_LIBRARY_VERSION=1:0:0
#                       | | |
#                +------+ | +---+
#                |        |     |
#             current:revision:age
#                |        |     |
#                |        |     +- increment if interfaces have been added
#                |        |        set to zero if interfaces have been removed
#                                  or changed
#                |        +- increment if source code has changed
#                |           set to zero if current is incremented
#                +- increment if interfaces have been added, removed or changed


dnl --------------------------------
dnl Package name and version number
dnl --------------------------------

AC_SUBST(GENERIC_LIBRARY_VERSION)

PACKAGE=$GENERIC_LIBRARY_NAME
AC_SUBST(GENERIC_LIBRARY_NAME)

GENERIC_VERSION=$GENERIC_MAJOR_VERSION.$GENERIC_MINOR_VERSION.$GENERIC_MICRO_VERSION
GENERIC_RELEASE=$GENERIC_MAJOR_VERSION.$GENERIC_MINOR_VERSION
AC_SUBST(GENERIC_RELEASE)
AC_SUBST(GENERIC_VERSION)

VERSION=$GENERIC_VERSION

dnl -----------------------------------------------
dnl Checks for programs.
dnl -----------------------------------------------

AM_PROG_AR
AC_PROG_CC
AC_PROG_CXX
AM_PROG_LIBTOOL
AM_SANITY_CHECK

AC_LANG_CPLUSPLUS

dnl AC_CONFIG_SUBDIRS(libltdl)
AC_CONFIG_MACRO_DIR([libltdl/m4])
LT_CONFIG_LTDL_DIR([libltdl])
AM_INIT_AUTOMAKE([foreign -Wall -Werror dist-bzip2])
AC_LIBTOOL_DLOPEN
dnl AC_LIBLTDL_CONVENIENCE
AC_LIBLTDL_INSTALLABLE
AC_PROG_LIBTOOL
LTDL_INIT
PKG_CHECK_MODULES([LIBCONFIG], [libconfig])
PKG_CHECK_MODULES([LUA], [lua5.1])

dnl -----------------------------------------------
dnl Generates Makefile's, configuration files and scripts
dnl -----------------------------------------------

AC_OUTPUT(Makefile \
          eosimias/Makefile \
          eosimias/eosimias_bdb/Makefile \
          eosimias/eosimias_libev/Makefile \
          eocene-1.0.pc \
          eocene/Makefile \
          eocene/eocene_sockets/Makefile \
          eocene/eocene_dhcpv4/Makefile \
          eocene/eocene_http/Makefile \
          eocene/eocene_bdb/Makefile \
          eocene/eocene_libev/Makefile \
          eocene/eocene_ethernet/Makefile \
          eocene/eocene_ipv4/Makefile \
          eocene/eocene_stp/Makefile \
          eocene/eocene_bridge_network/Makefile \
          eocene/eocene_output_text/Makefile \
		  anthidium/Makefile \
)

