INCLUDES = -I$(top_builddir)/kabc -I$(top_srcdir)/kabc $(all_includes)

# these are the headers for your project
noinst_HEADERS   = resourceevo.h dbwrapper.h

kde_module_LTLIBRARIES = kabc_evo.la

kabc_evo_la_SOURCES = dbwrapper.cpp resourceevo.cpp

kabc_evo_la_LDFLAGS	= $(all_libraries) -module $(KDE_PLUGIN)
kabc_evo_la_LIBADD	= ../../../kabc/libkabc.la ../../../kdeui/libkdeui.la -ldb ../../../kabc/vcardparser/libvcards.la

METASOURCES = AUTO

messages: rc.cpp
	$(XGETTEXT) *.cpp -o $(podir)/kabc_evolution.pot

servicedir = $(kde_servicesdir)/kresources/kabc
service_DATA = evolution.desktop
