/***************************************************************************
                          charcolumninterface.h  -  description
                             -------------------
    begin                : Fri Sep 12 2003
    copyright            : (C) 2003 by Friedrich W. H. Kossebau
    email                : Friedrich.W.H@Kossebau.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License version 2 as published by the Free Software Foundation.       *
 *                                                                         *
 ***************************************************************************/


#ifndef CHARCOLUMNINTERFACE_H
#define CHARCOLUMNINTERFACE_H

#include <qstring.h>

namespace KHE
{

/**
 * @short A simple interface for the access to the char column of a hex edit widget
 *
 * @author Friedrich W. H. Kossebau <Friedrich.W.H@Kossebau.de>
 * @see createBytesEditWidget(), charColumnInterface()
 * @since 3.2
 */
class CharColumnInterface
{
  public:
    /** encoding used to display the symbols in the text column */
    enum KEncoding
    {
      /** the encoding of your shell. If that is a multibyte encoding this will default to Latin1. */
      LocalEncoding=0,
      /** extended ASCII encoding, also known as Latin1 */
      ISO8859_1Encoding=1,
      /** @internal not implemented: the most common EBCDIC codepage */
      CECP1047Encoding=2,
      /** @internal enables extension without breaking binary compatibility */
      MaxEncodingId=0xFFFF
    };

  public: // set methods
    /** sets whether "unprintable" chars (value<32) should be displayed in the text column
      * with their corresponding character.
      * Default is @c false.
      * @param SU
      * @see showUnprintable()
      */
    virtual void setShowUnprintable( bool SU = true ) = 0;
    /** sets the substitute character for "unprintable" chars
      * Default is '.'.
      * @param SC new character
      * @see substituteChar()
      */
    virtual void setSubstituteChar( QChar SC ) = 0;
    /** sets the encoding of the text column.
      * If the encoding is not available the format will not be changed.
      * Default is @c LocalEncoding.
      * @param C the new encoding
      * @see encoding()
      */
    virtual void setEncoding( KEncoding C ) = 0;


  public: // get methods
    /** @return @c true if "unprintable" chars (value<32) are displayed in the text column
      * with their corresponding character, @c false otherwise
      * @see setShowUnprintable()
      */
    virtual bool showUnprintable() const = 0;
    /** @return the currently used substitute character for "unprintable" chars.
      * @see setSubstituteChar()
      */
    virtual QChar substituteChar() const = 0;
    /** @return the currently used encoding
      * @see setEncoding()
      */
    virtual KEncoding encoding()   const = 0;
};


/** tries to get the charcolumn interface of t
  * @return a pointer to the interface, otherwise 0
  * @author Friedrich W. H. Kossebau <Friedrich.W.H@Kossebau.de>
  * @since 3.2
  */
template<class T>
CharColumnInterface *charColumnInterface( T *t )
{
  if( !t )
    return 0;

  return static_cast<CharColumnInterface*>( t->qt_cast("KHE::CharColumnInterface") );
}

}

#endif
