h_sources = eocene.h eocene_base.h eocene_util.h
cc_sources = eocene.c eocene_util.c

SUBDIRS = eocene_dhcpv4 eocene_http eocene_sockets eocene_bridge_network eocene_ethernet eocene_ipv4 eocene_stp

#Distribute these directories:
DIST_SUBDIRS = eocene_dhcpv4 eocene_http eocene_sockets eocene_bridge_network eocene_ethernet eocene_ipv4 eocene_stp

library_includedir=$(includedir)/eocene
library_include_HEADERS = $(h_sources)

pkglibdir = $(libdir)/eocene

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

lib_LTLIBRARIES= libeocene.la
libeocene_la_SOURCES= $(h_sources) $(cc_sources)
libeocene_la_LDFLAGS= -version-info $(GENERIC_LIBRARY_VERSION)
libeocene_la_LIBADD= @LIBLTDL@ $(LIBCONFIG_LIBS) $(LUA_LIBS)
