INCLUDES = \
	-I$(srcdir)/include \
	-I$(srcdir)/include/generated \
	$(all_includes)

### KDE 4.0: either make noinst or rename to something like libkvcard
lib_LTLIBRARIES = libvcard.la

libvcard_la_SOURCES = vCard-all.cpp
libvcard_la_LDFLAGS = $(all_libraries)
libvcard_la_LIBADD = $(LIB_KDECORE) $(LIB_QT)

check_PROGRAMS = testwrite testread

testwrite_LDFLAGS = $(all_libraries) $(KDE_RPATH)
testwrite_LDADD = libvcard.la 
testwrite_SOURCES = testwrite.cpp

testread_LDFLAGS = $(all_libraries) $(KDE_RPATH)
testread_LDADD = libvcard.la 
testread_SOURCES = testread.cpp
