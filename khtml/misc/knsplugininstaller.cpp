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


#include "knsplugininstaller.moc"

#include <kdebug.h>
#include <kdiroperator.h> 
#include <klistview.h>
#include <klocale.h>
#include <kstddirs.h>
#include <ktempfile.h> 
#include <netaccess.h>

#include <qbuttongroup.h>
#include <qdir.h>
#include <qiodevice.h>
#include <qfile.h>
#include <qlabel.h>
#include <qlayout.h> 
#include <qmap.h>
#include <qstringlist.h>
#include <qtextstream.h>

#include <sys/utsname.h>

// Use 6031 for debugging (render_frame)
#define DEBUG_NUMBER 6031 

/*
 * Utility class to associate a list item with a pluginInfo object
 */
class PluginListItem : public QListViewItem
{

public:
    PluginListItem(KNSPluginInfo pluginInfo, QListView *parent)
    : QListViewItem(parent, pluginInfo.pluginName())
    , m_pluginInfo(pluginInfo) {}
    KNSPluginInfo pluginInfo() const { return m_pluginInfo; }

private:
    KNSPluginInfo m_pluginInfo;

};


// public methods 

KNSPluginInstallEngine::KNSPluginInstallEngine(KMimeType::Ptr mime) : QObject()
{
    m_mime = mime;

    // Fill the architecture map 
    m_archMap["i386"] = "ia32";
    m_archMap["i486"] = "ia32";
    m_archMap["i586"] = "ia32";
    m_archMap["i686"] = "ia32";
}

KNSPluginInstallEngine::~KNSPluginInstallEngine()
{
}

bool KNSPluginInstallEngine::pluginAvailable()
{

    if(m_pluginList.count())
        return true;
    
    // check if pluginsListFile is present in kde config
    if(!loadConfig())
        return false;

    // load the xml configuration file 
    if(!loadXmlConfig())
        return false;
    
    return findPlugin();
}

bool KNSPluginInstallEngine::isActive() 
{
    // check if we have a configuration key in the kde registry
    QString pluginsListFile;
    KConfig cfg("kcmnspluginrc", true);
    cfg.setGroup("Misc");
    pluginsListFile = cfg.readPathEntry("PluginsListFile");
    return !pluginsListFile.isEmpty();
}

const QValueList<KNSPluginInfo>& KNSPluginInstallEngine::pluginList() const
{
    return m_pluginList;
}

// private methods 
bool KNSPluginInstallEngine::loadConfig()
{
    QString pluginsListFile;
    KConfig cfg("kcmnspluginrc", true);
    cfg.setGroup("Misc");
    pluginsListFile = cfg.readPathEntry("PluginsListFile");
    if(!pluginsListFile.isEmpty())
    {
        m_pluginsListFileURL = KURL(pluginsListFile);
        kdDebug(DEBUG_NUMBER) << "config loaded "<<endl;
        return true;
    }
    return false;
}

bool KNSPluginInstallEngine::loadXmlConfig()
{

    // load the Xml configuration file 
    if(m_pluginsXmlConfig.isEmpty())
    {
        QString tmpFile;
        if(KIO::NetAccess::download(m_pluginsListFileURL, tmpFile, NULL)) {
            QFile f(tmpFile);
            if(!f.open(IO_ReadOnly))
                return false;
            QTextStream stream(&f);
            stream.setEncoding(QTextStream::UnicodeUTF8);
            m_pluginsXmlConfig = stream.read();
            f.close();
            KIO::NetAccess::removeTempFile(tmpFile);
        } else
            return false;
    }
    kdDebug(DEBUG_NUMBER) << "xml config loaded :" << endl;
    return true;
}

