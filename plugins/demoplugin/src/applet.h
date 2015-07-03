#ifndef APPLET_H
#define APPLET_H

#include <QtGui>
#include <QtPlugin>

class Applet : public QWidget
{
  Q_OBJECT
public:
  Applet(void);
  ~Applet(void);

  virtual bool init(QWidget* parent) { return true; }

  inline void load(const QVariant& settings) { m_settings = settings.isNull() ? defaultSettings() : settings; }
  inline const QVariant& save(void) const { return m_settings; }

  void setWidget(QWidget* widget);
  void setLayout(QLayout* layout);

protected:
  virtual QVariant defaultSettings(void) { return QVariant(); };

  QVariant m_settings;
};

Q_DECLARE_INTERFACE(Applet, "QtPanel.Applet/1.0")

#endif
