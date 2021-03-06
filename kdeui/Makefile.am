
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

SUBDIRS = . tests about
DIST_SUBDIRS = kdetrayproxy

INCLUDES= -I$(top_srcdir)/kdefx -I$(top_srcdir)/interfaces $(all_includes)

# For the future: examine if condensing the tons of *_LDFLAGS variables
# into $(all_libraries) isn't better
AM_LDFLAGS = $(LDFLAGS_AS_NEEDED) $(LDFLAGS_NEW_DTAGS)

lib_LTLIBRARIES = libkdeui.la libkspell.la
libkdeui_la_LDFLAGS = $(KDE_MT_LDFLAGS) -no-undefined -version-info 6:0:2
libkdeui_la_LIBADD = ../kdecore/libkdecore.la $(LIB_QT) $(top_builddir)/dcop/libDCOP.la $(LIB_X11) $(top_builddir)/kdefx/libkdefx.la $(LIB_XEXT)

libkspell_la_LDFLAGS = $(KDE_MT_LDFLAGS) -version-info 6:0:2 -no-undefined
libkspell_la_SOURCES = dummy.cpp

picsdir = $(kde_datadir)/kdeui/pics
pics_DATA = aboutkde.png ktip-bulb.png ktip-background.png

include_HEADERS = kprogress.h kcolordlg.h \
		kcolordialog.h kselect.h \
		kdatepik.h kdatepicker.h kdatetbl.h kfontdialog.h kpopupmenu.h \
		kfontrequester.h ktabctl.h kstatusbar.h \
		kmainwindow.h kmainwindowiface.h ktoolbar.h kmenubar.h \
		knuminput.h kseparator.h klineedit.h \
		krestrictedline.h kcolorbutton.h kcolorbtn.h \
		ksystemtray.h kdockwindow.h kbuttonbox.h \
		keditcl.h kled.h keditlistbox.h \
		kwizard.h kkeydialog.h kkeybutton.h \
		kurllabel.h kruler.h kcursor.h \
		klineeditdlg.h kinputdialog.h kactivelabel.h \
		kcharselect.h kcolordrag.h qxembed.h \
		knumvalidator.h kdialog.h kdialogbase.h \
		kjanuswidget.h kaboutdialog.h \
		kauthicon.h kmessagebox.h ksharedpixmap.h \
		kdualcolorbtn.h kdualcolorbutton.h ktoolbarbutton.h \
		ktoolbarradiogroup.h ktextbrowser.h \
		kaction.h kactioncollection.h kactionclasses.h khelpmenu.h kswitchlanguagedialog.h \
		kcmodule.h kcmenumngr.h kpanelmenu.h kpanelappmenu.h \
		kactionshortcutlist.h kstdaction.h kcombobox.h \
		kiconview.h klistview.h klistbox.h kbugreport.h kpassdlg.h \
		kxmlguiclient.h kxmlgui.h kxmlguibuilder.h kxmlguifactory.h \
		kpixmapio.h kwordwrap.h \
		kedittoolbar.h kdockwidget.h kanimwidget.h \
		krootpixmap.h kaboutkde.h kaboutapplication.h \
		kpanelapplet.h kpushbutton.h kdcopactionproxy.h kcolorcombo.h \
		kpanelextension.h kcompletionbox.h ksqueezedtextlabel.h \
		kcommand.h kwindowlistmenu.h kfontcombo.h kaccelgen.h ktip.h \
		kdatewidget.h karrowbutton.h kguiitem.h kstdguiitem.h \
		kstringvalidator.h kwindowinfo.h \
		ktextedit.h kpassivepopup.h \
		kdatetimewidget.h ktimewidget.h ktimezonewidget.h kscrollview.h \
		kspell.h ksconfig.h kspelldlg.h ksyntaxhighlighter.h \
		ktabbar.h ktabwidget.h ksplashscreen.h kconfigdialog.h \
		kactionselector.h klanguagebutton.h klistviewsearchline.h \
		kpixmapregionselectorwidget.h kpixmapregionselectordialog.h \
		kiconviewsearchline.h ktoolbarlabelaction.h kshortcutdialog.h

