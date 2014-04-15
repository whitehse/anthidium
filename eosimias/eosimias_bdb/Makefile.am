h_sources = eosimias_bdb.h eosimias_bdb_base.h
cc_sources = eosimias_bdb.c

AM_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/eosimias

pkglibdir = $(libdir)/eosimias

pkglib_LTLIBRARIES= eosimias_bdb.la
eosimias_bdb_la_SOURCES= $(h_sources) $(cc_sources)
eosimias_bdb_la_LDFLAGS= -module -avoid-version -no-undefined
eosimias_bdb_la_LIBADD= $(LIBADD_DLOPEN) $(LIBCONFIG_LIBS) -ldb
