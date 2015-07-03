#include "demoplugin.h"

//#include <QtGui/QGraphicsScene>
//#include <QtGui/QGraphicsRectItem>
#include "panelwindow.h"

DemoApplet::DemoApplet(void)
  : Applet()
{
  m_rectItem = new QGraphicsRectItem(this);
  m_rectItem->setPen(QPen(Qt::NoPen));
  m_rectItem->setBrush(QBrush(Qt::blue));
}

DemoApplet::~DemoApplet(void)
{
  delete m_rectItem;
}

void DemoApplet::onLayoutChanged(void)
{
  static const int delta = 8;
  m_rectItem->setRect(delta, delta, m_size.width() - 2*delta, m_size.height() - 2*delta);
}

QSize DemoApplet::sizeHint(void) const
{
  return QSize(64, 64);
}

Q_DECLARE_INTERFACE(DemoApplet, "qpanel.plugin")
