h_sources = eocene_bdb.h eocene_bdb_base.h
cc_sources = eocene_bdb.c

AM_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/eocene

pkglibdir = $(libdir)/eocene

pkglib_LTLIBRARIES= eocene_bdb.la
eocene_bdb_la_SOURCES= $(h_sources) $(cc_sources)
eocene_bdb_la_LDFLAGS= -module -avoid-version -no-undefined
eocene_bdb_la_LIBADD= $(LIBADD_DLOPEN) $(LIBCONFIG_LIBS) -ldb
