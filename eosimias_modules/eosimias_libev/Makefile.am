h_sources = eosimias_libev.h eosimias_libev_base.h
cc_sources = eosimias_libev.c

AM_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/eosimias

pkglibdir = $(libdir)/eosimias

pkglib_LTLIBRARIES= eosimias_libev.la
eosimias_libev_la_SOURCES= $(h_sources) $(cc_sources)
eosimias_libev_la_LDFLAGS= -module -avoid-version -no-undefined
eosimias_libev_la_LIBADD= $(LIBADD_DLOPEN) $(LIBCONFIG_LIBS) -lev
