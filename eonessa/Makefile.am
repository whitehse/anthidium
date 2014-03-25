h_sources = eonessa.h eonessa_base.h eonessa_ethertypes.h eonessa_ip.h eonessa_util.h eonessa_radiotap.h
cc_sources = eonessa.c eonessa_ip.c eonessa_util.c

library_includedir=$(includedir)/eonessa
library_include_HEADERS = $(h_sources)

AM_CPPFLAGS = -I$(top_srcdir)

lib_LTLIBRARIES= libeonessa.la
libeonessa_la_SOURCES= $(h_sources) $(cc_sources)
libeonessa_la_LDFLAGS= -version-info $(GENERIC_LIBRARY_VERSION)

