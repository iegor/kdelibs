/* Mountain Style for KDE3 */

/* Qt */
#include <qapplication.h>
#include <qbitmap.h>
#include <qglobal.h>
#include <qimage.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qpixmapcache.h>

/* Mountain */
#include "pixmaploader.h"
#include "pixmaps.mountain"

using namespace Mountain;

PixmapLoader* PixmapLoader::s_instance = 0;

PixmapLoader::PixmapLoader()
: m_pixmapCache(327680, 2017) {
  m_pixmapCache.setAutoDelete(true);

  for (int c=0; c<256; c++) { clamp[c]=static_cast<unsigned char>(c); }
  for (int c=256; c<540; c++) { clamp[c] = 255; }
}

void PixmapLoader::clear()
{
	//m_cache.clear();
}

QImage* PixmapLoader::getDisabled(int name, const QColor& color, const QColor& back, bool blend)
{
  MountainEmbedImage* edata = MountainGetDbImage(name);
  if (!edata)
    return 0;

  //Like getColored, but desaturate a bit, and lower gamma..

  //Create a real image...
  QImage* img = new QImage(edata->width, edata->height, 32);

  //OK, now, fill it in, using the color..
  Q_UINT32 r, g,b;
  Q_UINT32 i = qGray(color.rgb());
  r = (3*color.red()+i)>>2;
  g = (3*color.green()+i)>>2;
  b = (3*color.blue()+i)>>2;

  Q_UINT32 br = back.red(), bg = back.green(), bb = back.blue();

  if (edata->haveAlpha)
  {
    if (blend)
    {
      img->setAlphaBuffer(false);
      Q_UINT32* write = reinterpret_cast< Q_UINT32* >(img->bits() );
      int size = img->width()*img->height() * 3;

      for (int pos = 0; pos < size; pos+=3)
      {
        Q_UINT32 scale  = edata->data[pos];
        Q_UINT32 add    = (edata->data[pos+1]*i+127)>>8;
        Q_UINT32 alpha = edata->data[pos+2];
        Q_UINT32 destAlpha = 256 - alpha;

        Q_UINT32 rr = clamp[((r*scale+127)>>8) + add];
        Q_UINT32 rg = clamp[((g*scale+127)>>8) + add];
        Q_UINT32 rb = clamp[((b*scale+127)>>8) + add];

        *write =qRgb(((rr*alpha+127)>>8) + ((br*destAlpha+127)>>8),
                  ((rg*alpha+127)>>8) + ((bg*destAlpha+127)>>8),
                  ((rb*alpha+127)>>8) + ((bb*destAlpha+127)>>8));

        write++;
      }
    }
    else
    {
      img->setAlphaBuffer(true);
      Q_UINT32* write = reinterpret_cast< Q_UINT32* >(img->bits() );
      int size = img->width()*img->height() * 3;

      for (int pos = 0; pos < size; pos+=3)
      {
        Q_UINT32 scale  = edata->data[pos];
        Q_UINT32 add    = (edata->data[pos+1]*i+127)>>8;
        Q_UINT32 alpha = edata->data[pos+2];

        Q_UINT32 rr = clamp[((r*scale+127)>>8) + add];
        Q_UINT32 rg = clamp[((g*scale+127)>>8) + add];
        Q_UINT32 rb = clamp[((b*scale+127)>>8) + add];

        *write =qRgba(rr, rg, rb, alpha);

        write++;
      }

    }
  }
  else
  {
    img->setAlphaBuffer(false);
    Q_UINT32* write = reinterpret_cast< Q_UINT32* >(img->bits() );
    int size = img->width()*img->height() * 2;

    for (int pos = 0; pos < size; pos+=2)
    {
      Q_UINT32 scale  = edata->data[pos];
      Q_UINT32 add    = (edata->data[pos+1]*i+127)>>8;
      Q_UINT32 rr = clamp[((r*scale+127)>>8) + add];
      Q_UINT32 rg = clamp[((g*scale+127)>>8) + add];
      Q_UINT32 rb = clamp[((b*scale+127)>>8) + add];
      *write =qRgb(rr, rg, rb);
      write++;
    }
  }

  return img;
}

