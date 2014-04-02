h_sources = eocene_libev.h eocene_libev_base.h
cc_sources = eocene_libev.c

AM_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/eocene

pkglibdir = $(libdir)/eocene

pkglib_LTLIBRARIES= eocene_libev.la
eocene_libev_la_SOURCES= $(h_sources) $(cc_sources)
eocene_libev_la_LDFLAGS= -module -avoid-version -no-undefined
eocene_libev_la_LIBADD= $(LIBADD_DLOPEN) $(LIBCONFIG_LIBS) -lev
