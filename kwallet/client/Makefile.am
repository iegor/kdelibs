
INCLUDES= -I$(srcdir) $(all_includes)

lib_LTLIBRARIES = libkwalletclient.la

libkwalletclient_la_LDFLAGS = $(KDE_RPATH) $(all_libraries) -version-info 1:1 -no-undefined
libkwalletclient_la_LIBADD = $(LIB_KDECORE) $(LIB_QT) $(top_builddir)/dcop/libDCOP.la
libkwalletclient_la_SOURCES =   kwallet.skel \
				kwallet.cc

libkwalletclient_la_METASOURCES = AUTO

include_HEADERS = kwallet.h kwallettypes.h