# the order of the sources isn't randomly (at least not completely).
# the order is predictated by the use of X11 header files
# the files on the first line need to occur first when compiling
# with --enable-final since they use X defines that get undefined
# in ksharedpixmap.cpp
libkdeui_la_SOURCES = \
		qxembed.cpp ksharedpixmap.cpp kpixmapio.cpp \
		kpopupmenu.cpp ktoolbar.cpp kaction.cpp kstdaction.cpp \
		kactioncollection.cpp kactionclasses.cpp \
		kurllabel.cpp kmenubar.cpp kinputdialog.cpp \
		knuminput.cpp klineedit.cpp klistview.cpp kprogress.cpp \
		kcolordialog.cpp kselect.cpp kdatepicker.cpp \
		kdatetbl.cpp kfontrequester.cpp kfontdialog.cpp ktabctl.cpp \
		kstatusbar.cpp kmainwindow.cpp \
		keditlistbox.cpp kscrollview.cpp \
		kseparator.cpp krestrictedline.cpp  \
		kcolorbutton.cpp ksystemtray.cpp \
		kbuttonbox.cpp keditcl1.cpp keditcl2.cpp kled.cpp \
		kshortcutdialog_simple.ui kshortcutdialog_advanced.ui \
		kshortcutdialog.cpp kkeybutton.cpp kkeydialog.cpp \
		kruler.cpp kcursor.cpp klineeditdlg.cpp  \
		kcharselect.cpp kcolordrag.cpp  \
		knumvalidator.cpp kdialog.cpp kdialogbase.cpp \
		kjanuswidget.cpp kaboutdialog.cpp \
		kauthicon.cpp kmessagebox.cpp kdualcolorbutton.cpp \
		ktoolbarradiogroup.cpp ktoolbarbutton.cpp \
		ktextbrowser.cpp khelpmenu.cpp kswitchlanguagedialog.cpp \
		kcmenumngr.cpp kpanelmenu.cpp \
		kiconview.cpp klistbox.cpp kwordwrap.cpp kbugreport.cpp \
		kcombobox.cpp kpassdlg.cpp kxmlguiclient.cpp kxmlguifactory.cpp \
		kxmlguifactory_p.cpp kxmlguibuilder.cpp kedittoolbar.cpp \
		kpanelappmenu.cpp kdockwidget.cpp kdockwidget_private.cpp \
		kanimwidget.cpp krootpixmap.cpp kaboutkde.cpp \
		kaboutapplication.cpp kpanelapplet.cpp kdcopactionproxy.cpp \
		kcolorcombo.cpp kpushbutton.cpp kpanelextension.cpp \
		kcompletionbox.cpp ksqueezedtextlabel.cpp kcmodule.cpp \
		kcommand.cpp kwindowlistmenu.cpp kfontcombo.cpp ktip.cpp \
		kdatewidget.cpp karrowbutton.cpp kmainwindowiface.cpp \
                kmainwindowiface.skel kguiitem.cpp kstdguiitem.cpp \
		kstringvalidator.cpp kactivelabel.cpp \
		kwindowinfo.cpp ktextedit.cpp kwizard.cpp kpassivepopup.cpp \
		ktoolbarhandler.cpp kdatetimewidget.cpp ktimewidget.cpp ktimezonewidget.cpp \
		ksconfig.cpp kspelldlg.cpp \
		kspell.cpp ksyntaxhighlighter.cpp ktabbar.cpp ktabwidget.cpp \
		ksplashscreen.cpp kspellui.ui kconfigdialog.cpp \
		kactionselector.cpp klanguagebutton.cpp klistviewsearchline.cpp \
		kpixmapregionselectorwidget.cpp kpixmapregionselectordialog.cpp \
		kwhatsthismanager.cpp kiconviewsearchline.cpp \
		ktoolbarlabelaction.cpp

noinst_HEADERS = kdockwidget_private.h kdockwidget_p.h klistviewlineedit.h \
		kdialogbase_priv.h kaboutdialog_private.h kcursor_private.h \
		kdepackages.h kxmlguifactory_p.h \
		kstdaction_p.h kwhatsthismanager_p.h

scripts_SCRIPTS = preparetips
scriptsdir = $(kde_bindir)

libkdeui_la_METASOURCES = AUTO
libkdeui_la_NMCHECK = $(srcdir)/libkdeui.nmcheck
libkdeui_la_NMCHECKWEAK = $(srcdir)/libkdeui_weak.nmcheck $(top_srcdir)/kdecore/libkdecore_weak.nmcheck \
	$(top_srcdir)/dcop/libDCOP_weak.nmcheck $(top_srcdir)/kdecore/libqt-mt_weak.nmcheck

rcdir = $(kde_confdir)/ui
rc_DATA = ui_standards.rc

EXTRA_DIST = CHANGES.kdatepicker USERS.kdatepicker kpixmapio-perf.png dcolorreset.xpm kpartgui.dtd dcolorarrow.xbm colors Mainpage.dox

.PHONY: kdepackages

kdepackages:
	-rm $(srcdir)/kdepackages.h
	curl "http://bugsold.kde.org/xml.cgi?data=versiontable" > tmp_download
	echo "// DO NOT EDIT - EDIT bugs/Maintainers instead" >  $(srcdir)/kdepackages.h
	echo "const char * const packages[] = {" >> $(srcdir)/kdepackages.h
	cat tmp_download | egrep "product|component" | grep -v "</product>" | \
	sed -e "s,<product name=\"\([^\"]*\)\">,product=\"\1\"; component=\"general\",; \
	s#<component>\([^<]*\)</component>#component=\"\1\"#"  > tmp_download2
	(while read i; do eval $$i; echo "\"$$product/$$component\","; done) < tmp_download2 | \
	sed -e "s,/general\",/00general\"," | LC_ALL=C sort -u | \
	grep -v 'valgrind/' | sed -e "s,/00general\",\"," >> $(srcdir)/kdepackages.h
	echo "0 };" >>  $(srcdir)/kdepackages.h
	rm tmp_download2 tmp_download

dummy.cpp:
	echo "#ifdef _AIX" >dummy.cpp
	echo "namespace {" >> dummy.cpp
	echo "void *not_empty_file;" >>dummy.cpp
	echo "}" >> dummy.cpp
	echo "#endif" >> dummy.cpp

DOXYGEN_REFERENCES = kdecore kdefx dcop kio kutils
DOXYGEN_SET_INTERNAL_DOCS = YES
include ../admin/Doxyfile.am
