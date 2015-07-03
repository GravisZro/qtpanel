#include "trayplugin.h"

#include <x11core.h>

#include <xatoms.h>


CWindowIcon::CWindowIcon(WId window, QWidget* parent)
  : QWidget(parent),
    m_window(window)
{
  QBoxLayout* box = qobject_cast<QBoxLayout*>(parent->layout());
  Q_ASSERT(box);

  m_size = box->direction() <= QBoxLayout::RightToLeft ? parentWidget()->height() : parentWidget()->width();

  X11Core::registerForTrayIconUpdates(window);
  X11Core::reparentWindow(window, parentWidget()->winId());
  X11Core::resizeWindow(window, m_size, m_size);
  X11Core::redirectWindow(window);
  X11Core::mapWindow(window);
  X11Core::registerForTrayIconUpdates(window);

  connect(X11Core::instance(), SIGNAL(windowDamaged(WId)),
          this               , SLOT(onWindowDamaged(WId)));

  connect(X11Core::instance(), SIGNAL(windowReconfigured(WId,int,int,int,int)),
          this               , SLOT(onWindowReconfigured(WId,int,int,int,int)));
}

CWindowIcon::~CWindowIcon(void)
{

}

void CWindowIcon::paintEvent(QPaintEvent* event)
{
  QPainter painter;
  painter.begin(this);
  painter.drawPixmap(0, 0, m_pixmap);
  painter.end();
}

void CWindowIcon::onWindowDamaged(WId window)
{
  if(window == m_window)
  {
    X11Core::moveWindow(m_window, pos().x(), pos().y());
    m_pixmap = X11Core::getWindowPixmap(m_window).scaled(size(), Qt::KeepAspectRatio);
    update();
  }
}

void CWindowIcon::onWindowReconfigured(WId window, int x, int y, int width, int height)
{

}

void CWindowIcon::updateLayout(void)
{
  QPoint point = mapToGlobal(pos());
  X11Core::moveWindow(m_window, point.x(), point.y());
}


TrayApplet::TrayApplet(void)
  : Applet(), m_initialized(false)
{
  setLayout(new QHBoxLayout());
}

TrayApplet::~TrayApplet(void)
{
  if(m_initialized)
    X11Core::freeSystemTray();
}

bool TrayApplet::init(QWidget* parent)
{
  if(!(m_initialized = X11Core::makeSystemTray(winId())))
    return false; // Another tray is active.

  connect(X11Core::instance(), SIGNAL(clientMessageReceived(WId,Atom,void*)),
          this               , SLOT(onClientMessageReceived(WId,Atom,void*)));

  connect(X11Core::instance(), SIGNAL(windowClosed(WId)),
          this               , SLOT(onWindowClosed(WId)));

  return true;
}

void TrayApplet::onClientMessageReceived(WId window, Atom atom, void* data)
{
  if(atom == _NET_SYSTEM_TRAY_OPCODE && reinterpret_cast<Atom*>(data)[1] == 0) // TRAY_REQUEST_DOCK
  {
    CWindowIcon* icon = new CWindowIcon(reinterpret_cast<Atom*>(data)[2], this);
    m_icons.push_back(icon);
    layout()->addWidget(icon);
  }
}

void TrayApplet::onWindowClosed(WId window)
{
  for(QList<CWindowIcon*>::iterator pos = m_icons.begin(); pos != m_icons.end(); pos++)
  {
    if(**pos == window)
    {
      layout()->removeWidget(*pos);
      delete *pos;
      m_icons.erase(pos);
      updateLayout();
      break;
    }
  }
}

void TrayApplet::updateLayout(void)
{
  for(QList<CWindowIcon*>::iterator pos = m_icons.begin(); pos != m_icons.end(); pos++)
    (*pos)->updateLayout();
}
