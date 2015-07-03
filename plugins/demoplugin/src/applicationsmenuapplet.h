#ifndef APPLICATIONSMENUAPPLET_H
#define APPLICATIONSMENUAPPLET_H

#include "applet.h"
#include "standards.h"

class DesktopEntryObject : public DesktopEntry
{
  Q_OBJECT
public:
  DesktopEntryObject(const QString& path);

  inline QAction* Action(void) const { return m_action; }

private slots:
  void execute(void);

private:
  QAction* m_action;
};


class ApplicationsMenuApplet : public Applet
{
  Q_OBJECT
  Q_INTERFACES(Applet)
public:
  ApplicationsMenuApplet(void);
 ~ApplicationsMenuApplet(void);

  bool init(QWidget* parent);

protected:
  void onLayoutChanged(void);
  bool isHighlighted(void);

  virtual QVariant defaultSettings(void);

private slots:
//  void onActionTriggered(void);
//  void onApplicationUpdated(const DesktopApplication& app);
//  void onApplicationRemoved(const QString& path);

private:
  QMenu* m_menu;
  QHash<QString, QMenu*> m_menus;
  QList<DesktopEntryObject*> m_entries;
};
#endif
