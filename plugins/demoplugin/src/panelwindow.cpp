#include "panelwindow.h"

#include "x11core.h"
#include "pluginloader.h"

#include "xatoms.h"

#define DESKTOP_ALL (0xffffffff)

/*
#include "applicationsmenuapplet.h"
#include "dockapplet.h"
#include "trayapplet.h"
#include "clockapplet.h"
*/

PanelWindow::PanelWindow(Qt::Alignment alignment, Qt::Orientation orientation)
  : m_alignment(alignment),
    m_dockMode(false),
    m_orientation(orientation),
    m_layoutPolicy(FillSpace)
{
  setDockMode(true);
  m_layout = new QBoxLayout(orientation == Qt::Horizontal ? QBoxLayout::LeftToRight : QBoxLayout::TopToBottom);
  m_layout->setContentsMargins(0, 0, 0, 0);
//  m_layout->addSpacerItem(new QSpacerItem(1,1, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
  setLayout(m_layout);

  if(m_layoutPolicy == FillSpace)
  {
    if(orientation == Qt::Horizontal)
      setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
    else
      setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
  }

  //setOrientation(Qt::Vertical);
}

PanelWindow::~PanelWindow(void)
{
}

void PanelWindow::loadPlugin(const QString& name, const QVariant& settings)
{
  Applet* w = PluginLoader(name);

  if(w != nullptr)
  {
    m_applets.push_back(w);
    layout()->addWidget(w);
    w->load(settings);
    w->init(this);
    update();
  }
}

void PanelWindow::setDockMode(bool dockMode)
{
  m_dockMode = dockMode;

  setAttribute(Qt::WA_X11NetWmWindowTypeDock, m_dockMode);

  if(!m_dockMode)
  {
    // No need to reserve space anymore.
    X11Core::removeWindowProperty(winId(), _NET_WM_STRUT);
    X11Core::removeWindowProperty(winId(), _NET_WM_STRUT_PARTIAL);
  }

  // When in dock mode, panel should appear on all desktops.
  Atom desktop = m_dockMode ? DESKTOP_ALL : 0;
  X11Core::setWindowProperty<XA_CARDINAL>(winId(), _NET_WM_DESKTOP, desktop);

  updateLayout();
  updatePosition();
}

void PanelWindow::PanelWindow::setAlignment (Qt::Alignment alignment)
{
  m_alignment = alignment;
  updatePosition();
}

void PanelWindow::setOrientation(Qt::Orientation orientation)
{
  if(m_orientation != orientation)
  {
    m_orientation = orientation;
    resize(height(), width());
    emit orientationChanged(orientation);
  }
}

void PanelWindow::setLayoutPolicy(LayoutPolicy layoutPolicy)
{
  m_layoutPolicy = layoutPolicy;
  updateLayout();
}

