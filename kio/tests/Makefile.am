#    This file is part of the KDE libraries
#    Copyright (C) 1997 David Faure <faure@kde.org>

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

INCLUDES= -I$(top_srcdir) -I$(top_srcdir)/kio $(all_includes)
LDADD = $(LIB_KIO)
AM_LDFLAGS = $(all_libraries) $(KDE_RPATH)

check_PROGRAMS = ksycocatest getalltest kruntest ktartest kziptest\
                 kioslavetest kdirwatchtest kshredtest speed kurifiltertest \
                 kdefaultprogresstest kmimemagictest \
                 kfiltertest kiopassdlgtest kscantest kdirlistertest \
                 previewtest kionetrctest kdcopcheck metatest \
		 kmimefromext kpropsdlgtest kmfitest dataprotocoltest \
		 kprotocolinfotest ksycocaupdatetest netaccesstest jobtest \
		 kurlcompletiontest kmimetypetest kacltest

# Unfortunately some tests depend on the network settings, it seems
#check: kurifiltertest
#	./kurifiltertest
check-local: kziptest
	./kziptest list $(srcdir)/wronglocalsizes.zip

TESTS = kmimetypetest

bin_PROGRAMS = ktradertest

METASOURCES = AUTO

speed_SOURCES = speed.cpp
kioslavetest_SOURCES = kioslavetest.cpp
kshredtest_SOURCES = kshredtest.cpp
kdefaultprogresstest_SOURCES = kdefaultprogresstest.cpp
kionetrctest_SOURCES = kionetrctest.cpp
kiopassdlgtest_SOURCES = kiopassdlgtest.cpp
kurifiltertest_SOURCES = kurifiltertest.cpp
ksycocatest_SOURCES = ksycocatest.cpp
kdcopcheck_SOURCES = kdcopcheck.cpp
getalltest_SOURCES = getalltest.cpp
kruntest_SOURCES = kruntest.cpp
kdirwatchtest_SOURCES = kdirwatchtest.cpp
ktradertest_SOURCES = ktradertest.cpp
kmimemagictest_SOURCES = kmimemagictest.cpp
kfiltertest_SOURCES = kfiltertest.cpp
kscantest_SOURCES = kscantest.cpp
kdirlistertest_SOURCES = kdirlistertest.cpp
previewtest_SOURCES = previewtest.cpp
ktartest_SOURCES = ktartest.cpp
kziptest_SOURCES = kziptest.cpp
metatest_SOURCES = metatest.cpp
kmimefromext_SOURCES = kmimefromext.cpp
kpropsdlgtest_SOURCES = kpropsdlgtest.cpp
kmfitest_SOURCES = kmfitest.cpp
dataprotocoltest_SOURCES = dataprotocoltest.cpp
kprotocolinfotest_SOURCES = kprotocolinfotest.cpp
ksycocaupdatetest_SOURCES = ksycocaupdatetest.cpp
netaccesstest_SOURCES = netaccesstest.cpp
jobtest_SOURCES = jobtest.cpp
kurlcompletiontest_SOURCES = kurlcompletiontest.cpp
kmimetypetest_SOURCES = kmimetypetest.cpp
kacltest_SOURCES = kacltest.cpp


check_LTLIBRARIES = kunittest_kdirwatch.la
kunittest_kdirwatch_la_SOURCES = kdirwatchunittest.cpp
kunittest_kdirwatch_la_LIBADD = $(LIB_KUNITTEST) $(LIB_KIO)
kunittest_kdirwatch_la_LDFLAGS = -module $(KDE_CHECK_PLUGIN)

# kfile meta stuff. Comment this in, if you want a small
# metadata plugin test and "make install".
#kde_module_LTLIBRARIES = dummymeta.la
#dummymeta_la_SOURCES = dummymeta.cpp
#dummymeta_la_LIBADD = $(LIB_KIO)
#dummymeta_la_LDFLAGS = $(all_libraries) -module $(KDE_PLUGIN)

#services_DATA = dummymeta.desktop
#servicesdir = $(kde_servicesdir)
