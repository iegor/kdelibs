AUTOMAKE_OPTIONS = foreign

KDE_CXXFLAGS = -DQT_PLUGIN

INCLUDES = $(all_includes)

stylercdir = $(kde_datadir)/kstyle/themes
stylerc_DATA = aurora.themerc
EXTRA_DIST = $(stylerc_DATA)

noinst_HEADERS = aurora.h

kde_style_LTLIBRARIES = aurora.la
aurora_la_SOURCES = aurora.cpp
aurora_la_LDFLAGS = $(all_libraries) $(KDE_PLUGIN) -module
aurora_la_LIBADD = ../../kdefx/libkdefx.la $(LIB_QT)
aurora_la_METASOURCES = AUTO

DISTCLEANFILES = $(aurora_la_METASOURCES)
