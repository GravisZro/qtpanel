#ifndef STANDARDS_H
#define STANDARDS_H

/*
 == SPECIFICATIONS ==
 base directories:  http://standards.freedesktop.org/basedir-spec/basedir-spec-0.6.html
 desktop entry:     http://standards.freedesktop.org/desktop-entry-spec/desktop-entry-spec-latest.html

 icon theme: http://standards.freedesktop.org/icon-theme-spec/icon-theme-spec-latest.html
 icon name:  http://standards.freedesktop.org/icon-naming-spec/icon-naming-spec-latest.html

 menu: http://standards.freedesktop.org/menu-spec/menu-spec-1.0.html
*/

#include <QtCore>

//=====================================================

class CXDGDirs
{
public:
  static const QString& ENV(const char* name, const QString default_value);
  static inline void flushCache(void) { s_cached.clear(); }

  static inline const QString&     cacheHome        (void) { return ENV("XDG_CACHE_HOME" , QDir::homePath() + "/.cache"      ); }
  static inline const QString&     configHome       (void) { return ENV("XDG_CONFIG_HOME", QDir::homePath() + "/.config"     ); }
  static inline const QString&     dataHome         (void) { return ENV("XDG_DATA_HOME"  , QDir::homePath() + "/.local/share"); }
  static inline const QStringList  dataDirectories  (void) { return ENV("XDG_DATA_DIRS"  , "/usr/local/share/:/usr/share/").split(':'); }
  static inline const QStringList  configDirectories(void) { return ENV("XDG_CONFIG_DIRS", "/etc/xdg"                     ).split(':'); }
  static        const QStringList& iconDirectories  (void);
  static        const QStringList& appDirectories   (void);

private:
  static QHash<const char*, QString> s_cached;
};

//=====================================================

class LocalizerHash : public QVariantHash
{
public:
  void insert(const QString& key, const QVariant& value);
//  LocalizerHash& operator =(const QVariantHash& other);
};

class LocalizedIniFile : public QSettings,
                         public LocalizerHash
{
public:
  LocalizedIniFile(const QString& path);
private:
  LocalizerHash parse(void);
};

//=====================================================

class DesktopEntry : public LocalizedIniFile
{
public:
  DesktopEntry(const QString& path);

  inline QString     Type           (void) const { return val<QString    >("Type"          ); }
  inline QString     Version        (void) const { return val<QString    >("Version"       ); }
  inline QString     Name           (void) const { return val<QString    >("Name"          ); }
  inline QString     GenericName    (void) const { return val<QString    >("GenericName"   ); }
  inline bool        NoDisplay      (void) const { return val<bool       >("NoDisplay"     ); }
  inline QString     Comment        (void) const { return val<QString    >("Comment"       ); }
  inline QString     Icon           (void) const { return val<QString    >("Icon"          ); }
  inline bool        Hidden         (void) const { return val<bool       >("Hidden"        ); }
  inline QStringList OnlyShowIn     (void) const { return val<QStringList>("OnlyShowIn"    ); }
  inline QStringList NotShowIn      (void) const { return val<QStringList>("NotShowIn"     ); }
  inline QString     TryExec        (void) const { return val<QString    >("TryExec"       ); }
  inline QString     Exec           (void) const { return val<QString    >("Exec"          ); }
  inline QString     Path           (void) const { return val<QString    >("Path"          ); }
  inline bool        Terminal       (void) const { return val<bool       >("Terminal"      ); }
  inline QStringList MimeType       (void) const { return val<QStringList>("MimeType"      ); }
  inline QStringList Categories     (void) const { return val<QStringList>("Categories"    ); }
  inline bool        StartupNotify  (void) const { return val<bool       >("StartupNotify" ); }
  inline QString     StartupWMClass (void) const { return val<QString    >("StartupWMClass"); }
  inline QUrl        URL            (void) const { return val<QUrl       >("URL"           ); }

  QString Category (void); // note: this returns the most popular major category from subcategories
                           //       see http://standards.freedesktop.org/menu-spec/menu-spec-1.0.html#category-registry

private:
  template <typename T> inline T val(const char* id) const { return m_values[id].value<T>(); }
  QVariantHash m_values;
  QString m_category;
};

#endif // STANDARDS_H
