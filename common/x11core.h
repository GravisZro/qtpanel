#ifndef X11CORE_H
#define X11CORE_H

#include <stdint.h>
#include <QtGui>
#include <QtWidgets>
#include <QX11Info>

#include <X11/Xdefs.h>
#include <X11/Xatom.h>
#include <X11/extensions/Xcomposite.h>
#include <X11/extensions/Xdamage.h>
#include "xatoms.h"

//#define qX11App  reinterpret_cast<X11Core*>(qApp)

typedef QVector<Atom> AtomV;
typedef QList  <Atom> AtomL;

class X11Core : public QApplication
{
  Q_OBJECT
public:
  X11Core(int& argc, char** argv);
  ~X11Core(void);

  static inline int                appDpiX       (int screen = -1) { return QX11Info::appDpiX      (screen); }
  static inline int                appDpiY       (int screen = -1) { return QX11Info::appDpiY      (screen); }
  static inline unsigned long      appRootWindow (int screen = -1) { return QX11Info::appRootWindow(screen); }
  static inline int                appScreen     (void) { return QX11Info::appScreen     (); }
  static inline unsigned long      appTime       (void) { return QX11Info::appTime       (); }
  static inline unsigned long      appUserTime   (void) { return QX11Info::appUserTime   (); }
  static inline xcb_connection_t*  connection    (void) { return QX11Info::connection    (); }
  static inline Display*           display       (void) { return QX11Info::display       (); }
  static inline unsigned long      getTimestamp  (void) { return QX11Info::getTimestamp  (); }
  static inline bool               isPlatformX11 (void) { return QX11Info::isPlatformX11 (); }
  static inline void               setAppTime    (unsigned long time) { QX11Info::setAppTime     (time); }
  static inline void               setAppUserTime(unsigned long time) { QX11Info::setAppUserTime (time); }

  static inline X11Core* instance(void) { return reinterpret_cast<X11Core*>(QApplication::instance()); }

  bool x11EventFilter(XEvent* event);

  static WId rootWindow(void);
  static Atom atom(const char* name);

  template <Atom Atype, typename V> static void setWindowProperty (const WId window, const Atom type, const V& values);
  template <Atom Atype> static void  setWindowProperty     (const WId window, const Atom type, const AtomV& values);
  template <Atom Atype> static void  setWindowProperty     (const WId window, const Atom type, const Atom value);
  template <Atom Atype> static Atom  getWindowProperty     (const WId window, const Atom type, unsigned char** data);
  template <Atom Atype> static AtomV getWindowPropertyArray(const WId window, const Atom type);

  static void removeWindowProperty (                  const WId window, const Atom type);
  static Atom getWindowProperty    (const Atom Atype, const WId window, const Atom type, unsigned char** data);
/*
  static Atom    setWindowPropertyWindow       (const WId window, const Atom type, const Atom value);
  static AtomV   setWindowPropertyWindowArray  (const WId window, const Atom type, const Atom value);
  static AtomV   setWindowPropertyCardinalArray(const WId window, const Atom type, const Atom value);
  static AtomV   setWindowPropertyAtomArray    (const WId window, const Atom type, const Atom value);
  static QString setWindowPropertyUTF8String   (const WId window, const Atom type, const Atom value);
  static QString setWindowPropertyLatin1String (const WId window, const Atom type, const Atom value);
*/
  static Atom    getWindowPropertyWindow       (const WId window, const Atom type);
  static AtomV   getWindowPropertyWindowArray  (const WId window, const Atom type);
  static AtomV   getWindowPropertyCardinalArray(const WId window, const Atom type);
  static AtomV   getWindowPropertyAtomArray    (const WId window, const Atom type);
  static QString getWindowPropertyUTF8String   (const WId window, const Atom type);
  static QString getWindowPropertyLatin1String (const WId window, const Atom type);

  static QString getWindowName                 (const WId window);
  static QIcon   getWindowIcon                 (const WId window);
  static bool    getWindowUrgency              (const WId window);
  static QPixmap getWindowPixmap               (const WId window);

  static void registerForWindowPropertyChanges (const WId window);
  static void registerForTrayIconUpdates       (const WId window);

  static void activateWindow   (const WId window);
  static void minimizeWindow   (const WId window);
  static void maximizeWindow   (const WId window);
  static void unmaximizeWindow (const WId window);
  static void fullscreenWindow (const WId window);
  static void closeWindow      (const WId window);
  static void destroyWindow    (const WId window);
  static void redirectWindow   (const WId window);
  static void unredirectWindow (const WId window);
  static void resizeWindow     (const WId window, const int width, const int height);
  static void moveWindow       (const WId window, const int x, const int y);
  static void mapWindow        (const WId window);
  static void reparentWindow   (const WId window, const WId parent);