QImage* PixmapLoader::getColored(int name, const QColor& color, const QColor& back, bool blend)
{
  MountainEmbedImage* edata = MountainGetDbImage(name);
  if (!edata)
    return 0;

  //Create a real image...
  QImage* img = new QImage(edata->width, edata->height, 32);

  //OK, now, fill it in, using the color..
  Q_UINT32 r, g,b;
  r = color.red() + 2;
  g = color.green() + 2;
  b = color.blue() + 2;

  // int i = qGray(color.rgb());

  Q_UINT32 br = back.red(), bg = back.green(), bb = back.blue();

  if (edata->haveAlpha)
  {
    if (blend)
    {
      img->setAlphaBuffer(false);

      Q_UINT32* write = reinterpret_cast< Q_UINT32* >(img->bits() );
      int size = img->width()*img->height() * 3;
      for (int pos = 0; pos < size; pos+=3)
      {
        Q_UINT32 scale  = edata->data[pos];
        Q_UINT32 add    = edata->data[pos+1];
        Q_UINT32 alpha = edata->data[pos+2];
        Q_UINT32 destAlpha = 256 - alpha;

        if (scale != 0)
          add = add*5/4;

        Q_UINT32 rr = clamp[((r*scale+127)>>8) + add];
        Q_UINT32 rg = clamp[((g*scale+127)>>8) + add];
        Q_UINT32 rb = clamp[((b*scale+127)>>8) + add];

        *write =qRgb(((rr*alpha+127)>>8) + ((br*destAlpha+127)>>8),
                  ((rg*alpha+127)>>8) + ((bg*destAlpha+127)>>8),
                  ((rb*alpha+127)>>8) + ((bb*destAlpha+127)>>8));

        write++;
      }
    }
    else
    {
      img->setAlphaBuffer(true);

      Q_UINT32* write = reinterpret_cast< Q_UINT32* >(img->bits() );
      int size = img->width()*img->height() * 3;

      for (int pos = 0; pos < size; pos+=3)
      {
        Q_UINT32 scale  = edata->data[pos];
        Q_UINT32 add    = edata->data[pos+1];
        Q_UINT32 alpha = edata->data[pos+2];
        if (scale != 0)
          add = add*5/4;

        Q_UINT32 rr = clamp[((r*scale+127)>>8) + add];
        Q_UINT32 rg = clamp[((g*scale+127)>>8) + add];
        Q_UINT32 rb = clamp[((b*scale+127)>>8) + add];

        *write =qRgba(rr, rg, rb, alpha);
        write++;
      }
    }
  }
  else
  {
    img->setAlphaBuffer(false);

    Q_UINT32* write = reinterpret_cast< Q_UINT32* >(img->bits() );
    int size = img->width()*img->height() * 2;

    for (int pos = 0; pos < size; pos+=2)
    {
      Q_UINT32 scale  = edata->data[pos];
      Q_UINT32 add    = edata->data[pos+1];
      if (scale != 0)
        add = add*5/4;

      Q_UINT32 rr = clamp[((r*scale+127)>>8) + add];
      Q_UINT32 rg = clamp[((g*scale+127)>>8) + add];
      Q_UINT32 rb = clamp[((b*scale+127)>>8) + add];


      *write =qRgb(rr, rg, rb);
      write++;
    }
  }

  return img;
}

QPixmap PixmapLoader::pixmap( int name, const QColor& color, const QColor& bg, bool disabled, bool blend ) {
  return scale(name, 0, 0, color, bg, disabled, blend);
}


QPixmap PixmapLoader::scale( int name, int width, int height, const QColor& color,  const QColor& bg, bool disabled, bool blend ) {
  MountainCacheEntry entry(name, color, bg, disabled, blend, width, height);
  MountainCacheEntry* cacheEntry;

  int key = entry.key();

  if ((cacheEntry = m_pixmapCache.find(key, true)))
  {
    if (entry == *cacheEntry) //True match!
      return *cacheEntry->m_pixmap;
    else //Remove old entry in case of a conflict!
      m_pixmapCache.remove(key);
  }


  QImage* img = 0;
  QPixmap* result = 0;

  if (disabled)
    img = getDisabled(name, color, bg, blend);
  else
    img = getColored(name, color, bg, blend);

  if (!img)
  {
    MountainCacheEntry* toAdd = new MountainCacheEntry(entry);
    toAdd->m_pixmap = new QPixmap();
    m_pixmapCache.insert(key, toAdd, 16);
    return QPixmap();
  }

  if (width == 0 && height == 0)
    result = new QPixmap(*img);
  else
    result = new QPixmap(img->smoothScale( width ? width : img->width(),
                          height ? height: img->height()));
  delete img;

  MountainCacheEntry* toAdd = new MountainCacheEntry(entry);
  toAdd->m_pixmap = result;

  if (!m_pixmapCache.insert(key, toAdd, result->width()*result->height()*result->depth()/8)) {
    QPixmap toRet = *result;
    delete toAdd;
    return toRet;
  }

  return *result;
}

QSize PixmapLoader::size( int id ) {
  MountainEmbedImage* edata = MountainGetDbImage(id);
  if (!edata)
    return QSize(0,0);
  return QSize(edata->width, edata->height);
}

