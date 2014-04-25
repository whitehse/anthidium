h_sources = eonessa_snmp_snmpv2_mib.h eonessa_snmp_snmpv2_mib_base.h
cc_sources = eonessa_snmp_snmpv2_mib.c

AM_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/eosimias -I$(top_srcdir)/eonessa

pkglibdir = $(libdir)/eosimias

pkglib_LTLIBRARIES= eonessa_snmp_snmpv2_mib.la
eonessa_snmp_snmpv2_mib_la_SOURCES= $(h_sources) $(cc_sources)
eonessa_snmp_snmpv2_mib_la_LDFLAGS= -module -avoid-version -no-undefined
eonessa_snmp_snmpv2_mib_la_LIBADD= $(LIBADD_DLOPEN) $(LIBCONFIG_LIBS)