bool KNSPluginInstallEngine::findPlugin()
{

    // get system infos
    // TODO/FIX : correct this to work with x86-64 machines
    utsname sysinfo;
    if(uname(&sysinfo))
        return false;
    QString sysname(sysinfo.sysname);
    QString machine(sysinfo.machine);
    QString arch = m_archMap[machine]; 
    
    // Parse the document
    QDomDocument doc("xmlConfig");
    doc.setContent(m_pluginsXmlConfig);
    QDomNodeList archList = doc.elementsByTagName(QString("arch"));
    QDomNode archNode, osNode , pluginNode, node;
    QDomElement e;

    // look for the correct architecture
    bool found = false;
    unsigned int i;
    for(i=0; i < archList.count() ; i++) {
        archNode = archList.item(i);
        e = archNode.toElement();
        if( e.attribute("architecture") == arch) {
            kdDebug(DEBUG_NUMBER) << "found correct architecture :" << arch << endl;
            found = true;
            break;
        }
    }

    if(!found)
        return false;
    
    // look for the correct os 
    found = false;
    osNode = archNode.firstChild();
    while(!osNode.isNull()) {
        e = osNode.toElement();
        if( e.tagName() == "os" && e.attribute("name") == sysname) {
            kdDebug(DEBUG_NUMBER) << "found correct os :" << sysname << endl;
            found = true;
            break;
        }
        osNode=osNode.nextSibling();
    }

    if(!found)
        return false;
   
    // Look for a plugin with the given mimetype
    pluginNode = osNode.firstChild();
    while(!pluginNode.isNull()) {
        e = pluginNode.toElement();
        if( e.tagName() == "plugin" && m_mime->is(e.attribute("mimetype")) ) {
            kdDebug(DEBUG_NUMBER) << "found correct plugin :" << e.attribute("mimetype") << endl;
            KNSPluginInfo pluginInfo(pluginNode);
                if(pluginInfo.isValid())
                    m_pluginList.append(pluginInfo);
        }
        pluginNode=pluginNode.nextSibling();
    }

    if(m_pluginList.count())
        return true;
    else
        return false;
}


void KNSPluginInstallEngine::startInstall(KNSPluginInfo info)
{
    m_toInstallPluginInfo = info;
    // create a temporary dowload file 
    KTempFile tempFile(locateLocal("tmp", "plugin") , QString(".tar.gz"));
    m_tmpPluginFileName = tempFile.name();
    tempFile.unlink();
    tempFile.close();
    // start the download job
    m_downloadJob  = KIO::copy(info.pluginURL(), "file://"+m_tmpPluginFileName, false );
    // connect signals 
    connect(m_downloadJob, SIGNAL(percent (KIO::Job *, unsigned long)), this , SLOT(slotDownLoadProgress(KIO::Job *, unsigned long)));
    connect(m_downloadJob, SIGNAL(result(KIO::Job *)), this, SLOT(slotDownloadResult(KIO::Job *)) );
    kdDebug(DEBUG_NUMBER) << "download plugin " << m_tmpPluginFileName << endl;
} 

void KNSPluginInstallEngine::slotDownLoadProgress(KIO::Job *, unsigned long percent)
{ 
    // propagate the download progression
    emit installProgress( ((int)percent)/3 );
}

void KNSPluginInstallEngine::slotDownloadResult(KIO::Job *job)
{ 
    // test if the download job suceed
    if(job->error()) {
        kdDebug(DEBUG_NUMBER) << "download error" << m_tmpPluginFileName << endl;
        emit installFailed();
     }
     else {
        kdDebug(DEBUG_NUMBER) << "download completed" << m_tmpPluginFileName << endl;
        // the download succeed copy the plugins files 
        
       // test the existance of the homedir
       QDir dir(QDir::homeDirPath());
       if(!dir.exists()) {
           emit installFailed();
           return;
        }

       // test and create firefox plugins directory
       if(!dir.exists(".mozilla"))
           dir.mkdir(".mozilla");
       if(!dir.exists(".mozilla/plugins"))
           dir.mkdir(".mozilla/plugins");
       // destination kurl
       KURL destURL("file://"+QDir::homeDirPath()+"/.mozilla/plugins");

       // construct the source kurlList
       KURL::List urlList;
       QStringList pluginFileList = m_toInstallPluginInfo.pluginFileList();

       QStringList::iterator it;
       for( it = pluginFileList.begin(); it != pluginFileList.end(); ++it ) {
           urlList.append( KURL("tar://"+m_tmpPluginFileName+"/"+(*it)) );
        }
       m_installFileJob  = KIO::copy(urlList , destURL, false );
       connect(m_installFileJob, SIGNAL(percent (KIO::Job *, unsigned long)), this , SLOT(slotCopyProgress(KIO::Job *, unsigned long)));
       connect(m_installFileJob, SIGNAL(result(KIO::Job *)), this, SLOT(slotCopyResult(KIO::Job *)) );
    }
    kdDebug(DEBUG_NUMBER) << "COPY FILE " << m_tmpPluginFileName << endl;

    // zero the download job pointer
    m_downloadJob = NULL;
}

