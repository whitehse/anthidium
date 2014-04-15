h_sources = eosimias.h eosimias_base.h eosimias_util.h
cc_sources = eosimias.c eosimias_util.c

SUBDIRS = eosimias_bdb eosimias_libev

#Distribute these directories:
DIST_SUBDIRS = eosimias_bdb eosimias_libev

library_includedir=$(includedir)/eosimias
library_include_HEADERS = $(h_sources)

pkglibdir = $(libdir)/eosimias

AM_CPPFLAGS = \
    -I$(top_srcdir) -I$(top_srcdir)/libltdl \
    -DPACKAGE_PKG_LIB_DIR=\""$(pkglibdir)"\" \
    -DPACKAGE_SYSCONF_DIR=\""$(sysconfdir)"\" \
    -I$(top_srcdir) $(LIBCONFIG_CFLAGS) $(LUA_CFLAGS)
#    -DPACKAGE_LIBEXEC_DIR=\""$(libexecdir)"\" \
#    -DPACKAGE_DATA_DIR=\""$(datadir)"\" \
#    -DPACKAGE_BIN_DIR=\""$(bindir)"\" \
#    -DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
#    -DPACKAGE_LOCALSTATEDIR=\""$(localstatedir)"\" \
#    -DPACKAGE_SCRIPT_DIR=\""$(libexecdir)/scripts"\"

lib_LTLIBRARIES= libeosimias.la
libeosimias_la_SOURCES= $(h_sources) $(cc_sources)
libeosimias_la_LDFLAGS= -version-info $(GENERIC_LIBRARY_VERSION)
libeosimias_la_LIBADD= @LIBLTDL@ $(LIBCONFIG_LIBS) $(LUA_LIBS)
