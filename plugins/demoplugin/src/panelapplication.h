#ifndef PANELAPPLICATION_H
#define PANELAPPLICATION_H

#include <QtGui>

#include "x11core.h"
#include "panelwindow.h"

class PanelApplication : public X11Core
{
  Q_OBJECT
public:
  PanelApplication(int& argc, char** argv);
  ~PanelApplication();

private:
  QSettings m_settings;
  QVector<PanelWindow*> m_panelWindows;
};

#endif
