/* Mountain Style for KDE3, color utility routines... */

#ifndef __mountain_colorutil_h__
#define __mountain_colorutil_h__

class QPainter;

namespace Mountain
{
  class ColorUtil
  {
  public:
    static QColor lighten(QColor in, int factor);
  };
}

#endif /* __mountain_colorutil_h__ */
