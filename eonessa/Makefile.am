h_sources = eonessa.h eonessa_base.h eonessa_util.h
cc_sources = eonessa.c eonessa_util.c

#SUBDIRS = 

#Distribute these directories:
#DIST_SUBDIRS = 

library_includedir=$(includedir)/eonessa
library_include_HEADERS = $(h_sources)

pkglibdir = $(libdir)/eonessa

AM_CPPFLAGS = \
    -I$(top_srcdir) -I$(top_srcdir)/eosimias \
    -I$(top_srcdir)/libltdl \
    -DPACKAGE_PKG_LIB_DIR=\""$(pkglibdir)"\" \
    -DPACKAGE_SYSCONF_DIR=\""$(sysconfdir)"\" \
    -I$(top_srcdir) $(LIBCONFIG_CFLAGS) $(LUA_CFLAGS)
#    -DPACKAGE_LIBEXEC_DIR=\""$(libexecdir)"\" \
#    -DPACKAGE_DATA_DIR=\""$(datadir)"\" \
#    -DPACKAGE_BIN_DIR=\""$(bindir)"\" \
#    -DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
#    -DPACKAGE_LOCALSTATEDIR=\""$(localstatedir)"\" \
#    -DPACKAGE_SCRIPT_DIR=\""$(libexecdir)/scripts"\"

lib_LTLIBRARIES= libeonessa.la
libeonessa_la_SOURCES= $(h_sources) $(cc_sources)
libeonessa_la_LDFLAGS= -version-info $(GENERIC_LIBRARY_VERSION)
libeonessa_la_LIBADD= @LIBLTDL@ $(LIBCONFIG_LIBS) $(LUA_LIBS)