void TilePainter::draw( QPainter *p, int x, int y, int width, int height, const QColor& color, const QColor& bg, bool disabled, PaintMode mode ) {
  if (mode == PaintTrivialMask)
  {
    p->fillRect(x, y, width, height, Qt::color1);
    return;
  }

  bool swBlend = (mode != PaintFullBlend);
  unsigned int scaledColumns = 0, scaledRows = 0, lastScaledColumn = 0, lastScaledRow = 0;
  int scaleWidth = width, scaleHeight = height;

  //scaleWidth, scaleHeight are calculated to contain the area available
  //for all tiled and stretched columns/rows respectively.
  //This is need to redistribute the area remaining after painting
  //the "fixed" elements. We also keep track of the last col and row
  //being scaled so rounding errors don't cause us to be short a pixel or so.
  for ( unsigned int col = 0; col < columns(); ++col )
    if ( columnMode( col ) != Fixed )
    {
      scaledColumns++;
      lastScaledColumn = col;
    }
    else scaleWidth -= PixmapLoader::the().size (absTileName( col, 0 ) ).width();

  for ( unsigned int row = 0; row < rows(); ++row )
    if ( rowMode( row ) != Fixed )
    {
      scaledRows++;
      lastScaledRow = row;
    }
    else scaleHeight -= PixmapLoader::the().size (absTileName( 0, row ) ).height();


  if ( scaleWidth < 0 ) scaleWidth = 0;
  if ( scaleHeight < 0 ) scaleHeight = 0;


  int ypos = y;

  //Center vertically if everything is fixed but there is extra room remaining
  if ( scaleHeight && !scaledRows )
    ypos += scaleHeight / 2;

  for ( unsigned int row = 0; row < rows(); ++row )
  {
    int xpos = x;

    //Center horizontally if extra space and no where to redistribute it to...
    if ( scaleWidth && !scaledColumns )
      xpos += scaleWidth / 2;

    //If not fixed vertically, calculate our share of space available
    //for scalable rows.
    int h = rowMode( row ) == Fixed ? 0 : scaleHeight / scaledRows;

    //Redistribute any "extra" pixels to the last scaleable row.
    if ( scaledRows && row == lastScaledRow )
    {
      int allocatedEvenly = scaleHeight / scaledRows * scaledRows;
      h += scaleHeight - allocatedEvenly;
    }


    //If we're fixed, get the height from the pixmap itself.
    int realH = h ? h : PixmapLoader::the().size (absTileName( 0, row ) ).height();

    //Skip non-fitting stretched/tiled rows, too.
    if (rowMode( row ) != Fixed && h == 0)
      continue;


    //Set h to 0 to denote that we aren't scaling
    if ( rowMode( row ) == Tiled )
      h = 0;

    for ( unsigned int col = 0; col < columns(); ++col )
    {
      //Calculate width for rows that aren't fixed.
      int w = columnMode( col ) == Fixed ? 0 : scaleWidth / scaledColumns;

      //Get the width of the pixmap..
      int tileW = PixmapLoader::the().size (absTileName( col, row ) ).width();

      //Redistribute any extra pixels..
      if ( scaledColumns && col == lastScaledColumn ) w += scaleWidth - scaleWidth / scaledColumns * scaledColumns;

      //The width to use...
      int realW = w ? w : tileW;

      //Skip any non-fitting stretched/tiled columns
      if (columnMode( col ) != Fixed && w == 0)
        continue;

      //Set w to 0 to denote that we aren't scaling
      if ( columnMode( col ) == Tiled )
        w = 0;

      //If we do indeed have a pixmap..
      if ( tileW )
      {
        //If scaling in either direction.
        if ( w || h )
        {
          if (mode != PaintMask)
          {
            p->drawTiledPixmap( xpos, ypos, realW, realH, scale( col, row, w, h, color, bg, disabled, swBlend ) );
          }
          else
          {
            const QBitmap* mask  = scale( col, row, w, h, color,  bg, disabled, false ).mask();
            if (mask)
            {
              p->setBackgroundColor(Qt::color0);
              p->setPen(Qt::color1);
              p->drawTiledPixmap( xpos, ypos, realW, realH, *mask);
            }
            else
              p->fillRect ( xpos, ypos, realW, realH, Qt::color1);
          }
        }
        else
        {
          //Tiling (or fixed, the same really)
          if (mode != PaintMask)
          {
            p->drawTiledPixmap( xpos, ypos, realW, realH, tile( col, row, color, bg, disabled, swBlend ) );
          }
          else
          {
            const QBitmap* mask = tile( col, row, color, bg, disabled, false ).mask();
            if (mask)
            {
              p->setBackgroundColor(Qt::color0);
              p->setPen(Qt::color1);
              p->drawTiledPixmap( xpos, ypos, realW, realH, *mask);
            }
            else
              p->fillRect ( xpos, ypos, realW, realH, Qt::color1);

          }
        }
      }

      //Advance horizontal position
      xpos += realW;
    }

    //Advance vertical position
    ypos += realH;
  }
}

