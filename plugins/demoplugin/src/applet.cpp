#include "applet.h"

Applet::Applet(void)
{
}

Applet::~Applet(void)
{
}

void Applet::setWidget(QWidget* widget)
{
  Applet::setLayout(new QHBoxLayout());
  layout()->addWidget(widget);
}

void Applet::setLayout(QLayout* layout)
{
  QWidget::setLayout(layout);
  layout->setContentsMargins(2, 0, 2, 0);
}
