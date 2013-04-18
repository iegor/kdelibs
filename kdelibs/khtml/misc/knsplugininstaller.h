/*
 * This file is part of the KDE project.
 *
 * Copyright (C) 2005 Benoit Canet <bcanet@dental-on-line.fr>
 *           with some advices from Aurelien Gateau <agateau@dental-on-line.fr>
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
 * the Free Software Foundation, Inc., 51 Franklin Steet, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#ifndef KNSPLUGININSTALLER_H
#define KNSPLUGININSTALLER_H

#include <job.h>
#include <ktextedit.h>
#include <kmimetype.h>
#include <kprogress.h> 
#include <kurl.h>
#include <kwizard.h>

#include <qbuttongroup.h>
#include <qdom.h>
#include <qlabel.h>
#include <qobject.h>
#include <qprocess.h>
#include <qradiobutton.h>
#include <qvaluelist.h>
#include <qvbox.h>
#include <qwidget.h>

class QStringList;

/*
 * This class contains all the infos needed to install a given plugin
 * Takes and parse a QDomNode in its constructor
 */
class KNSPluginInfo 
{

public:

    /*
     * Construct the plugin info object
     */
    KNSPluginInfo();
    KNSPluginInfo(QDomNode pluginNode);
    ~KNSPluginInfo();

    /*
     * Check the validity of the plugin info object
     */
    bool isValid() const;

    //Accessor methods
    QString pluginName() const;
    QString licence() const;
    KURL licenceURL() const;
    KURL pluginURL() const;
    const QStringList& pluginFileList() const;
   
private:
 
    // plugin info
    QString m_pluginName;
    QString m_licence;
    KURL m_licenceURL;
    KURL m_pluginURL;
    QStringList m_pluginFileList;
    
    
};


/*
 * This class contain all the the methods used to perform a plugin installation
 *
 */
class KNSPluginInstallEngine : public QObject
{
    Q_OBJECT
public:

    /*
     * Construct the class
     */
    KNSPluginInstallEngine(KMimeType::Ptr mime);
    ~KNSPluginInstallEngine();
    
    /*
     * Check if the installer engine and wizzard is activated
     */
    static bool isActive();
    /**
     * Check the availability of a plugin 
     */
    bool pluginAvailable();
    /*
     * Return the list of plugins Available
     */
    const QValueList<KNSPluginInfo>& pluginList() const;
    void startInstall(KNSPluginInfo info);

    

private:

    // methods used to check the kde config and detect if an adequate plugin is available
 
    /*
     * load kde KNSPluginInstaller config
     */
    bool loadConfig();
    /*
     * retrieve the xml configuration file
     */
    bool loadXmlConfig();
    /*
     * parse the xml configuration file
     */
    bool findPlugin();
    

    QMap<QString, QString> m_archMap;
    QString m_pluginsXmlConfig;
    QValueList<KNSPluginInfo> m_pluginList;
    KMimeType::Ptr m_mime;
    KURL m_pluginsListFileURL;
    QString m_tmpPluginFileName;
    KIO::CopyJob *m_downloadJob;
    KIO::CopyJob *m_installFileJob;
    KNSPluginInfo m_toInstallPluginInfo;
    QProcess *m_scanProc;
    
signals:
    // Signals used to communicate with the wizzard 
    void installProgress(int percent);
    void installCompleted();
    void installFailed();
   
private slots:
    // Used to monitor the plugin downloading
    void slotDownLoadProgress(KIO::Job *job, unsigned long percent);
    void slotDownloadResult(KIO::Job *job);
    
    // Used to monitor the plugin installation
    void slotCopyProgress(KIO::Job *job, unsigned long percent);
    void slotCopyResult(KIO::Job *job);

    // Used to monitor the plugins scan
    void readScanProcFromStdout();
    void endScanProc();



};

/*
 * This class is a wizzard used to install a plugin 
 */
class KNSPluginWizard : public KWizard
{
    Q_OBJECT
public:
        
    /**
    * Construct a KNSpluginInstaller
    */
    KNSPluginWizard(QWidget *parent, const char *name,  KMimeType::Ptr mime);
    ~KNSPluginWizard();


    /**
     * Lauch the wizzard
     */
    int exec();
    /*
     * Check the availability of a plugin
     */
    bool pluginAvailable();


private:
    // methods used in the constructor to init the wizzard pages
    void initConfirmationPage();
    void initLicencePage();
    void initInstallationProgressPage();
    void initFinishPage();

    // in this method we disable or enable the wizzard pages buttons
    void initPagesButtonStates();
    
    /*
     * Connect signals
     */
    void connectSignals();
    
    /*
     * Overiden method called when a page is shown
     */
    void showPage(QWidget *page);


    // Plugin installation engine
    KNSPluginInstallEngine m_installEngine;

    // pages widgets
    QVBox *m_confirmationVBox;
    QVBox *m_licenceVBox;
    QWidget *m_installationProgressWidget;
    QWidget *m_finishWidget;
    
    // plugin list
    KListView *m_pluginListView;
    
    // licence stuff
    QLabel *m_licencePageLabel;
    KTextEdit *m_licencePageText;
    QRadioButton *m_licencePageAgree;
    QRadioButton *m_licencePageDisagree;
    QButtonGroup *m_agreementButtonGroup;

    // installation progress bar
    KProgress *m_installationProgressBar;

    // Finish Label 
    QLabel *m_finishLabel;

    // installation status
    bool m_installationComplete;
 
private slots:
    /*
     * Check if the user Agree or disagree with the licence
     */
    void slotAgreementClicked(int id);
    /*
     * Called when the installation is completed
     */
    void slotInstallationCompleted();
    /*
     * Called when the installation has failed
     */
    void slotInstallationFailed();

signals:
    /*
     * Emited when the installation has complete - TODO connect this signal to reload the page
     */
    void pluginInstallCompleted();
};



   

#endif
