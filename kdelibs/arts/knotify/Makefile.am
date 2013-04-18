
INCLUDES= -I$(top_srcdir)/arts/kde -I$(includedir)/arts $(all_includes)

####### Files

kde_module_LTLIBRARIES = knotify.la

knotify_la_SOURCES	= knotify.cpp knotify.skel
if include_ARTS
knotify_la_LIBADD	= -lsoundserver_idl $(LIB_KDEUI) $(top_builddir)/arts/kde/libartskde.la \
	$(LIB_QT) $(top_builddir)/dcop/libDCOP.la $(LIB_KDECORE) -lartsflow_idl -lmcop
endif
knotify_la_LDFLAGS = $(all_libraries) -module -avoid-version
knotify_la_METASOURCES = AUTO

check_PROGRAMS		= knotifytest
knotifytest_SOURCES	= knotifytest.cpp
knotifytest_LDADD	= $(LIB_KDECORE)
knotifytest_LDFLAGS	= $(all_libraries) $(KDE_RPATH)

noinst_HEADERS	=  knotify.h

kdelnkdir = $(kde_servicesdir)
kdelnk_DATA = knotify.desktop

messages:
	$(XGETTEXT) knotify.cpp -o $(podir)/knotify.pot

