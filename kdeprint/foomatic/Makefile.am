INCLUDES = -I$(top_srcdir)/kdeprint $(all_includes)

kde_module_LTLIBRARIES = kdeprint_foomatic.la

kdeprint_foomatic_la_SOURCES = kmfoomaticfactory.cpp \
				  kmfoomaticmanager.cpp \
				  kfoomaticprinterimpl.cpp
kdeprint_foomatic_la_LDFLAGS = $(all_libraries) -module -avoid-version -no-undefined
kdeprint_foomatic_la_LIBADD = $(top_builddir)/kdeprint/management/libkdeprint_management.la
kdeprint_foomatic_la_METASOURCES = AUTO

noinst_HEADERS = kmfoomaticmanager.h \
		 kfoomaticprinterimpl.h

bin_PROGRAMS = make_driver_db_foomatic

make_driver_db_foomatic_SOURCES = make_driver_db_foomatic.c

entry_DATA = foomatic.print
entrydir = $(kde_datadir)/kdeprint/plugins
