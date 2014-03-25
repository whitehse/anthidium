h_sources = eocene_dhcpv4.h eocene_dhcpv4_base.h eocene_dhcpv4_util.h
cc_sources = eocene_dhcpv4.c eocene_dhcpv4_util.c

AM_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/eonessa -I$(top_srcdir)/eocene

pkglibdir = $(libdir)/eocene

pkglib_LTLIBRARIES= eocene_dhcpv4.la
eocene_dhcpv4_la_SOURCES= $(h_sources) $(cc_sources)
eocene_dhcpv4_la_LDFLAGS= -module -avoid-version -no-undefined
eocene_dhcpv4_la_LIBADD= $(LIBADD_DLOPEN) $(LIBCONFIG_LIBS)
