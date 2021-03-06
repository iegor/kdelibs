/* This file is part of the KDE libraries
   Copyright (C) 2002 Joseph Wenninger <jowenn@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef __ktexteditor_documentinfointerface_h__
#define __ktexteditor_documentinfointerface_h__

class QString;
class QCString;

#include <kdelibs_export.h>

namespace KTextEditor
{

/**
 * This is an interface for accessing information about files open
 * in the Document, Plugin and PluginViewInterface classes.
 */
class KTEXTEDITOR_EXPORT DocumentInfoInterface
{
  friend class PrivateDocumentInterface;

  public:
    DocumentInfoInterface();
    virtual ~DocumentInfoInterface();

    virtual QString mimeType()=0;
    virtual long  fileSize()=0;
    virtual QString niceFileSize()=0;

    unsigned int documentInfoInterfaceNumber () const;
    
  protected:  
    void setDocumentInfoInterfaceDCOPSuffix (const QCString &suffix);  

  private:
    class PrivateDocumentInfoInterface *d;
    static unsigned int globalDocumentInfoInterfaceNumber;
    unsigned int myDocumentInfoInterfaceNumber;
};


}

#endif
