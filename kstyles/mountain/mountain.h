/* Mountain Style for KDE3 */
#ifndef __mountain_style_h__
#define __mountain_style_h__

/* Qt */
#include <qframe.h>

/* KDE */
#include <kstyle.h>

/* Mountain */
#include "pixmaploader.h"

class QProgressBar;

namespace Mountain {
  class MountainStyle : public KStyle {
      Q_OBJECT

    public:
      MountainStyle();
      virtual ~MountainStyle();

      void renderMenuBlendPixmap(KPixmap& pix, const QColorGroup &cg, const QPopupMenu*) const;
      QPixmap stylePixmap(StylePixmap stylepixmap, const QWidget* widget, const QStyleOption& opt) const;

      void polish(QWidget* widget);
      void unPolish(QWidget* widget);
      void polish(QPalette&);
      void polish(QApplication *app);

      void drawKStylePrimitive(KStylePrimitive kpe,
                              QPainter* p,
                              const QWidget* widget,
                              const QRect& r,
                              const QColorGroup& cg,
                              SFlags flags = Style_Default,
                              const QStyleOption& = QStyleOption::Default) const;

      void drawPrimitive(PrimitiveElement pe,
                        QPainter* p,
                        const QRect& r,
                        const QColorGroup& cg,
                        SFlags flags = Style_Default,
                        const QStyleOption& = QStyleOption::Default) const;

      void drawControl(ControlElement element,
                      QPainter* p,
                      const QWidget* widget,
                      const QRect& r,
                      const QColorGroup& cg,
                      SFlags flags = Style_Default,
                      const QStyleOption& opt = QStyleOption::Default) const;

      void drawControlMask(ControlElement element,
                          QPainter* p,
                          const QWidget* widget,
                          const QRect& r,
                          const QStyleOption& opt = QStyleOption::Default) const;

      void drawComplexControl(ComplexControl control,
                              QPainter* p,
                              const QWidget* widget,
                              const QRect& r,
                              const QColorGroup& cg,
                              SFlags flags = Style_Default,
                              SCFlags controls = SC_All,
                              SCFlags active = SC_None,
                              const QStyleOption& = QStyleOption::Default) const;

      void drawComplexControlMask(ComplexControl control,
                                  QPainter* p,
                                  const QWidget* widget,
                                  const QRect& r,
                                  const QStyleOption& = QStyleOption::Default) const;

      int pixelMetric(PixelMetric m, const QWidget* widget = 0) const;

      QSize sizeFromContents(ContentsType contents,
                            const QWidget* widget,
                            const QSize& contentSize,
                            const QStyleOption& opt) const;

      SubControl querySubControl(ComplexControl control,
                                const QWidget* widget,
                                const QPoint& point,
                                const QStyleOption& opt = QStyleOption::Default) const;

      QRect querySubControlMetrics(ComplexControl control,
                                  const QWidget* widget,
                                  SubControl subcontrol,
                                  const QStyleOption& opt = QStyleOption::Default) const;

    private slots:
      //Animation slots.
      void updateProgressPos();
      void progressBarDestroyed(QObject* bar);

    private:

      bool isSizeConstrainedCombo(const QComboBox* combo) const;
      bool isFormWidget(const QWidget*   widget) const;

      ///Configuration settings
      bool animateProgressBar;
      bool highlightScrollBar;

      //Rendering flags
      mutable bool forceSmallMode;
      mutable bool maskMode;   //Ugly round trip flag to permit masking with little code;
      mutable bool formMode;   //Set when rendering form widgets

      mutable const QWidget* toolbarBlendWidget;  //Ditto for blending with toolbars

      enum TitleBarMode {
        None = 0,
        Regular,
        Maximized
      };

      mutable TitleBarMode titleBarMode; //Set when passing back CC_TilteBar modes to handle
      //PE_ButtonTool properly for them, as well as when handling CC_ToolButton from
      //The maximized window controls.

      mutable bool flatMode; //Set when calling PE_PushButton or PE_ButtonDefault
      // on a flat button.

      mutable bool customScrollMode; //Set when drawing scrollbars with custom colors.

      bool firstComboPopupRelease;

      //Animation support.
      QMap<QProgressBar*, int> progAnimWidgets;

      bool eventFilter(QObject* object, QEvent* event);

      Mountain::TilePainter::PaintMode pmode() const {
        if(formMode) {
          //If we're a form widget, we blend on painting, and consider ourselves
          //not to have a mask (so we don't get clipped to it)
          if(maskMode)
          { return Mountain::TilePainter::PaintTrivialMask; }
          else
          { return Mountain::TilePainter::PaintFullBlend; }
        } else {
          if(maskMode)
          { return Mountain::TilePainter::PaintMask; }
          else
          { return Mountain::TilePainter::PaintNormal; }
        }
      }

      Mountain::TilePainter::PaintMode pmodeFullBlend() const {
        return maskMode ? Mountain::TilePainter::PaintMask : Mountain::TilePainter::PaintFullBlend;
      }

      QWidget* hoverWidget;

      bool kickerMode;

      // For progress bar animation
      QTimer *animationTimer;

      QRect subRect(SubRect r, const QWidget *widget) const;

    private:
      // Disable copy constructor and = operator
      MountainStyle(const MountainStyle&);
      MountainStyle& operator=(const MountainStyle&);
  };
}; /* namespace Mountain */

#endif /* __mountain_style_h__ */

