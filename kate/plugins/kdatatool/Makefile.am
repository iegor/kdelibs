INCLUDES    = -I$(top_srcdir)/interfaces -I$(top_srcdir)/kdefx $(all_includes)
METASOURCES = AUTO

# Install this plugin in the KDE modules directory
kde_module_LTLIBRARIES = ktexteditor_kdatatool.la

ktexteditor_kdatatool_la_SOURCES = kate_kdatatool.cpp
ktexteditor_kdatatool_la_LIBADD = $(top_builddir)/interfaces/ktexteditor/libktexteditor.la $(LIB_QT) $(LIB_KDECORE) $(LIB_KFILE) $(LIB_KDEUI)
ktexteditor_kdatatool_la_LDFLAGS = -module $(KDE_PLUGIN) $(all_libraries)

kdatatooldatadir = $(kde_datadir)/ktexteditor_kdatatool
kdatatooldata_DATA = ktexteditor_kdatatoolui.rc

kde_services_DATA = ktexteditor_kdatatool.desktop

messages: rc.cpp
	$(XGETTEXT) *.cpp *.h -o $(podir)/ktexteditor_kdatatool.pot


