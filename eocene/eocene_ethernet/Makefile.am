h_sources = eocene_ethernet.h eocene_ethernet_base.h eocene_ethernet_ethertypes.h eocene_ethernet_saps.h eocene_ethernet_util.h
cc_sources = eocene_ethernet.c eocene_ethernet_util.c

AM_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/eosimias -I$(top_srcdir)/eocene

pkglibdir = $(libdir)/eocene

pkglib_LTLIBRARIES= eocene_ethernet.la
eocene_ethernet_la_SOURCES= $(h_sources) $(cc_sources)
eocene_ethernet_la_LDFLAGS= -module -avoid-version -no-undefined
eocene_ethernet_la_LIBADD= $(LIBADD_DLOPEN) $(LIBCONFIG_LIBS)
