/*
 * This file is part of the KDE Libraries
 * Copyright (C) 1999-2000 Espen Sand (espen@kde.org)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

// I (espen) prefer that header files are included alphabetically
#include <qhbox.h>
#include <qlabel.h>
#include <qtimer.h>
#include <qtoolbutton.h>
#include <qwhatsthis.h>
#include <qwidget.h>

#include <kaboutapplication.h>
#include <kaboutdata.h>
#include <kaboutkde.h>
#include <kaction.h>
#include <kapplication.h>
#include <kbugreport.h>
#include <kdialogbase.h>
#include <khelpmenu.h>
#include <kiconloader.h>
#include <klocale.h>
#include <kmessagebox.h>
#include <kpopupmenu.h>
#include <kstdaccel.h>
#include <kstdaction.h>

#include "kswitchlanguagedialog.h"

#include "config.h"
#include <qxembed.h>

class KHelpMenuPrivate
{
public:
    KHelpMenuPrivate():mSwitchApplicationLanguage(NULL)
    {
    }
    ~KHelpMenuPrivate()
    {
        delete mSwitchApplicationLanguage;
    }

    const KAboutData *mAboutData;
    KSwitchLanguageDialog *mSwitchApplicationLanguage;
};

KHelpMenu::KHelpMenu( QWidget *parent, const QString &aboutAppText,
		      bool showWhatsThis )
  : QObject(parent), mMenu(0), mAboutApp(0), mAboutKDE(0), mBugReport(0),
    d(new KHelpMenuPrivate)
{
  mParent = parent;
  mAboutAppText = aboutAppText;
  mShowWhatsThis = showWhatsThis;
  d->mAboutData = 0;
}

KHelpMenu::KHelpMenu( QWidget *parent, const KAboutData *aboutData,
		      bool showWhatsThis, KActionCollection *actions )
  : QObject(parent), mMenu(0), mAboutApp(0), mAboutKDE(0), mBugReport(0),
    d(new KHelpMenuPrivate)
{
  mParent = parent;
  mShowWhatsThis = showWhatsThis;

  d->mAboutData = aboutData;

  if (!aboutData)
    mAboutAppText = QString::null;

  if (actions)
  {
    KStdAction::helpContents(this, SLOT(appHelpActivated()), actions);
    if (showWhatsThis)
      KStdAction::whatsThis(this, SLOT(contextHelpActivated()), actions);
    KStdAction::reportBug(this, SLOT(reportBug()), actions);
    KStdAction::aboutApp(this, SLOT(aboutApplication()), actions);
    KStdAction::aboutKDE(this, SLOT(aboutKDE()), actions);
    KStdAction::switchApplicationLanguage(this, SLOT(switchApplicationLanguage()), actions);
  }
}

KHelpMenu::~KHelpMenu()
{
  delete mMenu;
  delete mAboutApp;
  delete mAboutKDE;
  delete mBugReport;
  delete d;
}


KPopupMenu* KHelpMenu::menu()
{
  if( !mMenu )
  {
    //
    // 1999-12-02 Espen Sand:
    // I use hardcoded menu id's here. Reason is to stay backward
    // compatible.
    //
    const KAboutData *aboutData = d->mAboutData ? d->mAboutData : KGlobal::instance()->aboutData();
    QString appName = (aboutData)? aboutData->programName() : QString::fromLatin1(qApp->name());

    mMenu = new KPopupMenu();
    connect( mMenu, SIGNAL(destroyed()), this, SLOT(menuDestroyed()));

    bool need_separator = false;
    if (kapp->authorizeKAction("help_contents"))
    {
      mMenu->insertItem( BarIcon( "contents", KIcon::SizeSmall),
                     i18n( "%1 &Handbook" ).arg( appName) ,menuHelpContents );
      mMenu->connectItem( menuHelpContents, this, SLOT(appHelpActivated()) );
      mMenu->setAccel( KStdAccel::shortcut(KStdAccel::Help), menuHelpContents );
      need_separator = true;
    }

    if( mShowWhatsThis && kapp->authorizeKAction("help_whats_this") )
    {
      QToolButton* wtb = QWhatsThis::whatsThisButton(0);
      mMenu->insertItem( wtb->iconSet(),i18n( "What's &This" ), menuWhatsThis);
      mMenu->connectItem( menuWhatsThis, this, SLOT(contextHelpActivated()) );
      delete wtb;
      mMenu->setAccel( SHIFT + Key_F1, menuWhatsThis );
      need_separator = true;
    }

    if (kapp->authorizeKAction("help_report_bug") && aboutData && !aboutData->bugAddress().isEmpty() )
    {
      if (need_separator)
        mMenu->insertSeparator();
      mMenu->insertItem( i18n( "&Report Bug..." ), menuReportBug );
      mMenu->connectItem( menuReportBug, this, SLOT(reportBug()) );
      need_separator = true;
    }

    if (kapp->authorizeKAction("switch_application_language"))
    {
      if (need_separator)
        mMenu->insertSeparator();
      mMenu->insertItem( i18n( "Switch application &language..." ), menuSwitchLanguage );
      mMenu->connectItem( menuSwitchLanguage, this, SLOT(switchApplicationLanguage()) );
      need_separator = true;
    }

    if (need_separator)
      mMenu->insertSeparator();

    if (kapp->authorizeKAction("help_about_app"))
    {
      mMenu->insertItem( kapp->miniIcon(),
        i18n( "&About %1" ).arg(appName), menuAboutApp );
      mMenu->connectItem( menuAboutApp, this, SLOT( aboutApplication() ) );
    }

    if (kapp->authorizeKAction("help_about_kde"))
    {
      mMenu->insertItem( SmallIcon("about_kde"), i18n( "About &KDE" ), menuAboutKDE );
      mMenu->connectItem( menuAboutKDE, this, SLOT( aboutKDE() ) );
    }
  }

  return mMenu;
}



void KHelpMenu::appHelpActivated()
{
  kapp->invokeHelp();
}


void KHelpMenu::aboutApplication()
{
  if (d->mAboutData)
  {
    if( !mAboutApp )
    {
      mAboutApp = new KAboutApplication( d->mAboutData, mParent, "about", false );
      connect( mAboutApp, SIGNAL(finished()), this, SLOT( dialogFinished()) );
    }
    mAboutApp->show();
  }
  else if( mAboutAppText.isEmpty() )
  {
    emit showAboutApplication();
  }
  else
  {
    if( !mAboutApp )
    {
      mAboutApp = new KDialogBase( QString::null, // Caption is defined below
				   KDialogBase::Yes, KDialogBase::Yes,
				   KDialogBase::Yes, mParent, "about",
				   false, true, KStdGuiItem::ok() );
      connect( mAboutApp, SIGNAL(finished()), this, SLOT( dialogFinished()) );

      QHBox *hbox = new QHBox( mAboutApp );
      mAboutApp->setMainWidget( hbox );
      hbox->setSpacing(KDialog::spacingHint()*3);
      hbox->setMargin(KDialog::marginHint()*1);

      QLabel *label1 = new QLabel(hbox);
      label1->setPixmap( kapp->icon() );
      QLabel *label2 = new QLabel(hbox);
      label2->setText( mAboutAppText );

      mAboutApp->setPlainCaption( i18n("About %1").arg(kapp->caption()) );
      mAboutApp->disableResize();
    }

    mAboutApp->show();
  }
}


void KHelpMenu::aboutKDE()
{
  if( !mAboutKDE )
  {
    mAboutKDE = new KAboutKDE( mParent, "aboutkde", false );
    connect( mAboutKDE, SIGNAL(finished()), this, SLOT( dialogFinished()) );
  }
  mAboutKDE->show();
}


void KHelpMenu::reportBug()
{
  if( !mBugReport )
  {
    mBugReport = new KBugReport( mParent, false, d->mAboutData );
    connect( mBugReport, SIGNAL(finished()),this,SLOT( dialogFinished()) );
  }
  mBugReport->show();
}

void KHelpMenu::switchApplicationLanguage()
{
  if ( !d->mSwitchApplicationLanguage )
  {
    d->mSwitchApplicationLanguage = new KSwitchLanguageDialog( mParent, "switchlanguagedialog", false );
    connect( d->mSwitchApplicationLanguage, SIGNAL(finished()), this, SLOT( dialogFinished()) );
  }
  d->mSwitchApplicationLanguage->show();
}


void KHelpMenu::dialogFinished()
{
  QTimer::singleShot( 0, this, SLOT(timerExpired()) );
}


void KHelpMenu::timerExpired()
{
  if( mAboutKDE && !mAboutKDE->isVisible() )
  {
    delete mAboutKDE; mAboutKDE = 0;
  }

  if( mBugReport && !mBugReport->isVisible() )
  {
    delete mBugReport; mBugReport = 0;
  }

  if( mAboutApp && !mAboutApp->isVisible() )
  {
    delete mAboutApp; mAboutApp = 0;
  }

  if (d->mSwitchApplicationLanguage && !d->mSwitchApplicationLanguage->isVisible())
  {
    delete d->mSwitchApplicationLanguage; d->mSwitchApplicationLanguage = 0;
  }
}


void KHelpMenu::menuDestroyed()
{
  mMenu = 0;
}


void KHelpMenu::contextHelpActivated()
{
  QWhatsThis::enterWhatsThisMode();
  QWidget* w = QApplication::widgetAt( QCursor::pos(), true );
  while ( w && !w->isTopLevel() && !w->inherits("QXEmbed")  )
      w = w->parentWidget();
#ifdef Q_WS_X11
   if ( w && w->inherits("QXEmbed") )
	  (( QXEmbed*) w )->enterWhatsThisMode();
#endif
}

void KHelpMenu::virtual_hook( int, void* )
{ /*BASE::virtual_hook( id, data );*/ }


#include "khelpmenu.moc"
