INCLUDES =
AM_LDFLAGS = $(all_libraries) $(KDE_RPATH)
METASOURCES = AUTO

kde_module_LTLIBRARIES = kxzipfilter.la

kxzipfilter_la_SOURCES = kxzipfilter.cpp
kxzipfilter_la_LIBADD = $(LIB_KIO) $(LIBZ) $(LIB_QT) $(LIB_KDECORE)
kxzipfilter_la_LDFLAGS = $(all_libraries) -module $(KDE_PLUGIN)

kde_services_DATA = kxzipfilter.desktop