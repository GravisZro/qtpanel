#include "applicationsmenuapplet.h"

#include "standards.h"

DesktopEntryObject::DesktopEntryObject(const QString& path)
  : DesktopEntry(path)
{
  m_action = new QAction(nullptr);
  connect(m_action, SIGNAL(triggered()), this, SLOT(execute()));

  m_action->setIconText(Name());
  if(Icon().size())
  {
//    qDebug() << Icon() << QIcon::hasThemeIcon(Icon());
    m_action->setIcon(QIcon::fromTheme(Icon(), QIcon(Icon())));
  }
}

void DesktopEntryObject::execute(void)
{
  QStringList args = Exec().split(' ');
  QString process = args[0];
  args.removeAt(0);
  args.clear();
  QProcess::startDetached(process, args, qgetenv("HOME"));
}

//==============================================================

static QHash<const char*, const char*> menu_hash(void)
{
  QHash<const char*, const char*> a;
  a.insert("Utility"    , "Accessories");
  a.insert("Development", "Development");
  a.insert("Education"  , "Education"  );
  a.insert("Office"     , "Office"     );
  a.insert("Graphics"   , "Graphics"   );
  a.insert("AudioVideo" , "Multimedia" );
  a.insert("Video"      , "Multimedia" );
  a.insert("Audio"      , "Multimedia" );
  a.insert("Game"       , "Games"      );
  a.insert("Network"    , "Network"    );
  a.insert("System"     , "System"     );
  a.insert("Settings"   , "Settings"   );
  a.insert("Other"      , "Other"      );
  return a;
}

static const QHash<const char*, const char*> g_menu_names = menu_hash();

#define MENU_COUNT 11

static const char* g_menus[MENU_COUNT][2] = { { "Utility"    , "applications-accessories" },
                                              { "Development", "applications-development" },
                                              { "Education"  , "applications-science"     },
                                              { "Office"     , "applications-office"      },
                                              { "Graphics"   , "applications-graphics"    },
                                              { "AudioVideo" , "applications-multimedia"  },
                                              { "Game"       , "applications-games"       },
                                              { "Network"    , "applications-internet"    },
                                              { "System"     , "preferences-system"       },
                                              { "Settings"   , "preferences-desktop"      },
                                              { "Other"      , "applications-other"       } };

//==============================================================

ApplicationsMenuApplet::ApplicationsMenuApplet(void)
  : Applet()
{
  if(QIcon::themeName() == "hicolor" ||
     QIcon::themeName().isEmpty())
  {
    QIcon::setThemeName("nuvola"); // kde
    if(QIcon::fromTheme("start-here").isNull())
      QIcon::setThemeName("gnome"); // gnome
    if(QIcon::fromTheme("start-here").isNull())
      QIcon::setThemeName("hicolor"); // default
  }

  qDebug() << "using theme:" << QIcon::themeName();

//  QIcon::setThemeSearchPaths(CXDGDirs::iconDirectories());
  QPushButton* button = new QPushButton();
  button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
  button->setMenu(m_menu = new QMenu());
  button->setText("Applications");
  button->setIcon(QIcon::fromTheme("start-here").pixmap(button->height(), button->height()));
  setWidget(button);
}

ApplicationsMenuApplet::~ApplicationsMenuApplet(void)
{
  delete m_menu;
}

QVariant ApplicationsMenuApplet::defaultSettings(void)
{
  QVariantList list;

  for(int y = 0; y < MENU_COUNT; ++y)
    list << QVariant::fromValue<void*>(g_menus[y]);

  QDir dir;
  dir.setNameFilters(QStringList("*.desktop"));
  QStringList dirs = CXDGDirs::appDirectories();
  for(QStringList::const_iterator pos = dirs.begin(); pos != dirs.end(); ++pos)
  {
    dir.setPath(*pos);
    QStringList files = dir.entryList(QDir::Files);
    for(QStringList::const_iterator pos2 = files.begin(); pos2 != files.end(); ++pos2)
    {
      DesktopEntryObject* de = new DesktopEntryObject(dir.absoluteFilePath(*pos2));
      de->Action()->setIcon(de->Action()->icon().pixmap(m_menu->height(),m_menu->height())); // resize icon
      m_entries.push_back(de);
    }
  }

  return QVariant::fromValue<QVariantList>(list);
}

