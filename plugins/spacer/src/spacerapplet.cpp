#include "spacerapplet.h"

SpacerApplet::SpacerApplet(void)
  : Applet()
{

}

SpacerApplet::~SpacerApplet(void)
{

}

QSize SpacerApplet::sizeHint(void) const
{
  return QSize(-1, -1);
}

Q_DECLARE_INTERFACE(SpacerApplet, "qpanel.spacerplugin")
