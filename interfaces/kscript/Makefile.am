SUBDIRS = . sample

INCLUDES = -I$(top_srcdir)/kio -I$(top_srcdir) -I$(srcdir) -I$(srcdir)/.. $(all_includes)

#lib_LTLIBRARIES = libkscriptloader.la libkscript.la
lib_LTLIBRARIES = libkscript.la
#libkscriptloader_la_SOURCES = scriptloader.cpp
#libkscriptloader_la_LDFLAGS = $(all_libraries) $(KDE_RPATH)
#libkscriptloader_la_LIBADD = $(LIB_KPARTS)

libkscript_la_SOURCES = scriptmanager.cpp
libkscript_la_LDFLAGS = $(all_libraries) $(KDE_RPATH) -no-undefined
libkscript_la_LIBADD = $(LIB_KIO) $(LIB_QT) $(LIB_KDECORE) $(LIB_KDEUI)

kscriptinclude_HEADERS = scriptinterface.h scriptclientinterface.h scriptmanager.h
kscriptincludedir = $(includedir)

METASOURCES = AUTO

servicetypedir = $(kde_servicetypesdir)
servicetype_DATA = scriptinterface.desktop
