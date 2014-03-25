h_sources = anthidium.h anthidium_base.h
cc_sources = anthidium.c

bin_PROGRAMS=anthidium
AM_CXXFLAGS = $(INTI_CFLAGS)

pkglibdir = $(libdir)/eocene

AM_CPPFLAGS = \
    -I$(top_srcdir) \
    -DPACKAGE_PKG_LIB_DIR=\""$(pkglibdir)"\" \
    -DPACKAGE_SYSCONF_DIR=\""$(sysconfdir)"\" \
    -I$(top_srcdir) $(LIBCONFIG_CFLAGS) $(LUA_CFLAGS)

#    -DPACKAGE_LIBEXEC_DIR=\""$(libexecdir)"\" \
#    -DPACKAGE_DATA_DIR=\""$(datadir)"\" \
#    -DPACKAGE_BIN_DIR=\""$(bindir)"\" \
#    -DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
#    -DPACKAGE_LOCALSTATEDIR=\""$(localstatedir)"\" \
#    -DPACKAGE_SCRIPT_DIR=\""$(libexecdir)/scripts"\"

anthidium_SOURCES = $(h_sources) $(cc_sources)
anthidium_LDADD = $(INTI_LIBS) -L../eonessa/.libs -leonessa -L../eocene/.libs -leocene -lpcap $(LIBCONFIG_LIBS) $(LUA_LIBS)
#select_LDFLAGS = -static
