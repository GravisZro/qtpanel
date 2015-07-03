#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include <QtCore>
#include <applet.h>

Applet* PluginLoader(const QString& fileName)
{
  Applet* app = nullptr;

  try
  {
    if(!QLibrary::isLibrary(fileName))
      throw QString("loader: not a library");
    QPluginLoader loader;
    loader.setFileName(fileName);
    loader.load();
    if(!loader.isLoaded())
      throw loader.errorString();
    app = qobject_cast<Applet*>(loader.instance());
    if(!app)
      throw QString("loader: not an applet plugin");
    qDebug() << "successfully loaded" << fileName;
  }
  catch(QString err)
  {
    qDebug() << err;
    app = nullptr;
  }

  //Q_ASSERT(app);
  return app;
}

#endif // PLUGINLOADER_H
