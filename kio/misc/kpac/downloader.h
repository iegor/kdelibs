/* 
   Copyright (c) 2003 Malte Starostik <malte@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/


#ifndef KPAC_DOWNLOADER_H
#define KPAC_DOWNLOADER_H

#include <qobject.h>

#include <kurl.h>

namespace KIO { class Job; }

namespace KPAC
{
    class Downloader : public QObject
    {
        Q_OBJECT
    public:
        Downloader( QObject* );

        void download( const KURL& );
        const KURL& scriptURL() { return m_scriptURL; }
        const QString& script() { return m_script; }
        const QString& error() { return m_error; }

    signals:
        void result( bool );

    protected:
        virtual void failed();
        void setError( const QString& );

    private slots:
        void data( KIO::Job*, const QByteArray& );
        void result( KIO::Job* );

    private:
        QByteArray m_data;
        KURL m_scriptURL;
        QString m_script;
        QString m_error;
    };
}

#endif // KPAC_DOWNLOADER_H

// vim: ts=4 sw=4 et
