h_sources = anthidium.h anthidium_base.h
cc_sources = anthidium.c

bin_PROGRAMS=anthidium
AM_CXXFLAGS = $(INTI_CFLAGS)

pkglibdir = $(libdir)/eocene

AM_CPPFLAGS = \
    -I$(top_srcdir) \
    -I$(top_srcdir)/eosimias \
    -I$(top_srcdir)/eocene \
    -I$(top_srcdir)/eonessa \
    -DPACKAGE_PKG_LIB_DIR=\""$(pkglibdir)"\" \
    -DPACKAGE_SYSCONF_DIR=\""$(sysconfdir)"\" \
    $(LIBCONFIG_CFLAGS) $(LUA_CFLAGS)

#    -DPACKAGE_LIBEXEC_DIR=\""$(libexecdir)"\" \
#    -DPACKAGE_DATA_DIR=\""$(datadir)"\" \
#    -DPACKAGE_BIN_DIR=\""$(bindir)"\" \
#    -DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
#    -DPACKAGE_LOCALSTATEDIR=\""$(localstatedir)"\" \
#    -DPACKAGE_SCRIPT_DIR=\""$(libexecdir)/scripts"\"

anthidium_SOURCES = $(h_sources) $(cc_sources)
anthidium_LDADD = $(INTI_LIBS) -L$(top_srcdir)/eosimias/.libs -leosimias -L$(top_srcdir)/eocene/.libs -leocene -L$(top_srcdir)/eonessa/.libs -leonessa -lpcap $(LIBCONFIG_LIBS) $(LUA_LIBS)
#select_LDFLAGS = -static
