#include "panelapplication.h"

PanelApplication::PanelApplication(int& argc, char** argv)
  : X11Core(argc, argv)
{
  setOrganizationName("X11CoreDesktop");
  setApplicationName("X11CorePanel");

  QString setting;
  int num_panels = m_settings.value("num_panels", 1).toInt();

  m_panelWindows.resize(num_panels);
  PanelWindow* panelWindow;

  for(int i = 0; i < num_panels; ++i)
  {
    setting = "panel_%1/%2";
    setting = setting.arg(i);
    panelWindow = m_panelWindows[i] = new PanelWindow();

    panelWindow->resize         (m_settings.value(setting.arg("width" ), QApplication::desktop()->screenGeometry().width()).toInt(),
                                 m_settings.value(setting.arg("height"), 16 ).toInt());
    panelWindow->setLayoutPolicy((PanelWindow::LayoutPolicy) m_settings.value(setting.arg("LayoutPolicy"), PanelWindow::FillSpace).toInt());
    panelWindow->setOrientation ((Qt::Orientation) m_settings.value(setting.arg("Orientation"), Qt::Horizontal).toInt());
    panelWindow->setDockMode    (m_settings.value(setting.arg("DockMode"), true).toBool());

    QStringList plugin_names;

    plugin_names.append(".shadow_build/libapplicationsmenuplugin.so");
    plugin_names.append(".shadow_build/libdockplugin.so");
    plugin_names.append(".shadow_build/libtrayplugin.so");
    plugin_names.append(".shadow_build/libclockplugin.so");

    plugin_names = m_settings.value(setting.arg("plugins/names"), plugin_names).toStringList();

    for(QStringList::const_iterator pos = plugin_names.begin(); pos != plugin_names.end(); ++pos)
      panelWindow->loadPlugin(*pos, m_settings.value(setting.arg("plugins/%1/settings").arg(*pos)));

    panelWindow->show();
  }
}

PanelApplication::~PanelApplication()
{
}
