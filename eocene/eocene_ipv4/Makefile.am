h_sources = eocene_ipv4.h eocene_ipv4_base.h
cc_sources = eocene_ipv4.c

AM_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/eosimias -I$(top_srcdir)/eocene -I$(top_srcdir)/eocene/eocene_ethernet

pkglibdir = $(libdir)/eocene

pkglib_LTLIBRARIES= eocene_ipv4.la
eocene_ipv4_la_SOURCES= $(h_sources) $(cc_sources)
eocene_ipv4_la_LDFLAGS= -module -avoid-version -no-undefined
eocene_ipv4_la_LIBADD= $(LIBADD_DLOPEN) $(LIBCONFIG_LIBS)
