#    This file is part of the KDE libraries
#    Copyright (C) 2002 George Staikos <staikos@kde.org>

#    This library is free software; you can redistribute it and/or
#    modify it under the terms of the GNU Library General Public
#    License as published by the Free Software Foundation; either
#    version 2 of the License, or (at your option) any later version.

#    This library is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#    Library General Public License for more details.

#    You should have received a copy of the GNU Library General Public License
#    along with this library; see the file COPYING.LIB.  If not, write to
#    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
#    Boston, MA 02110-1301, USA.

INCLUDES= -I$(srcdir)/.. -I$(top_srcdir) -I$(top_srcdir)/kwallet/backend -I$(top_builddir)/kwallet/backend -I$(top_srcdir)/kwallet/client -I$(top_builddir)/kwallet/client $(all_includes)

kde_module_LTLIBRARIES = kded_kwalletd.la

kded_kwalletd_la_LDFLAGS = $(all_libraries) -module -avoid-version
kded_kwalletd_la_LIBADD = $(LIB_KIO) ../../../kwallet/backend/libkwalletbackend.la ../../../kwallet/client/libkwalletclient.la $(LIB_KDED) $(LIB_QT) $(top_builddir)/dcop/libDCOP.la $(LIB_KDECORE) $(LIB_KDEUI)
kded_kwalletd_la_SOURCES = kwalletd.cpp kwalletd.skel ktimeout.cpp kwalletwizard.ui kbetterthankdialogbase.ui

METASOURCES = AUTO

noinst_HEADERS = kwalletd.h ktimeout.h kwalletwizard.ui.h

services_DATA = kwalletd.desktop
servicesdir = $(kde_servicesdir)/kded

kwalletwizard.lo: kwalletwizard.ui kwalletwizard.ui.h
kbetterthankdialogbase.lo: kbetterthankdialogbase.ui kbetterthankdialogbase.ui.h
