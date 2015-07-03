#include "standards.h"

QHash<const char*, QString> CXDGDirs::s_cached;

const QString& CXDGDirs::ENV(const char* name, const QString default_value)
{
  if(!s_cached.contains(name))
  {
    QByteArray arr = qgetenv(name);
    if(arr.isEmpty())
      s_cached.insert(name, QDir::toNativeSeparators(default_value));
    else
      s_cached.insert(name, QDir::toNativeSeparators(arr.data()));
  }

  return s_cached[name];
}

const QStringList& CXDGDirs::iconDirectories(void)
{
  static QStringList dirs;
  if(dirs.isEmpty())
  {
    dirs = dataDirectories();
    dirs.push_back(QDir::homePath() + "/.icons/");
    for(QStringList::iterator pos = dirs.begin(); pos != dirs.end(); ++pos)
      (*pos).append("icons/");
    dirs.push_back("/usr/share/pixmaps/");
  }
  return dirs;
}

const QStringList& CXDGDirs::appDirectories(void)
{
  static QStringList dirs;
  if(dirs.isEmpty())
  {
    dirs = dataDirectories();
    dirs.push_back(dataHome());
    for(QStringList::iterator pos = dirs.begin(); pos != dirs.end(); ++pos)
      (*pos).append("/applications/").replace("//", "/");
  }
  return dirs;
}

//=====================================================


void LocalizerHash::insert(const QString& key, const QVariant& value)
{
  static QString locale = QLocale::system().name();
  static QRegExp regex("([^\\[]+)\\[([^\\]]+)\\]");
  regex.indexIn(key);
  QString base = regex.cap(1);
  if(locale == regex.cap(2)) // exact locale found
    QVariantHash::insert(base, value);
  else if(base.isEmpty() && !contains(key)) // no locale specified
    QVariantHash::insert(key, value);
}

/*
LocalizerHash& LocalizerHash::operator =(const QVariantHash& other)
{
  QStringList k = other.keys();
  for(QStringList::const_iterator pos = k.begin(); pos != k.end(); ++pos)
    insert(*pos, value(*pos));
  return *this;
}
*/

LocalizedIniFile::LocalizedIniFile(const QString& path)
  : QSettings(path, QSettings::IniFormat),
    LocalizerHash(parse())
{
}

LocalizerHash LocalizedIniFile::parse(void) // parses recursively
{
  LocalizerHash hash;
  QStringList children = childKeys();
  for(QStringList::iterator pos = children.begin(); pos != children.end(); ++pos)
    hash.insert(*pos, QSettings::value(*pos));

  children = childGroups();
  for(QStringList::iterator pos = children.begin(); pos != children.end(); ++pos)
  {
    beginGroup(*pos);
    hash.insert(*pos, parse());
    endGroup();
  }

  return hash;
}

//=====================================================

