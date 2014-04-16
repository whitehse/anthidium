h_sources = eocene_bridge_network.h eocene_bridge_network_base.h
cc_sources = eocene_bridge_network.c

AM_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/eosimias -I$(top_srcdir)/eocene -I$(top_srcdir)/eocene/eocene_ethernet -I$(top_srcdir)/eocene/eocene_stp

pkglibdir = $(libdir)/eocene

pkglib_LTLIBRARIES= eocene_bridge_network.la
eocene_bridge_network_la_SOURCES= $(h_sources) $(cc_sources)
eocene_bridge_network_la_LDFLAGS= -module -avoid-version -no-undefined
eocene_bridge_network_la_LIBADD= $(LIBADD_DLOPEN) $(LIBCONFIG_LIBS)
