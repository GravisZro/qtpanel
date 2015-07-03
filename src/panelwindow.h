#ifndef PANELWINDOW_H
#define PANELWINDOW_H

#include <QtGui>
#include <applet.h>


class PanelWindow: public QWidget
{
  Q_OBJECT
public:
  enum LayoutPolicy
  {
    Normal,
    AutoSize,
    FillSpace
  };

  PanelWindow(Qt::Alignment alignment = Qt::AlignLeft | Qt::AlignBottom, Qt::Orientation orientation = Qt::Horizontal); // Qt::Vertical);
  ~PanelWindow(void);

  void loadPlugin(const QString& name, const QVariant& settings);

  void setAlignment   (Qt::Alignment alignment);
  void setDockMode    (bool dockMode);
  void setLayoutPolicy(LayoutPolicy layoutPolicy);
  void setOrientation (Qt::Orientation orientation);

  inline Qt::Alignment   alignment   (void) const { return m_alignment;    }
  inline bool            dockMode    (void) const { return m_dockMode;     }
  inline LayoutPolicy    layoutPolicy(void) const { return m_layoutPolicy; }
  inline Qt::Orientation orientation (void) const { return m_orientation;  }

signals:
  void orientationChanged(Qt::Orientation orientation);

protected:
  void resizeEvent(QResizeEvent* event);

private slots:
  void updatePosition(void);
  void updateLayout  (void);
  void showPanelContextMenu(const QPoint& point);

private:
  Qt::Alignment m_alignment;
  bool m_dockMode;
  Qt::Orientation m_orientation;
  LayoutPolicy m_layoutPolicy;

  QList<Applet*> m_applets;
  QBoxLayout* m_layout;
};

#endif
