INCLUDES = -I$(top_srcdir)/kio $(all_includes)
METASOURCES = AUTO

kde_module_LTLIBRARIES = kbzip2filter.la

kbzip2filter_la_SOURCES = kbzip2filter.cpp
kbzip2filter_la_LIBADD = $(LIB_KIO) $(LIBBZ2) $(LIB_QT) $(LIB_KDECORE)
kbzip2filter_la_LDFLAGS = $(all_libraries) -module $(KDE_PLUGIN)

kde_services_DATA = kbzip2filter.desktop