QString DesktopEntry::Category(void)
{
  static QHash<QString, QString> aliases;

  if(!m_category.isEmpty())
    return m_category;

  if(aliases.isEmpty())
  {
    aliases.insert("Utility"           , "Accessories"     );
//  aliases.insert("Development"       , "Development"     );
//  aliases.insert("Education"         , "Education"       );
//  aliases.insert("Office"            , "Office"          );
//  aliases.insert("Graphics"          , "Graphics"        );
    aliases.insert("AudioVideo"        , "Multimedia"      );
    aliases.insert("Video"             , "Multimedia"      );
    aliases.insert("Audio"             , "Multimedia"      );
    aliases.insert("Game"              , "Games"           );
//  aliases.insert("Network"           , "Network"         );
//  aliases.insert("System"            , "System"          );
//  aliases.insert("Settings"          , "Settings"        );
//  aliases.insert("Other"             , "Other"           );

    aliases.insert("Building"          , "Development"     );
    aliases.insert("Debugger"          , "Development"     );
    aliases.insert("IDE"               , "Development"     );
    aliases.insert("GUIDesigner"       , "Development"     );
    aliases.insert("Profiling"         , "Development"     );
    aliases.insert("RevisionControl"   , "Development"     );
    aliases.insert("Translation"       , "Development"     );
    aliases.insert("Calendar"          , "Office"          );
    aliases.insert("ContactManagement" , "Office"          );
//  aliases.insert("Database"          , "Office"          );
    aliases.insert("Database"          , "Development"     );
//  aliases.insert("Database"          , "AudioVideo"      );
//  aliases.insert("Dictionary"        , "Office"          );
    aliases.insert("Dictionary"        , "TextTools"       );
    aliases.insert("Chart"             , "Office"          );
//  aliases.insert("Email"             , "Office"          );
    aliases.insert("Email"             , "Network"         );
    aliases.insert("Finance"           , "Office"          );
    aliases.insert("FlowChart"         , "Office"          );
    aliases.insert("PDA"               , "Office"          );
    aliases.insert("ProjectManagement" , "Office"          );
//  aliases.insert("ProjectManagement" , "Development"     );
    aliases.insert("Presentation"      , "Office"          );
    aliases.insert("Spreadsheet"       , "Office"          );
    aliases.insert("WordProcessor"     , "Office"          );
    aliases.insert("2DGraphics"        , "Graphics"        );
    aliases.insert("VectorGraphics"    , "2DGraphics"      );
    aliases.insert("RasterGraphics"    , "2DGraphics"      );
    aliases.insert("3DGraphics"        , "Graphics"        );
    aliases.insert("Scanning"          , "Graphics"        );
    aliases.insert("OCR"               , "Scanning"        );
    aliases.insert("Photography"       , "Graphics"        );
//  aliases.insert("Photography"       , "Office"          );
//  aliases.insert("Publishing"        , "Graphics"        );
    aliases.insert("Publishing"        , "Office"          );
    aliases.insert("Viewer"            , "Graphics"        );
    aliases.insert("Viewer"            , "Office"          );
    aliases.insert("TextTools"         , "Utility"         );
    aliases.insert("DesktopSettings"   , "Settings"        );
    aliases.insert("HardwareSettings"  , "Settings"        );
    aliases.insert("Printing"          , "HardwareSettings");
    aliases.insert("PackageManager"    , "Settings"        );
    aliases.insert("Dialup"            , "Network"         );
    aliases.insert("InstantMessaging"  , "Network"         );
    aliases.insert("Chat"              , "Network"         );
    aliases.insert("IRCClient"         , "Network"         );
    aliases.insert("FileTransfer"      , "Network"         );
//  aliases.insert("HamRadio"          , "Network"         );
    aliases.insert("HamRadio"          , "Audio"           );
    aliases.insert("News"              , "Network"         );
    aliases.insert("P2P"               , "Network"         );
    aliases.insert("RemoteAccess"      , "Network"         );
    aliases.insert("Telephony"         , "Network"         );
    aliases.insert("TelephonyTools"    , "Utility"         );
    aliases.insert("VideoConference"   , "Network"         );
    aliases.insert("WebBrowser"        , "Network"         );
//  aliases.insert("WebDevelopment"    , "Network"         );
    aliases.insert("WebDevelopment"    , "Development"     );
    aliases.insert("Midi"              , "Audio"           );
    aliases.insert("Mixer"             , "Audio"           );
    aliases.insert("Sequencer"         , "Audio"           );
    aliases.insert("Tuner"             , "AudioVideo"      );
    aliases.insert("TV"                , "Video"           );
    aliases.insert("AudioVideoEditing" , "AudioVideo"      );
    aliases.insert("Player"            , "Audio"           );
    aliases.insert("Player"            , "Video"           );
    aliases.insert("Player"            , "AudioVideo"      );
    aliases.insert("Recorder"          , "Audio"           );
    aliases.insert("Recorder"          , "Video"           );
    aliases.insert("Recorder"          , "AudioVideo"      );
    aliases.insert("DiscBurning"       , "AudioVideo"      );
    aliases.insert("ActionGame"        , "Game"            );
    aliases.insert("AdventureGame"     , "Game"            );
    aliases.insert("ArcadeGame"        , "Game"            );
    aliases.insert("BoardGame"         , "Game"            );
    aliases.insert("BlocksGame"        , "Game"            );
    aliases.insert("CardGame"          , "Game"            );
    aliases.insert("KidsGame"          , "Game"            );
    aliases.insert("LogicGame"         , "Game"            );
    aliases.insert("RolePlaying"       , "Game"            );
    aliases.insert("Simulation"        , "Game"            );
    aliases.insert("SportsGame"        , "Game"            );
    aliases.insert("StrategyGame"      , "Game"            );
    aliases.insert("Art"               , "Education"       );
    aliases.insert("Construction"      , "Education"       );
    aliases.insert("Music"             , "AudioVideo"      );
    aliases.insert("Music"             , "Education"       );
    aliases.insert("Languages"         , "Education"       );
    aliases.insert("Science"           , "Education"       );
//  aliases.insert("ArtificialIntelligence", "Science"     );
    aliases.insert("ArtificialIntelligence", "ComputerScience" ); // custom
    aliases.insert("Astronomy"         , "Science"         );
    aliases.insert("Biology"           , "Science"         );
    aliases.insert("Chemistry"         , "Science"         );
    aliases.insert("ComputerScience"   , "Science"         );
    aliases.insert("DataVisualization" , "Science"         );
    aliases.insert("Electricity"       , "Science"         );
    aliases.insert("Geography"         , "Education"       );
    aliases.insert("Geology"           , "Science"         );
    aliases.insert("Geoscience"        , "Science"         );
    aliases.insert("History"           , "Education"       );
//  aliases.insert("ImageProcessing"   , "Science"         );
    aliases.insert("ImageProcessing"   , "ComputerScience" ); // custom
    aliases.insert("Literature"        , "Education"       );
    aliases.insert("Math"              , "Science"         );
    aliases.insert("NumericalAnalysis" , "Math"            );
    aliases.insert("MedicalSoftware"   , "Science"         );
    aliases.insert("Physics"           , "Science"         );
    aliases.insert("Robotics"          , "Science"         );
    aliases.insert("Sports"            , "Education"       );
    aliases.insert("ParallelComputing" , "ComputerScience" );
    aliases.insert("Amusement"         , "Game"            ); // custom
    aliases.insert("Archiving"         , "Utility"         );
    aliases.insert("Compression"       , "Archiving"       );
    aliases.insert("Electronics"       , "Science"         ); // custom
    aliases.insert("Emulator"          , "System"          );
    aliases.insert("Emulator"          , "Game"            );
    aliases.insert("Engineering"       , "Science"         ); // custom
    aliases.insert("FileTools"         , "Utility"         );
    aliases.insert("FileTools"         , "System"          );
    aliases.insert("FileManager"       , "System"          );
    aliases.insert("FileManager"       , "FileTools"       );
    aliases.insert("TerminalEmulator"  , "System"          );
    aliases.insert("Filesystem"        , "System"          );
    aliases.insert("Monitor"           , "System"          );
    aliases.insert("Security"          , "Settings"        );
    aliases.insert("Security"          , "System"          );
    aliases.insert("Accessibility"     , "Settings"        );
    aliases.insert("Accessibility"     , "Utility"         );
    aliases.insert("Calculator"        , "Utility"         );
    aliases.insert("Clock"             , "Utility"         );
    aliases.insert("TextEditor"        , "Utility"         );
  }

  QStringList list = Categories();
  QHash<QString, int> counter;
  QList<int> counts;
  int high_val = 0;

  for(QStringList::iterator pos = list.begin(); pos != list.end(); ++pos)
  {
    while(aliases.contains(*pos)) { *pos = aliases.value(*pos); }
    counter[*pos] = counter.value(*pos, 0) + 1;
  }

  counts = counter.values();
  for(QList<int>::const_iterator pos = counts.begin(); pos != counts.end(); ++pos)
    if(*pos > high_val)
      high_val = *pos;

  m_category = counter.key(high_val);

  return m_category;
}


DesktopEntry::DesktopEntry(const QString& path)
  : LocalizedIniFile(path)
{
  m_values = LocalizerHash::value("Desktop Entry").value<QVariantHash>();

  if(!m_values.contains("NoDisplay"    )) { m_values.insert("NoDisplay"    , false); }
  if(!m_values.contains("Hidden"       )) { m_values.insert("Hidden"       , false); }
  if(!m_values.contains("Terminal"     )) { m_values.insert("Terminal"     , false); }
  if(!m_values.contains("StartupNotify")) { m_values.insert("StartupNotify", false); }

  if(m_values.contains("OnlyShowIn"))
    m_values["OnlyShowIn"] = m_values["OnlyShowIn"].toString().split(";", QString::SkipEmptyParts);

  if(m_values.contains("NotShowIn"))
    m_values["NotShowIn" ] = m_values["NotShowIn" ].toString().split(";", QString::SkipEmptyParts);

  if(m_values.contains("MimeType"))
    m_values["MimeType"  ] = m_values["MimeType"  ].toString().split(";", QString::SkipEmptyParts);

  if(m_values.contains("Categories"))
    m_values["Categories"] = m_values["Categories"].toString().split(";", QString::SkipEmptyParts);
}