bool ApplicationsMenuApplet::init(QWidget* parent)
{
  if(m_settings.type() == QVariant::List)
  {
    QVariantList list = m_settings.value<QVariantList>();

    while(!list.isEmpty())
    {
      const char** names = reinterpret_cast<const char**>(list.takeFirst().value<void*>());

      QMenu* menu = m_menu->addMenu(g_menu_names.value(names[0]));
      menu->setIcon(QIcon::fromTheme(names[1]).pixmap(menu->height(),menu->height()));
      m_menus.insert(g_menu_names.value(names[0]), menu);
    }

    QStringList categories;
    for(QList<DesktopEntryObject*>::iterator pos = m_entries.begin(); pos != m_entries.end(); ++pos)
    {
      if(m_menus.contains((*pos)->Category()))
        m_menus[(*pos)->Category()]->addAction((*pos)->Action());
      else
        m_menus["Other"]->addAction((*pos)->Action());
/*
      categories = (*pos)->Categories();
      for(QStringList::iterator pos2 = categories.begin(); pos2 != categories.end(); ++pos2)
        if(m_menus.contains(*pos2))
          m_menus[*pos2]->addAction((*pos)->Action());
*/
    }
  }

  m_menu->addSeparator();
  m_menu->addAction(QIcon::fromTheme("application-exit"), "Quit", qApp, SLOT(quit()));

/*
  connect(DesktopApplications::instance(), SIGNAL(applicationUpdated(const DesktopApplication&)), this, SLOT(onApplicationUpdated(const DesktopApplication&)));
  connect(DesktopApplications::instance(), SIGNAL(applicationRemoved(const QString&)), this, SLOT(onApplicationRemoved(const QString&)));

  QList<DesktopApplication> apps = DesktopApplications::instance()->applications();
  foreach(const DesktopApplication& app, apps)
    onApplicationUpdated(app);
*/

  return true;
}


/*
void ApplicationsMenuApplet::onApplicationUpdated(const DesktopApplication& app)
{
  onApplicationRemoved(app.path());

  if(app.isNoDisplay())
    return;

  QAction* action = new QAction(m_menu);
  action->setIconVisibleInMenu(true);
  action->setData(app.path());
  action->setText(app.name());
  action->setIcon(QIcon(QPixmap::fromImage(app.iconImage())));

  connect(action, SIGNAL(triggered()), this, SLOT(onActionTriggered()));

  // Add to relevant menu.
  int subMenuIndex = m_subMenus.size() - 1; // By default put it in "Other".
  for(int i = 0; i < m_subMenus.size() - 1; i++) // Without "Other".
  {
    if(app.categories().contains(m_subMenus[i].category()))
    {
      subMenuIndex = i;
      break;
    }
  }

  QMenu* menu = m_subMenus[subMenuIndex].menu();
  QList<QAction*> actions = menu->actions();
  QAction* before = nullptr;
  for(int i = 0; i < actions.size(); i++)
  {
    if(actions[i]->text().compare(action->text(), Qt::CaseInsensitive) > 0)
    {
      before = actions[i];
      break;
    }
  }

  if(menu->actions().isEmpty())
  {
    QList<QAction*> actions = m_menu->actions();
    QAction* before = nullptr;
    for(int i = 0; i < actions.size(); i++)
    {
      if(actions[i]->text().compare(menu->title(), Qt::CaseInsensitive) > 0)
      {
        before = actions[i];
        break;
      }
    }

    m_menu->insertMenu(before, menu);
  }

  menu->insertAction(before, action);


  m_actions[app.path()] = action;
}

void ApplicationsMenuApplet::onApplicationRemoved(const QString& path)
{
  if(m_actions.contains(path))
  {
    delete m_actions[path];
    m_actions.remove(path);
  }

  for(int i = 0; i < m_subMenus.size(); i++)
  {
    if(m_subMenus[i].menu()->actions().isEmpty())
      m_menu->removeAction(m_subMenus[i].menu()->menuAction());
  }
}
*/

Q_EXPORT_PLUGIN2(applicationsmenuplugin, ApplicationsMenuApplet);
