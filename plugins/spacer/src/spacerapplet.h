#ifndef SPACERAPPLET_H
#define SPACERAPPLET_H

#include "applet.h"

class SpacerApplet: public Applet
{
  Q_OBJECT
  Q_INTERFACES(Applet)
public:
  SpacerApplet(void);
  ~SpacerApplet(void);

  QSize sizeHint(void) const;

protected slots:
    void onLayoutChanged(void) { }
};

#endif
