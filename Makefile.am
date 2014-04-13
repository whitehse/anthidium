## top directory

#Build in these directories:
#ACLOCAL_AMFLAGS = -I m4
SUBDIRS = libltdl eocene eocene_modules eonessa eonessa_modules eosimias anthidium

#Distribute these directories:
DIST_SUBDIRS = libltdl eocene eocene_modules eonessa anthidium

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = eocene-1.0.pc

pkglibdir = $(libdir)/eocene

AM_CPPFLAGS = \
    -DPACKAGE_PKG_LIB_DIR=\""$(pkglibdir)"\" \
    -DPACKAGE_SYSCONF_DIR=\""$(sysconfdir)"\" \
    -I$(top_srcdir)
#    -DPACKAGE_LIBEXEC_DIR=\""$(libexecdir)"\" \
#    -DPACKAGE_DATA_DIR=\""$(datadir)"\" \
#    -DPACKAGE_BIN_DIR=\""$(bindir)"\" \
#    -DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
#    -DPACKAGE_LOCALSTATEDIR=\""$(localstatedir)"\" \
#    -DPACKAGE_SCRIPT_DIR=\""$(libexecdir)/scripts"\" \
#    $(LIBCONFIG_CFLAGS) $(EV_CFLAGS)

EXTRA_DIST=