  static void killClient       (const WId window);
  static bool makeSystemTray   (const WId window);
  static void freeSystemTray   (void);
  static Atom getARGBVisualId  (void);

signals:
  void windowClosed         (const WId window);
  void windowReconfigured   (const WId window, const int x, const int y, const int width, const int height);
  void windowDamaged        (const WId window);
  void windowPropertyChanged(const WId window, const Atom type);
  void clientMessageReceived(const WId window, const Atom type, void* data);

private:
  Q_DISABLE_COPY(X11Core);

  static void sendNETWMMessage(const WId window,
                               const Atom type,
                               const long l0 = 0,
                               const long l1 = 0,
                               const long l2 = 0,
                               const long l3 = 0,
                               const long l4 = 0);

  static int m_damageEventBase;
};



inline WId X11Core::rootWindow(void)
{
  return QX11Info::appRootWindow();
}

template <Atom Atype, typename V>
inline void X11Core::setWindowProperty (const WId window, const Atom type, const V& values)
{
  XChangeProperty(QX11Info::display(), window, type, Atype, 32, PropModeReplace, reinterpret_cast<const unsigned char*>(&values), sizeof(values) / sizeof(Atom));
}

template <Atom Atype>
inline void X11Core::setWindowProperty(const WId window, const Atom type, const AtomV& values)
{
  XChangeProperty(QX11Info::display(), window, type, Atype, 32, PropModeReplace, reinterpret_cast<const unsigned char*>(values.data()), values.size());
}

template <Atom Atype>
inline void X11Core::setWindowProperty(const WId window, const Atom type, Atom value)
{
  XChangeProperty(QX11Info::display(), window, type, Atype, 32, PropModeReplace, reinterpret_cast<const unsigned char*>(&value), 1);
}

inline void X11Core::fullscreenWindow(const WId window)
{
  sendNETWMMessage(window, _NET_WM_STATE, True, _NET_WM_STATE_FULLSCREEN);
}

inline void X11Core::maximizeWindow(const WId window)
{
  sendNETWMMessage(window, _NET_WM_STATE, True, _NET_WM_STATE_MAXIMIZED_HORZ, _NET_WM_STATE_MAXIMIZED_VERT);
}

inline void X11Core::minimizeWindow(const WId window)
{
  sendNETWMMessage(window, _NET_WM_STATE, True, _NET_WM_STATE_HIDDEN);
  //XIconifyWindow(QX11Info::display(), window, QX11Info::appScreen());
}

inline void X11Core::closeWindow(const WId window)
{
  sendNETWMMessage(window, _NET_CLOSE_WINDOW, CurrentTime, 2);
}

inline void X11Core::destroyWindow(const WId window)
{
  XDestroyWindow(QX11Info::display(), window);
}

inline void X11Core::killClient(const WId window)
{
  XKillClient(QX11Info::display(), window);
}

inline void X11Core::freeSystemTray(void)
{
  XSetSelectionOwner(QX11Info::display(), _NET_SYSTEM_TRAY_SX, None, CurrentTime);
}

inline void X11Core::redirectWindow(const WId window)
{
  XCompositeRedirectWindow(QX11Info::display(), window, CompositeRedirectManual);
}

inline void X11Core::unredirectWindow(const WId window)
{
  XCompositeUnredirectWindow(QX11Info::display(), window, CompositeRedirectManual);
}

inline QPixmap X11Core::getWindowPixmap(const WId window)
{
  //return QPixmap::fromX11Pixmap(XCompositeNameWindowPixmap(QX11Info::display(), window));
  return QPixmap();
}

inline void X11Core::resizeWindow(const WId window, const int width, const int height)
{
  XResizeWindow(QX11Info::display(), window, width, height);
}

inline void X11Core::moveWindow(const WId window, const int x, const int y)
{
  XMoveWindow(QX11Info::display(), window, x, y);
}

inline void X11Core::mapWindow(const WId window)
{
  XMapWindow(QX11Info::display(), window);
}

inline void X11Core::reparentWindow(const WId window, const WId parent)
{
  XReparentWindow(QX11Info::display(), window, parent, 0, 0);
  XSync(QX11Info::display(), False);
}

inline void X11Core::registerForWindowPropertyChanges(const WId window)
{
  XSelectInput(QX11Info::display(), window, PropertyChangeMask);
}

inline void X11Core::registerForTrayIconUpdates(const WId window)
{
  XSelectInput (QX11Info::display(), window, StructureNotifyMask);
  XDamageCreate(QX11Info::display(), window, XDamageReportNonEmpty);
}

inline void X11Core::removeWindowProperty(const WId window, const Atom atom)
{
  XDeleteProperty(QX11Info::display(), window, atom);
}

#endif
