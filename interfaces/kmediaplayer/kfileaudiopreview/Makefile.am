INCLUDES = -I$(top_srcdir)/interfaces/ -I$(top_srcdir)/arts/kde -I$(includedir)/arts $(all_includes)
METASOURCES = AUTO

kde_module_LTLIBRARIES = kfileaudiopreview.la

kfileaudiopreview_la_SOURCES = kfileaudiopreview.cpp
kfileaudiopreview_la_LDFLAGS = $(all_libraries) $(KDE_RPATH) -module -avoid-version -no-undefined
kfileaudiopreview_la_LIBADD = $(top_builddir)/interfaces/kmediaplayer/libkmediaplayer.la $(top_builddir)/arts/kde/libartskde.la $(LIB_KIO) $(LIB_QT) $(LIB_KDECORE)

noinst_HEADERS = kfileaudiopreview.h

messages:
	$(XGETTEXT) $(kfileaudiopreview_la_SOURCES) -o $(podir)/kfileaudiopreview.pot
