kde_module_LTLIBRARIES = kded_kdetrayproxy.la

INCLUDES= -I$(top_srcdir)/kded $(all_includes)
kded_kdetrayproxy_la_SOURCES = kdetrayproxy.cpp module.cpp module.skel
kded_kdetrayproxy_la_LDFLAGS = $(all_libraries) -module -avoid-version
kded_kdetrayproxy_la_LIBADD = $(LIB_KDECORE) $(LIB_KDED) $(LIB_QT) $(top_builddir)/dcop/libDCOP.la $(LIB_X11) $(top_builddir)/kded/libkdeinit_kded.la

METASOURCES = AUTO

noinst_HEADERS = kdetrayproxy.h module.h

servicesdir = $(kde_servicesdir)/kded
services_DATA = kdetrayproxy.desktop