void KNSPluginInstallEngine::slotCopyProgress(KIO::Job *, unsigned long percent)
{
    // propagate the download progression
    emit installProgress( ((int)percent)/3 + 33 );
} 
 
void KNSPluginInstallEngine::slotCopyResult(KIO::Job *job)
{
    // test if the download job suceed
    if(job->error()) {
        kdDebug(DEBUG_NUMBER) << "download error" << m_tmpPluginFileName << endl;
        emit installFailed();
    }
    else {
       // start the plugins scan
       m_scanProc = new QProcess( this );
       m_scanProc->addArgument( "nspluginscan" );
       m_scanProc->addArgument( "--verbose" );

       connect( m_scanProc, SIGNAL(readyReadStdout()),
               this, SLOT(readScanProcFromStdout()) );
       connect( m_scanProc, SIGNAL(processExited()),
               this, SLOT(endScanProc()) );
       if ( !m_scanProc->start() ) {
            emit installFailed();
       }
    }
}

void KNSPluginInstallEngine::readScanProcFromStdout()
{
    // Monitor the scan progress
    QString progress = m_scanProc->readLineStdout();
    int percent;
    bool ok;
    percent = progress.toInt(&ok);
    if(!ok)
        emit installFailed();
    emit installProgress( (percent)/3 + 66 );
}


void KNSPluginInstallEngine::endScanProc()
{
    // end of scan
    if(m_scanProc->normalExit()) {
        emit installProgress( 100 );
        emit installCompleted();
    } else
        emit installFailed();
}

KNSPluginWizard::KNSPluginWizard(QWidget *parent, const char *name, KMimeType::Ptr mime)
: KWizard(parent, name, true)
, m_installEngine(mime)
{
    setCaption(i18n("KDE plugin wizard"));
    setModal(true);

    // read the plugin installer configuration
    m_installEngine.pluginAvailable();

    // init the wizzard Pages
    initConfirmationPage();
    initLicencePage();
    initInstallationProgressPage();
    initFinishPage();
    initPagesButtonStates();

    // connect signals and slots
    connectSignals();

    //set correct default installation status
    m_installationComplete = false;

};


KNSPluginWizard::~KNSPluginWizard()
{
};

void KNSPluginWizard::initConfirmationPage() 
{

        m_confirmationVBox = new QVBox(this);
        new QLabel(i18n("The following plugins are available."), m_confirmationVBox);
        m_pluginListView = new KListView(m_confirmationVBox);        
        m_pluginListView->addColumn(i18n("Name"));
        m_pluginListView->setSelectionMode(QListView::Single);
        new QLabel(i18n("Click on next to install the selected plugin."), m_confirmationVBox);
        addPage (m_confirmationVBox, i18n("Plugin installation confirmation"));
        
        bool selected = false;
  
        // Fill the plugin list
        QValueList<KNSPluginInfo>::iterator it;
        QValueList<KNSPluginInfo> pluginList = m_installEngine.pluginList();
        for( it = pluginList.begin(); it != pluginList.end(); ++it ) {
            PluginListItem *item = new PluginListItem((*it) , m_pluginListView);
            if(!selected) {
                selected = true;
                m_pluginListView->setSelected(item, true);
            }
            kdDebug(DEBUG_NUMBER) << "New Plugin List item"<< endl;
            setNextEnabled(m_confirmationVBox, true);
        }
}

