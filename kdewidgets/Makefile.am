
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

SUBDIRS=. pics tests
AM_CXXFLAGS = -DQT_PLUGIN

INCLUDES = -I$(top_srcdir)/kfile $(all_includes)

bin_PROGRAMS = makekdewidgets
makekdewidgets_SOURCES = makekdewidgets.cpp
makekdewidgets_LDFLAGS = $(KDE_RPATH) $(all_libraries)
makekdewidgets_LDADD = $(LIB_QT) ../kdecore/libkdecore.la 

kde_widget_LTLIBRARIES = kdewidgets.la
kdewidgets_la_LDFLAGS = $(KDE_PLUGIN) -module $(all_libraries)
kdewidgets_la_LIBADD = $(LIB_KIO) $(LIB_KABC) $(LIB_QT) $(LIB_KDEUI) $(LIB_KDECORE)
kdewidgets_la_SOURCES = classpreviews.cpp kdewidgets.cpp

kdewidgets.cpp: $(srcdir)/kde.widgets makekdewidgets
	./makekdewidgets -o kdewidgets.cpp $(srcdir)/kde.widgets

CLEANFILES = kdewidgets.cpp

