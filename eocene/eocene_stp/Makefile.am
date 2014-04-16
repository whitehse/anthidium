h_sources = eocene_stp.h eocene_stp_base.h
cc_sources = eocene_stp.c

AM_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/eosimias -I$(top_srcdir)/eocene -I$(top_srcdir)/eocene/eocene_ethernet

pkglibdir = $(libdir)/eocene

pkglib_LTLIBRARIES= eocene_stp.la
eocene_stp_la_SOURCES= $(h_sources) $(cc_sources)
eocene_stp_la_LDFLAGS= -module -avoid-version -no-undefined
eocene_stp_la_LIBADD= $(LIBADD_DLOPEN) $(LIBCONFIG_LIBS)