void KNSPluginWizard::initLicencePage()
{
    m_licenceVBox = new QVBox(this);
    m_licencePageLabel = new QLabel(m_licenceVBox);
    m_licencePageText = new KTextEdit(m_licenceVBox);
    m_licencePageText->setReadOnly(true);
    
    // invisible buttonGroup
    QButtonGroup *buttonGroup = new QButtonGroup(this);
    m_agreementButtonGroup = buttonGroup;
    buttonGroup->hide();
    buttonGroup->setExclusive(true);
    
    m_licencePageAgree = new QRadioButton ( i18n("I agree."), m_licenceVBox);
    
    m_licencePageDisagree = new QRadioButton ( i18n("I do not agree (plugin will not be installed)."), m_licenceVBox);

    buttonGroup->insert(m_licencePageAgree);
    buttonGroup->insert(m_licencePageDisagree);
    m_licencePageDisagree->setChecked(true);
    
    addPage (m_licenceVBox, i18n("Plugin licence"));


    connect(buttonGroup, SIGNAL(clicked(int)), this, SLOT(slotAgreementClicked(int)));
}

void KNSPluginWizard::initInstallationProgressPage() {

    m_installationProgressWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(m_installationProgressWidget);
    layout->addWidget(new QLabel(i18n("Installation in progress."), m_installationProgressWidget));
    layout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding ));
    m_installationProgressBar = new KProgress(m_installationProgressWidget);
    m_installationProgressBar->setTotalSteps(100);
    layout->addWidget(m_installationProgressBar);
    
    addPage( m_installationProgressWidget, i18n("Plugin installation"));
    
}

void KNSPluginWizard::initFinishPage()
{
    m_finishWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(m_finishWidget);
    layout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding ));
    m_finishLabel = new QLabel(m_finishWidget);
    layout->addWidget(m_finishLabel);
    layout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding ));
    
    addPage(m_finishWidget, i18n("Installation status"));
    
}


void KNSPluginWizard::initPagesButtonStates()
{
    // set buttons states for the confirmation page
    setNextEnabled(m_confirmationVBox, true);
    setFinishEnabled(m_confirmationVBox, false);
    setHelpEnabled(m_confirmationVBox, false);

    // set buttons states for the licence page
    setNextEnabled(m_licenceVBox    , false);
    setBackEnabled(m_licenceVBox  , false);
    setFinishEnabled(m_licenceVBox  , false);
    setHelpEnabled(m_licenceVBox    , false);
    
    // for the installation page
    setNextEnabled(m_installationProgressWidget     , false);
    setBackEnabled(m_installationProgressWidget     , false);
    setFinishEnabled(m_installationProgressWidget   , false);
    setHelpEnabled(m_installationProgressWidget     , false);

    // for the finish page 
    setNextEnabled(m_finishWidget     , false);
    setBackEnabled(m_finishWidget     , false);
    setFinishEnabled(m_finishWidget   , true);
    setHelpEnabled(m_finishWidget     , false);
}



void KNSPluginWizard::connectSignals() {
    connect(&m_installEngine, SIGNAL(installProgress(int)), m_installationProgressBar, SLOT(setProgress(int)) );
    connect(&m_installEngine, SIGNAL(installCompleted()), this, SLOT(slotInstallationCompleted()) );
     connect(&m_installEngine, SIGNAL(installFailed()), this, SLOT(slotInstallationFailed()) );
     

}

void KNSPluginWizard::showPage(QWidget *page)
{

    // if the licence page is shown set the label and the licence content
    if(page == m_licenceVBox && m_licencePageLabel->text().isEmpty()) {
        KNSPluginInfo info =  static_cast<PluginListItem *>(m_pluginListView->selectedItem())->pluginInfo();
        m_licencePageLabel->setText(i18n("To install ")+info.pluginName()+i18n(" you need to agree to the following"));
        QString licence;
        licence = info.licence();
        QString tmpFile;
        if(info.licenceURL().isValid()) 
            // retrieve the licence if we have an url
            if(KIO::NetAccess::download(info.licenceURL(), tmpFile, NULL)) {
                    QFile f(tmpFile);
                    if(f.open(IO_ReadOnly)) {
                        QTextStream stream(&f);
                        stream.setEncoding(QTextStream::UnicodeUTF8);
                        licence  = stream.read();
                        f.close();
                        KIO::NetAccess::removeTempFile(tmpFile);
                    }
             } 
        // else display the licence found in the xml config
        m_licencePageText->setText(licence);

    }
    
    // if the installation page is shown start the download
    if(page == m_installationProgressWidget) {
        KNSPluginInfo info =  static_cast<PluginListItem *>(m_pluginListView->selectedItem())->pluginInfo();
        m_installEngine.startInstall(info);

    }

    // If we must display the finish page
    if(page == m_finishWidget) {
        if(m_installationComplete)  {
            m_finishLabel->setText(i18n("Installation completed. Reload the page."));

        } else
            m_finishLabel->setText(i18n("Installation failed"));

    }

    
    KWizard::showPage(page);
}

