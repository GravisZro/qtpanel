#ifndef CLOCKAPPLET_H
#define CLOCKAPPLET_H

#include <applet.h>

#include <QtGui>

class CCalendarWidget : public QMenu
{
  Q_OBJECT
public:
  CCalendarWidget(void) : QMenu()
  {
    setLayout(new QVBoxLayout());
    m_cal = new QCalendarWidget();
    layout()->addWidget(m_cal);
  }

  QCalendarWidget* m_cal;
};

class ClockApplet : public Applet
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "QtPanel.Applet/1.0")
  Q_INTERFACES(Applet)
public:
  ClockApplet(void);
  ~ClockApplet(void);

private slots:
  void open(void);
  void updateContent(void);

private:
  QPushButton* m_button;
  QTimer* m_timer;
  CCalendarWidget* m_calendar;
  QString m_output_format;
};



#endif
