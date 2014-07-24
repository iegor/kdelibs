/* Keramik Style for KDE3, gradient routines */

#ifndef __mountain_gradients_h__
#define __mountain_gradients_h__

class QPainter;

namespace Mountain
{
  class GradientPainter
  {
  public:
    static void renderGradient( QPainter* p, const QRect& r, QColor cr,
              bool horizontal, bool menu = false,
              int px = 0, int py = 0, int pwidth = -1, int pheight = -1 );

    static void releaseCache();
  };
};

#endif /* __mountain_gradients_h__ */