RectTilePainter::RectTilePainter( int name,
                                  bool scaleH, bool scaleV,
                                  unsigned int columns, unsigned int rows )
: TilePainter( name )
, m_scaleH( scaleH )
, m_scaleV( scaleV ) {
  m_columns =  columns;
  m_rows       = rows;

  TileMode mh = m_scaleH ? Scaled : Tiled;
  TileMode mv = m_scaleV ? Scaled : Tiled;
  for (int c=0; c<4; c++)
  {
    if (c != 1)
      colMde[c] = Fixed;
    else
      colMde[c] = mh;
  }

  for (int c=0; c<4; c++)
  {
    if (c != 1)
      rowMde[c] = Fixed;
    else
      rowMde[c] = mv;
  }
}

int RectTilePainter::tileName( unsigned int column, unsigned int row ) const {
  return row *3 +  column;
}

ActiveTabPainter::ActiveTabPainter( bool bottom )
: RectTilePainter( bottom? mountain_tab_bottom_active: mountain_tab_top_active, false)
, m_bottom( bottom ) {
  m_rows = 2;
  if(m_bottom) {
    rowMde[0] = rowMde[2] = rowMde[3] = Scaled;
    rowMde[1] = Fixed;
  }
  else {
    rowMde[0] = rowMde[2] = rowMde[3] = Fixed;
    rowMde[1] = Scaled;
  }
}

int ActiveTabPainter::tileName( unsigned int column, unsigned int row ) const {
  if ( m_bottom ) { return RectTilePainter::tileName( column, row + 1 ); }
  return RectTilePainter::tileName( column, row );
}

InactiveTabPainter::InactiveTabPainter( Mode mode, bool bottom )
	: RectTilePainter( bottom? mountain_tab_bottom_inactive: mountain_tab_top_inactive, false),
	  m_mode( mode ), m_bottom( bottom )
{
	m_rows = 2;
	if (m_bottom)
	{
		rowMde[0] = Scaled;
		rowMde[1] = Fixed;
	}
	else
	{
		rowMde[0] = Fixed;
		rowMde[1] = Scaled;
	}

	/**
	 Most fully, inactive tabs look like this:
	 L  C  R
	 / --- \
	 | === |

	 Where L,C, and R denote the tile positions. Of course, we don't want to draw all of the rounding for all the tabs.

	 We want the left-most tab to look like this:

	 L C
	 / --
	 | ==

	 "Middle" tabs look like this:

	 L C
	 | --
	 | ==

	 And the right most tab looks like this:

	 L C  R
	 | -- \
	 | == |

	So we have to vary the number of columns, and for everything but left-most tab, the L tab gets the special separator
	tile.
    */

	Mode rightMost = QApplication::reverseLayout() ? First : Last;
	m_columns = (m_mode == rightMost ? 3 : 2);
}

int InactiveTabPainter::tileName( unsigned int column, unsigned int row ) const
{
	Mode leftMost = QApplication::reverseLayout() ? Last : First;
	if ( column == 0 && m_mode != leftMost )
		return MountainTileSeparator;
	if ( m_bottom )
		return RectTilePainter::tileName( column, row + 1 );
	return RectTilePainter::tileName( column, row );
}

ScrollBarPainter::ScrollBarPainter( int type, int count, bool horizontal )
	: TilePainter( name( horizontal ) ),
	  m_type( type ),
	  m_count( count ),
	  m_horizontal( horizontal )
{
	for (int c=0; c<5; c++)
	{
		if ( !m_horizontal || !( c % 2 ) ) colMde[c] = Fixed;
		else colMde[c] =  Tiled;

		if ( m_horizontal || !( c % 2 ) ) rowMde[c] = Fixed;
		else rowMde[c] =  Tiled;
	}

	m_columns = m_horizontal ? m_count : 1;
	m_rows       = m_horizontal ? 1 : m_count;

}

int ScrollBarPainter::name( bool horizontal )
{
	return horizontal? mountain_scrollbar_hbar: mountain_scrollbar_vbar;
}

int ScrollBarPainter::tileName( unsigned int column, unsigned int row ) const
{
	unsigned int num = ( column ? column : row ) + 1;
	if ( m_count == 5 )
		if ( num == 3 ) num = 4;
		else if ( num == 4 ) num = 2;
		else if ( num == 5 ) num = 3;

	return m_type + (num-1)*16;
}

int SpinBoxPainter::tileName( unsigned int column, unsigned int ) const
{
	return column + 1;
}
