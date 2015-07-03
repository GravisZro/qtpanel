#ifndef DEMOAPPLET_H
#define DEMOAPPLET_H

#include <QtGui>
#include "applet.h"


class DemoApplet: public Applet
{
  Q_OBJECT
  Q_INTERFACES(Applet)
public:
  DemoApplet(void);
  ~DemoApplet(void);

  QSize sizeHint(void) const;

protected:
  void onLayoutChanged(void);

private:
  QGraphicsRectItem* m_rectItem;
};

#endif
