# let automoc handle all of the meta source files (moc)
METASOURCES = AUTO
# set the include path for X, qt and KDE
INCLUDES = -I$(top_srcdir) $(all_includes) $(AVAHI_CFLAGS)

lib_LTLIBRARIES = libkdnssd.la

noinst_HEADERS = domainbrowser.h query.h remoteservice.h \
				 publicservice.h servicebase.h servicebrowser.h settings.h sdevent.h
libkdnssd_la_SOURCES = remoteservice.cpp responder.cpp \
					   servicebase.cpp settings.kcfgc publicservice.cpp \
					   query.cpp domainbrowser.cpp servicebrowser.cpp
dnssdincludedir = $(includedir)/dnssd
libkdnssd_la_CXXFLAGS = $(INCLUDES)
libkdnssd_la_LIBADD = $(LIB_KDECORE) $(AVAHI_LIBS) $(LIB_QT)
libkdnssd_la_LDFLAGS = $(all_libraries) $(KDE_RPATH) -version-info 1:0

#kde_kcfg_DATA = kcm_kdnssd.kcfg

include ../admin/Doxyfile.am

responder.cpp: responder.moc$
remoteservice.cpp: remoteservice.moc$
query.cpp: query.moc$
publicservice.cpp: publicservice.moc$
servicebrowser.cpp: servicebrowser.moc$
domainbrowser.cpp: domainbrowser.moc
