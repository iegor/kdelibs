
#	This file is part of the KDE libraries
#    Copyright (C) 1997 Matthias Kalle Dalheimer (kalle@kde.org)
#			  (C) 1997 Stephan Kulow (coolo@kde.org)

#    This library is free software; you can redistribute it and/or
#    modify it under the terms of the GNU Library General Public
#    License as published by the Free Software Foundation; either
#    version 2 of the License, or (at your option) any later version.

#    This library is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#    Library General Public License for more details.

#    You should have received a copy of the GNU General Public License
#    along with this library; see the file COPYING.  If not, write to
#    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
#    Boston, MA 02110-1301, USA.

#SUBDIRS = . tests

INCLUDES= $(all_includes)

lib_LTLIBRARIES = libkdefx.la
libkdefx_la_LDFLAGS = $(KDE_RPATH) $(KDE_MT_LDFLAGS) $(all_libraries) -no-undefined -version-info 6:0:2
libkdefx_la_LIBADD = $(LIB_QT) $(LIB_XRENDER) $(LIB_X11)
libkdefx_la_NMCHECK = $(srcdir)/libkdefx.nmcheck
libkdefx_la_NMCHECKWEAK = $(srcdir)/libkdefx_weak.nmcheck $(top_srcdir)/kdecore/libqt-mt_weak.nmcheck \
	$(top_srcdir)/kdecore/standard_weak.nmcheck

include_HEADERS = kpixmap.h kpixmapsplitter.h \
	kpixmapeffect.h kimageeffect.h kdrawutil.h kstyle.h kcpuinfo.h

libkdefx_la_SOURCES = kpixmap.cpp kpixmapsplitter.cpp \
		kpixmapeffect.cpp kimageeffect.cpp kdrawutil.cpp kstyle.cpp \
		kcpuinfo.cpp

METASOURCES = AUTO

EXTRA_DIST = Mainpage.dox

DOXYGEN_REFERENCES = kdecore
include ../admin/Doxyfile.am

