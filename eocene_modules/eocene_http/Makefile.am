h_sources = eocene_http.h eocene_http_base.h
cc_sources = eocene_http.c

AM_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/eocene

pkglibdir = $(libdir)/eocene

pkglib_LTLIBRARIES= eocene_http.la
eocene_http_la_SOURCES= $(h_sources) $(cc_sources)
eocene_http_la_LDFLAGS= -module -avoid-version -no-undefined
eocene_http_la_LIBADD= $(LIBADD_DLOPEN) $(LIBCONFIG_LIBS)
