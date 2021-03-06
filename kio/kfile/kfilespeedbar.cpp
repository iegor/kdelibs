/* This file is part of the KDE libraries
    Copyright (C) 2002 Carsten Pfeiffer <pfeiffer@kde.org>

    library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation, version 2.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "kfilespeedbar.h"
#include "config-kfile.h"

#include <qdir.h>
#include <qfile.h>
#include <qtextcodec.h>
#include <qtextstream.h>

#include <kconfig.h>
#include <kglobal.h>
#include <kglobalsettings.h>
#include <klocale.h>
#include <kprotocolinfo.h>
#include <kstandarddirs.h>
#include <kurl.h>

KFileSpeedBar::KFileSpeedBar( QWidget *parent, const char *name )
    : KURLBar( true, parent, name )
{
    KConfig *config = KGlobal::config();
    KConfigGroupSaver cs( config, ConfigGroup );
    m_initializeSpeedbar = config->readBoolEntry( "Set speedbar defaults",
                                                   true );
    setIconSize(KIcon::SizeSmallMedium);
    readConfig( KGlobal::config(), "KFileDialog Speedbar" );

    if ( m_initializeSpeedbar )
    {
        KURL u;
        u.setPath( KGlobalSettings::desktopPath() );
        insertItem( u, i18n("Desktop"), false );

//TODO: win32
        if ((KGlobalSettings::documentPath() != (QDir::homeDirPath()+"/")) &&
            QDir(KGlobalSettings::documentPath()).exists())
        {
            u.setPath( KGlobalSettings::documentPath() );
            insertItem( u, i18n("Documents"), false, "folder_txt" );
        }

        u.setPath( QDir::homeDirPath() );
        insertItem( u, i18n("Home Folder"), false,
                               "folder_home" );

        u = "media:/";
        if ( KProtocolInfo::isKnownProtocol( u ) )
            insertItem( u, i18n("Storage Media"), false,
                                   KProtocolInfo::icon( "media" ) );

        if (  QFile::exists(  QDir::homeDirPath()+"/.config/user-dirs.dirs" ) )
        {
			QString download, music, pictures, videos, templates, publicShares;

            QFile f(  QDir::homeDirPath()+"/.config/user-dirs.dirs" );
			if (!f.open(IO_ReadOnly))
				return;

			QTextStream s( &f );
			s.setCodec( QTextCodec::codecForLocale() );

			// read the xdg user dirs
			QString line = s.readLine();
			while (!line.isNull())
			{
				if (line.startsWith("XDG_DOWNLOAD_DIR="))
					download = line.remove("XDG_DOWNLOAD_DIR=").remove("\"").replace("$HOME", QDir::homeDirPath());
				else if (line.startsWith("XDG_MUSIC_DIR="))
					music = line.remove("XDG_MUSIC_DIR=").remove("\"").replace("$HOME", QDir::homeDirPath());
				else if (line.startsWith("XDG_PICTURES_DIR="))
					pictures = line.remove("XDG_PICTURES_DIR=").remove("\"").replace("$HOME", QDir::homeDirPath());
				else if (line.startsWith("XDG_VIDEOS_DIR="))
					videos = line.remove("XDG_VIDEOS_DIR=").remove("\"").replace("$HOME", QDir::homeDirPath());
				else if (line.startsWith("XDG_TEMPLATES_DIR="))
					templates = line.remove("XDG_TEMPLATES_DIR=").remove("\"").replace("$HOME", QDir::homeDirPath());
				else if (line.startsWith("XDG_PUBLICSHARES_DIR="))
					publicShares = line.remove("XDG_PUBLICSHARES_DIR=").remove("\"").replace("$HOME", QDir::homeDirPath());

				line = s.readLine();
			}
			// now add in the speedbar
			if (!download.isEmpty())
                insertItem( download, i18n( "Download" ), false, "folder_html" );
			if (!music.isEmpty())
                insertItem( music, i18n( "Music" ), false, "folder_sound" );
			if (!pictures.isEmpty())
                insertItem( pictures, i18n( "Pictures" ), false, "folder_image" );
			if (!videos.isEmpty())
                insertItem( videos, i18n( "Videos" ), false, "folder_video" );
			if (!templates.isEmpty())
                insertItem( templates, i18n( "Templates" ), false, "folder_video" );
			if (!publicShares.isEmpty())
                insertItem( publicShares, i18n( "Public" ), false, "folder_video" );
        }
        
        u = "remote:/";
        if ( KProtocolInfo::isKnownProtocol( u ) )
            insertItem( u, i18n("Network Folders"), false,
                                   KProtocolInfo::icon( "remote" ) );
    }
}

KFileSpeedBar::~KFileSpeedBar()
{
}

void KFileSpeedBar::save( KConfig *config )
{
    if ( m_initializeSpeedbar && isModified() )
    {
        KConfigGroup conf( config, ConfigGroup );
        // write to kdeglobals
        conf.writeEntry( "Set speedbar defaults", false, true, true );
    }

    writeConfig( config, "KFileDialog Speedbar" );
}

QSize KFileSpeedBar::sizeHint() const
{
    QSize sizeHint = KURLBar::sizeHint();
    int ems = fontMetrics().width("mmmmmmmmmmmm");
    if (sizeHint.width() < ems)
    {
        sizeHint.setWidth(ems);
    }
    return sizeHint;
}

#include "kfilespeedbar.moc"