int KNSPluginWizard::exec()
{
    if(!m_installEngine.pluginList().count())
        return QDialog::Rejected;

    return KWizard::exec();
}


bool KNSPluginWizard::pluginAvailable()
{
    return m_installEngine.pluginAvailable();
}

void KNSPluginWizard::slotAgreementClicked(int id)
{
    if( id == m_agreementButtonGroup->id(m_licencePageAgree) ) {
        setNextEnabled(m_licenceVBox, true);
   
    } else {
        setNextEnabled(m_licenceVBox, false);
    }
       
}

void KNSPluginWizard::slotInstallationCompleted() 
{
    m_installationComplete = true;
    // enable next button 
    setNextEnabled(m_installationProgressWidget, true);
    next();
}
void KNSPluginWizard::slotInstallationFailed()
{
    m_installationComplete = false;
    showPage(m_finishWidget);
}


// KNSPlugin info copy constructor

KNSPluginInfo::KNSPluginInfo()
{

}

// KNSPlugin info constructor par an xml dom fragment
KNSPluginInfo::KNSPluginInfo(QDomNode pluginNode)
{
    QDomElement e;
    QDomNode node;

    // Read plugin informations
    node = pluginNode.firstChild();
    while(!node.isNull()) {
        e = node.toElement();
        if( e.tagName() == "pluginname") {
            kdDebug(DEBUG_NUMBER) << "found name " << e.text() << endl;
            m_pluginName = e.text();
        }
        
        if( e.tagName() == "pluginurl") {
            kdDebug(DEBUG_NUMBER) << "found plugin url " << e.text() << endl;
            m_pluginURL = KURL(e.text());
        }

        if( e.tagName() == "licence") {
            kdDebug(DEBUG_NUMBER) << "found licence " << e.text() << endl;
            m_licence = e.text();
        }            
        
        if( e.tagName() == "licenceurl") {
            kdDebug(DEBUG_NUMBER) << "found licenceurl " << e.text() << endl;
            m_licenceURL = KURL(e.text());
        }            
        
        if( e.tagName() == "pluginfile") {
            kdDebug(DEBUG_NUMBER) << "found pluginfile " << e.text() << endl;
            m_pluginFileList.append(e.text());
        }
        node = node.nextSibling();
    }
}


KNSPluginInfo::~KNSPluginInfo()
{

}


bool KNSPluginInfo::isValid() const
{
    // tell if the pluginInfo is a valid One
    if( m_pluginName.isEmpty() || ( m_licence.isEmpty() && !m_licenceURL.isValid() ) || !m_pluginURL.isValid() || m_pluginFileList.empty() ) {
        kdDebug(DEBUG_NUMBER) << "invalid plugin info" << endl;
        return false;

    }
    
    else {

        kdDebug(DEBUG_NUMBER) << "valid plugin info" << endl;
        return true;
    }
}

// Accesors
QString KNSPluginInfo::pluginName() const
{
    return m_pluginName;
}

QString KNSPluginInfo::licence() const
{
    return m_licence;
}

KURL KNSPluginInfo::licenceURL() const
{
    return m_licenceURL;
}

KURL KNSPluginInfo::pluginURL() const
{
    return m_pluginURL;
}

const QStringList& KNSPluginInfo::pluginFileList() const
{
    return m_pluginFileList;
}
