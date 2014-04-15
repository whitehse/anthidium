h_sources = eocene_sockets.h eocene_sockets_base.h
cc_sources = eocene_sockets.c

AM_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/eocene

pkglibdir = $(libdir)/eocene

pkglib_LTLIBRARIES= eocene_sockets.la
eocene_sockets_la_SOURCES= $(h_sources) $(cc_sources)
eocene_sockets_la_LDFLAGS= -module -avoid-version -no-undefined
eocene_sockets_la_LIBADD= $(LIBADD_DLOPEN) $(LIBCONFIG_LIBS)
