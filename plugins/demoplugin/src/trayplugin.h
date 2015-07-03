#ifndef TRAYAPPLET_H
#define TRAYAPPLET_H

#include "applet.h"

#include <X11/Xdefs.h>

class CWindowIcon : public QWidget
{
  Q_OBJECT
public:
  CWindowIcon(WId window, QWidget* parent = nullptr);
  ~CWindowIcon(void);

  QSize sizeHint(void) const { return QSize(m_size, m_size); }
  QSize size    (void) const { return sizeHint(); }

  void updateLayout(void);

  bool operator== (const WId& window) const { return window == m_window; }

public slots:
  void repaint(void);

protected:
  void paintEvent(QPaintEvent* event);

private slots:
  void onWindowDamaged(WId window);
  void onWindowReconfigured(WId window, int x, int y, int width, int height);

private:
  WId m_window;
  QPixmap m_pixmap;
  int m_size;
};

class TrayApplet: public Applet
{
  Q_OBJECT
  Q_INTERFACES(Applet)
public:
  TrayApplet(void);
  ~TrayApplet(void);

  bool init(QWidget* parent);

private slots:
  void onWindowClosed(WId window);
  void onClientMessageReceived(WId window, Atom atom, void* data);

  void updateLayout(void);

private:
  bool m_initialized;
  QList<CWindowIcon*> m_icons;
};

#endif
