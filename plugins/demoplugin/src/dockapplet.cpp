#include "dockapplet.h"
#include "xatoms.h"

#include "x11core.h"

#if 0

void DockItem::updateClientsIconGeometry(void)
{
  QPoint topLeft = m_dockApplet->mapToScene(QPointF(m_targetPosition)).toPoint();

  AtomV values;
  values.resize(4);
  //values[0] = static_cast<Atom>(topLeft.x()) + m_dockApplet->panelWindow()->pos().x();
  //values[1] = static_cast<Atom>(topLeft.y()) + m_dockApplet->panelWindow()->pos().y();
  values[2] = m_targetSize.width();
  values[3] = m_targetSize.height();
  for(int i = 0; i < m_clients.size(); i++)
  {
    X11Core::setWindowPropertyCardinalArray(m_clients[i]->handle(), _NET_WM_ICON_GEOMETRY, values);
  }
}

void Client::windowPropertyChanged(Atom atom)
{
  if(atom == _NET_WM_WINDOW_TYPE ||
     atom == _NET_WM_STATE)
  {
    AtomV windowTypes  = X11Core::getWindowPropertyAtomsArray(m_handle, _NET_WM_WINDOW_TYPE);
    AtomV windowStates = X11Core::getWindowPropertyAtomsArray(m_handle, _NET_WM_STATE);

    // Show only regular windows in dock.
    // When no window type is set, assume it's normal window.
    m_visible = (windowTypes.size() == 0) || (windowTypes.size() == 1 && windowTypes[0] == _NET_WM_WINDOW_TYPE_NORMAL);
    // Don't show window if requested explicitly in window states.
    if(windowStates.contains(_NET_WM_STATE_SKIP_TASKBAR))
      m_visible = false;

    if(m_dockItem == nullptr && m_visible)
    {
      m_dockItem = m_dockApplet->dockItemForClient(this);
      m_dockItem->addClient(this);
    }

    if(m_dockItem != nullptr && !m_visible)
    {
      m_dockItem->removeClient(this);
      m_dockItem = nullptr;
    }
  }

  if(atom == _NET_WM_VISIBLE_NAME ||
     atom == _NET_WM_NAME ||
     atom == WM_NAME)
  {
    m_name = X11Core::getWindowName(m_handle);
    if(m_dockItem != nullptr)
      m_dockItem->onUpdateContent();
  }

  if(atom == _NET_WM_ICON)
  {
    m_icon = X11Core::getWindowIcon(m_handle);
    if(m_dockItem != nullptr)
      m_dockItem->onUpdateContent();
  }

  if(atom == WM_HINTS)
  {
    m_isUrgent = X11Core::getWindowUrgency(m_handle);
    if(m_dockItem != nullptr)
      m_dockItem->startAnimation();
  }
}

#endif

/*
m_isUrgent = X11Core::getWindowUrgency(m_handle); // atom == WM_HINTS

X11Core::closeWindow(m_clients[i]->handle());
*/


CDockedWindow::CDockedWindow(WId window, QWidget* parent)
  : QPushButton(parent),
    m_window(window)
{
  setContextMenuPolicy(Qt::CustomContextMenu);

  connect(this, SIGNAL(clicked()), this, SLOT(onClicked()));
  connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onContextMenu(QPoint)));

  onUpdateWindow();
}

CDockedWindow::~CDockedWindow(void)
{
}

void CDockedWindow::onUpdateWindow(void)
{
  onWindowPropertyChanged(_NET_WM_WINDOW_TYPE);
  onWindowPropertyChanged(_NET_WM_STATE);
  onWindowPropertyChanged(_NET_WM_NAME);
  onWindowPropertyChanged(_NET_WM_ICON);
  onWindowPropertyChanged(WM_HINTS);
}

void CDockedWindow::onWindowPropertyChanged(Atom atom)
{
  if(atom == _NET_WM_WINDOW_TYPE)
    setVisible( m_visible =  X11Core::getWindowPropertyAtomArray(m_window, _NET_WM_WINDOW_TYPE).contains(_NET_WM_WINDOW_TYPE_NORMAL));
  else if(atom == _NET_WM_STATE)
    setVisible( m_visible = !X11Core::getWindowPropertyAtomArray(m_window, _NET_WM_STATE      ).contains(_NET_WM_STATE_SKIP_TASKBAR));
  else if(atom == _NET_WM_VISIBLE_NAME ||
          atom == _NET_WM_NAME ||
          atom == WM_NAME)
    setText(X11Core::getWindowName(m_window));
  else if(atom == _NET_WM_ICON)
    setIcon(X11Core::getWindowIcon(m_window));
  else if(atom == WM_HINTS)
  {
    bool isUrgent = X11Core::getWindowUrgency(m_window); // Windows blinks the window... perhaps bring it to the front?
  }
}

