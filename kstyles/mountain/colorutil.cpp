/* Mountain Style for KDE3, color utility routines.. */

/* Qt */
#include <qcolor.h>

/* Mountain */
#include "colorutil.h"

namespace Mountain
{
  QColor ColorUtil::lighten(QColor in, int factor)
  {
    if (factor > 100)
    {
      int h, s, v;
      in.hsv(&h, &s, &v);

      float mShare = v/230.0;
      if (mShare > 1) mShare = 1;

      mShare *= mShare;

      int diff = factor - 100;
      int hd  = int(mShare*diff);
      int delta  =  int((diff - hd)*7.55);

      QColor wrk = in.light(100+hd);

      int r = wrk.red();
      int g = wrk.green();
      int b = wrk.blue();

      r+=delta;
      g+=delta;
      b+=delta;

      if (r>255) r=255;
      if (g>255) g=255;
      if (b>255) b=255;

      return QColor(r,g,b);
    }

    return in;
  }
}
