#include "clockapplet.h"

ClockApplet::ClockApplet(void)
  : Applet()
{
  m_output_format = "ddd MMM dd   h:mm ap";

  setWidget(m_button = new QPushButton(QDateTime::currentDateTime().toString(m_output_format)));
  m_button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);

  m_calendar = new CCalendarWidget();
  m_calendar->popup(QPoint(0 - m_calendar->width(), 0 - m_calendar->height()));
  m_calendar->hide();

  connect(m_button, SIGNAL(clicked()), this, SLOT(open()));



  m_timer = new QTimer(this);
  m_timer->setInterval(1000);
  m_timer->stop();
  connect(m_timer, SIGNAL(timeout()), this, SLOT(updateContent()));
  QTimer::singleShot(1000 - QDateTime::currentDateTime().time().msec(), m_timer, SLOT(start()));
}

ClockApplet::~ClockApplet(void)
{
}

void ClockApplet::open()
{
  QRect bar = parentWidget()->geometry();
  QRect screen(QApplication::desktop()->screenGeometry());
  QRect local(pos() + parentWidget()->pos(), size());
  QRect trans;

  // [0] == horizontal  [1] == common  [2] == vertical
  int xs[] = { width() - m_calendar->width(), 0, 0 - width() - m_calendar->width() };
  int ys[] = { height(), 0 - m_calendar->height(), 0 - height() };

  int start = 0;

  if(bar.width() > bar.height())
    bar.setWidth(screen.width());
  else
  {
    bar.setHeight(screen.height());
    start = 1; // adjust for vertical orientation
  }

  int end = start + 2;
  for(int x = start; x < end; ++x)
  {
    for(int y = start; y < end; ++y)
    {
      trans = local.translated(xs[x], ys[y]);
      if(screen.contains(trans) &&
        !bar.intersects(trans))
      {
        m_calendar->popup(trans.topLeft());
        return;
      }
    }
  }
}

void ClockApplet::updateContent(void)
{
  m_button->setText((QDateTime::currentDateTime().toString(m_output_format)));

}