void CDockedWindow::onClicked(void)
{
  if(X11Core::getWindowPropertyAtomArray(m_window, _NET_WM_STATE).contains(_NET_WM_STATE_HIDDEN))
    onActivate();
  else
    onMinimize();
}

void CDockedWindow::onContextMenu(QPoint pos)
{
  QMenu menu;
  AtomV state = X11Core::getWindowPropertyAtomArray(m_window, _NET_WM_STATE);


//  _NET_WM_ACTION_CHANGE_DESKTOP

  if(!state.contains(_NET_WM_STATE_FULLSCREEN))
    menu.addAction("Fullscreen", this, SLOT(onFullscreen()));

  if(state.contains(_NET_WM_STATE_HIDDEN))
    menu.addAction("Restore", this, SLOT(onActivate()));
  else
    menu.addAction("Minimize", this, SLOT(onMinimize()));

  if(!state.contains(_NET_WM_STATE_MAXIMIZED_HORZ))
    menu.addAction("Maximize", this, SLOT(onMaximize()));

  menu.addSeparator();
  menu.addAction("Close", this, SLOT(onClose()));

  menu.exec(mapToGlobal(pos));
}

void CDockedWindow::onMinimize(void)
{
  X11Core::minimizeWindow(m_window);
}

void CDockedWindow::onMaximize(void)
{
  onActivate();
  X11Core::maximizeWindow(m_window);
}

void CDockedWindow::onActivate(void)
{
  X11Core::activateWindow(m_window);
}

void CDockedWindow::onClose(void)
{
  X11Core::closeWindow(m_window);
}

void CDockedWindow::onFullscreen(void)
{
  onActivate();
  X11Core::fullscreenWindow(m_window);
}


/*
CDockModel::CDockModel(QObject* parent)
  : QAbstractTableModel(parent)
{
  // Register for notifications about window property changes.
  connect(X11Core::instance(), SIGNAL(windowPropertyChanged(WId,Atom)), this, SLOT(onWindowPropertyChanged(WId,Atom)));
}

CDockModel::~CDockModel(void)
{

}

QVariant CDockModel::data(const QModelIndex& index, int role) const
{
  return QVariant();
}
*/

DockApplet::DockApplet(void)
  : Applet()
{
  setLayout(new QHBoxLayout());
  setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

  connect(X11Core::instance(), SIGNAL(windowPropertyChanged(WId,Atom)), this, SLOT(onWindowPropertyChanged(WId,Atom)));
}

DockApplet::~DockApplet(void)
{
}

void DockApplet::onUpdateActiveWindow(void)
{
  m_active_window = X11Core::getWindowPropertyWindow(X11Core::rootWindow(), _NET_ACTIVE_WINDOW);
  onUpdateClientList();
}

void DockApplet::onUpdateClientList(void)
{
  CDockedWindow* value;
  AtomL old_window_list = m_windows.keys(); // copy of the existing list of keys
  AtomV windows = X11Core::getWindowPropertyWindowArray(X11Core::rootWindow(), _NET_CLIENT_LIST);

  // add new windows
  for(AtomV::iterator pos = windows.begin(); pos != windows.end(); ++pos)
  {
    old_window_list.removeOne(*pos); // remove from the list of existing keys
    if(!m_windows.contains(*pos))
    {
      m_windows.insert(*pos, value = new CDockedWindow(*pos));
      layout()->addWidget(value);
    }
  }

  // remove all the no longer existant windows
  for(AtomL::iterator pos  = old_window_list.begin();
                      pos != old_window_list.end();
                      pos  = old_window_list.erase(pos))
  {
    value = m_windows.take(*pos);
    layout()->removeWidget(value);
    delete value;
  }
}

void DockApplet::onWindowPropertyChanged(WId window, Atom atom)
{
  if(window == X11Core::rootWindow())
  {
    if(atom == _NET_CLIENT_LIST)
      onUpdateActiveWindow();
    else if(atom == _NET_ACTIVE_WINDOW)
      onUpdateActiveWindow();
  }
  else if(m_windows.contains(window))
    m_windows[window]->onWindowPropertyChanged(atom);
}


Q_EXPORT_PLUGIN2(dockplugin, DockApplet);