void PanelWindow::updatePosition(void)
{
  if(!m_dockMode)
    return;

  int x = 0;
  int y = 0;

  _NET_WM_STRUT_PARTIAL_t screen;
  QRect screenGeometry = QApplication::desktop()->screenGeometry(X11Core::appScreen());

  if(m_alignment & Qt::AlignLeft)
    x = screenGeometry.left();
  else if(m_alignment & Qt::AlignRight)
    x = screenGeometry.right() - width() + 1;
  else //if(m_alignment & Qt::AlignHCenter)
    x = screenGeometry.center().x() - (width() / 2);

  if(m_alignment & Qt::AlignTop)
    y = screenGeometry.top();
  else if(m_alignment & Qt::AlignBottom)
    y = screenGeometry.bottom() - height() + 1;
  else //if(m_alignment & Qt::AlignVCenter)
    y = screenGeometry.center().y() - (height() / 2);

  move(x, y);

  // Update reserved space.

  if(m_orientation == Qt::Horizontal)
  {
    if(m_alignment & Qt::AlignTop)
    {
      screen.top       = height();
      screen.top_start = y;
      screen.top_end   = y + screen.top;
    }
    else if(m_alignment & Qt::AlignBottom)
    {
      screen.bottom       = height();
      screen.bottom_start = y;
      screen.bottom_end   = y + screen.bottom;
    }
    else if(m_alignment & Qt::AlignVCenter) { }
    else
      Q_ASSERT(false);
  }
  else if(m_orientation == Qt::Vertical)
  {
    if(m_alignment & Qt::AlignLeft)
    {
      screen.left        = width();
      screen.left_start  = x;
      screen.left_end    = x + screen.left;
    }
    else if(m_alignment & Qt::AlignRight)
    {
      screen.right       = width();
      screen.right_start = x;
      screen.right_end   = x + screen.right;
    }
    else if(m_alignment & Qt::AlignHCenter) { }
    else
      Q_ASSERT(false);
  }
  else
    Q_ASSERT(false);

  X11Core::setWindowProperty<XA_CARDINAL>(winId(), _NET_WM_STRUT_PARTIAL, screen);
  X11Core::setWindowProperty<XA_CARDINAL>(winId(), _NET_WM_STRUT, screen);

  // Update "blur behind" hint.
  Atom values[] = { 0, 0, width(), height() };
  X11Core::setWindowProperty<XA_CARDINAL>(winId(), _KDE_NET_WM_BLUR_BEHIND_REGION, values);
}

void PanelWindow::resizeEvent(QResizeEvent* event)
{
  updatePosition();
  updateLayout();
}

void PanelWindow::updateLayout()
{
  return;
  // TODO: Vertical orientation support.

  static const int spacing = 4;

  if(m_layoutPolicy != Normal && !m_dockMode)
  {
    int sh = 0;
    if(m_layoutPolicy == AutoSize)
    {
      for(int i = 0; i < m_applets.size(); i++)
      {
        if(m_applets[i]->sizeHint().width() >= 0)
          sh += m_applets[i]->sizeHint().width();
        else
          sh += 64; // Spacer applets don't really make sense on auto-size panel.
      }
      sh += spacing*(m_applets.size() - 1);
      if(sh < 0)
        sh = 0;
    }
    else if(m_layoutPolicy == FillSpace)
    {
      QRect screenGeometry = QApplication::desktop()->screenGeometry(X11Core::appScreen());
      sh = screenGeometry.width();
    }

    if(sh != width())
      resize(sh, height());
  }

  // Get total amount of space available for "spacer" applets (that take all available free space).
  int freeSpace = width() - spacing*(m_applets.size() - 1);
  int numSpacers = 0;
  for(int i = 0; i < m_applets.size(); i++)
  {
    if(m_applets[i]->sizeHint().width() >= 0)
      freeSpace -= m_applets[i]->sizeHint().width();
    else
      numSpacers++;
  }

  int spaceForOneSpacer = numSpacers > 0 ? (freeSpace / numSpacers) : 0;

  // Calculate rectangles for each applet.
  int spacePos = 0;
  for(int i = 0; i < m_applets.size(); i++)
  {
    QPoint appletPosition(spacePos, 0);
    QSize appletSize = m_applets[i]->sizeHint();

    if(appletSize.width() < 0)
    {
      if(numSpacers > 1)
      {
        appletSize.setWidth(spaceForOneSpacer);
        freeSpace -= spaceForOneSpacer;
        numSpacers--;
      }
      else
      {
        appletSize.setWidth(freeSpace);
        freeSpace = 0;
        numSpacers--;
      }
    }

    appletSize.setHeight(height());

    //m_applets[i]->setPos(appletPosition);
    //m_applets[i]->setSize(appletSize);

    spacePos += appletSize.width() + spacing;
  }
}

void PanelWindow::showPanelContextMenu(const QPoint& point)
{
  QMenu menu;
  menu.addAction(QIcon::fromTheme("application-exit"), "Quit panel", QApplication::instance(), SLOT(quit()));
  menu.exec(pos() + point);
}
