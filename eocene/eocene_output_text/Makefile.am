h_sources = eocene_output_text.h eocene_output_text_base.h
cc_sources = eocene_output_text.c

AM_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/eocene -I$(top_srcdir)/eocene_modules/eocene_ethernet

pkglibdir = $(libdir)/eocene

pkglib_LTLIBRARIES= eocene_output_text.la
eocene_output_text_la_SOURCES= $(h_sources) $(cc_sources)
eocene_output_text_la_LDFLAGS= -module -avoid-version -no-undefined
eocene_output_text_la_LIBADD= $(LIBADD_DLOPEN) $(LIBCONFIG_LIBS)
