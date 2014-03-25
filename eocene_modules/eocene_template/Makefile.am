h_sources = eocene_template.h eocene_template_base.h
cc_sources = eocene_template.c

AM_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/eonessa -I$(top_srcdir)/eocene

pkglibdir = $(libdir)/eocene

pkglib_LTLIBRARIES= eocene_template.la
eocene_template_la_SOURCES= $(h_sources) $(cc_sources)
eocene_template_la_LDFLAGS= -module -avoid-version -no-undefined
eocene_template_la_LIBADD= $(LIBADD_DLOPEN) $(LIBCONFIG_LIBS)
