#ifndef DOCKAPPLET_H
#define DOCKAPPLET_H

#include <applet.h>
#include <x11core.h>

#if 0
class DockApplet;
class Client;

// Represents a single item in a dock.
// There isn't one to one relationship between window (client) and dock item, that's why
// it's separate entity. One dock item can represent pinned launcher and one or more opened
// windows of that application.
class DockItem : public QGraphicsObject
{
  Q_OBJECT
public:
  DockItem(DockApplet* dockApplet);
  ~DockItem(void);

  void onUpdateContent(void);

  void addClient   (Client* client);
  void removeClient(Client* client);

  void setTargetPosition(const QPoint& targetPosition);
  void setTargetSize(const QSize& targetSize);
  void moveInstantly(void);
  void startAnimation(void);

  const QVector<Client*>& clients(void) const
  {
    return m_clients;
  }

  QRectF boundingRect(void) const;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

public slots:
  void animate();
  void close();

protected:
  void hoverEnterEvent  (QGraphicsSceneHoverEvent* event);
  void hoverLeaveEvent  (QGraphicsSceneHoverEvent* event);
  void mousePressEvent  (QGraphicsSceneMouseEvent* event);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
  void mouseMoveEvent   (QGraphicsSceneMouseEvent* event);

private:
  void updateClientsIconGeometry(void);
  bool isUrgent(void);

  QTimer* m_animationTimer;
  DockApplet* m_dockApplet;
  TextGraphicsItem* m_textItem;
  QGraphicsPixmapItem* m_iconItem;
  QVector<Client*> m_clients;
  QPoint m_position;
  QPoint m_targetPosition;
  QSize m_size;
  QSize m_targetSize;
  bool m_dragging;
  qreal m_highlightIntensity;
  qreal m_urgencyHighlightIntensity;
  QPoint m_mouseDownPosition;
  QPoint m_dragStartPosition;
};

// Used for tracking connected windows (X11 clients).
// Client may have it's DockItem, but not necessary (for example, special windows are not shown in dock).
class Client
{
public:
  Client(DockApplet* dockApplet, Atom handle);
  ~Client(void);

  inline       Atom     handle   (void) const { return m_handle  ; }
  inline       bool     isVisible(void) const { return m_visible ; }
  inline const QString& name     (void) const { return m_name    ; }
  inline const QIcon&   icon     (void) const { return m_icon    ; }
  inline       bool     isUrgent (void) const { return m_isUrgent; }

  void windowPropertyChanged(Atom atom);

private:
  void updateVisibility(void);
  void updateName(void);
  void updateIcon(void);
  void updateUrgency(void);

  DockApplet* m_dockApplet;
  Atom m_handle;
  QString m_name;
  QIcon m_icon;
  bool m_isUrgent;
  bool m_visible;
  DockItem* m_dockItem;
};
#endif

class CAdaptiveGridLayout : public QGridLayout
{
  Q_OBJECT
public:
  CAdaptiveGridLayout(void) : QGridLayout() { }

};

class CDockedWindow : public QPushButton
{
  Q_OBJECT
public:
  CDockedWindow(WId window, QWidget* parent = nullptr);
  ~CDockedWindow(void);

  bool operator== (const WId& window) const { return window == m_window; }

signals:
  void selfDestruct(WId window);

public slots:
  void onWindowPropertyChanged(Atom atom);

private slots:
  void onClicked      (void);
  void onUpdateWindow (void);
  void onContextMenu  (QPoint pos);
  void onMinimize     (void);
  void onMaximize     (void);
  void onUnMaximize   (void);
  void onActivate     (void);
  void onClose        (void);
  void onFullscreen   (void);

private:
  WId m_window;
  QTimer m_timer; // for urgent WM hint
  bool m_visible;
};

/*
class CDockModel : public QAbstractTableModel
{
  Q_OBJECT
public:
  CDockModel(QObject* parent = nullptr);
  ~CDockModel(void);

  QVariant data(const QModelIndex& index, int role) const;

private slots:
  void onWindowPropertyChanged(WId window, Atom atom);
  void onUpdateClientList(void);
  void onUpdateActiveWindow(void);

private:
  QHash<Atom, CDockedWindow*> m_windows;
  Atom m_active_window;
};
*/

class DockApplet: public Applet
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "QtPanel.Applet/1.0")
  Q_INTERFACES(Applet)
public:
  DockApplet(void);
  ~DockApplet(void);

//  QVariant data(const QModelIndex& index, int role) const;

private slots:
  void onWindowPropertyChanged(WId window, Atom atom);
  void onUpdateClientList(void);
  void onUpdateActiveWindow(void);

private:
  QHash<Atom, CDockedWindow*> m_windows;
  Atom m_active_window;

//  CDockModel* m_model;
};

#endif
