INCLUDES = -I$(top_srcdir)/kio $(all_includes)
AM_LDFLAGS = $(all_libraries) $(KDE_RPATH)
METASOURCES = AUTO

kde_module_LTLIBRARIES = kgzipfilter.la

kgzipfilter_la_SOURCES = kgzipfilter.cpp
kgzipfilter_la_LIBADD = $(LIB_KIO) $(LIBZ) $(LIB_QT) $(LIB_KDECORE)
kgzipfilter_la_LDFLAGS = $(all_libraries) -module $(KDE_PLUGIN)

kde_services_DATA = kgzipfilter.desktop

