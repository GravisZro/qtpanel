#include "x11core.h"

//#include <QtGui/QImage>
//#include <QtGui/QX11Info>


// Keep all the X11 stuff with scary defines below normal headers.
#include <X11/Xlib.h>
#include <X11/Xutil.h>

static XErrorHandler oldX11ErrorHandler = nullptr;

static int x11errorHandler(Display* display, XErrorEvent* error)
{
  if(error->error_code == BadWindow)
    return 0; // This usually happens when querying property on a window that's already gone. That's OK.

  return (*oldX11ErrorHandler)(display, error);
}

template<typename T>
class XFreed // NEVER use this with non-pointer types
{
  XFreed(void) { Q_ASSERT(false); } // perhaps you should have read the definition before using XFreed
};

template<typename T>
class XFreed <T*> // pointer specialized template
{
public:
  XFreed(void) { data = nullptr; }
  ~XFreed(void) { if(data != nullptr) { XFree(data); } } // only free if data was allocated

  // equals operator allows non-superscaler types to be used
  inline T* operator= (T* input) { data = input; return data; }

  // will _always_ convert into another pointer
  template <typename any> inline operator any**(void) { return reinterpret_cast<any**>(&data); }
  template <typename any> inline operator any* (void) { return reinterpret_cast<any* >( data); }

  // data accessors
  inline    operator  T*(void) const { return  data; }
  inline T& operator   *(void) const { return *data; }
  inline T  operator [](int i) const { return  data[i]; }

  // doesnt work yet  :/
  //inline T& operator ->(void) { return *data; }

private:
  T* data;
};



int X11Core::m_damageEventBase = INT_MAX;

X11Core::X11Core(int& argc, char** argv)
  : QApplication(argc, argv)
{
  Q_ASSERT(this == qApp);

#ifdef QT_DEBUG
  Q_ASSERT(sizeof(unsigned long) == sizeof(uint64_t)); // if you have hit here then your compiler sucks
  Q_ASSERT(sizeof(unsigned long) == sizeof(Atom));     // if you have hit here then you are screwed
#endif
  if(m_damageEventBase == INT_MAX)
  {
    oldX11ErrorHandler = XSetErrorHandler(x11errorHandler);
    int damageErrorBase;
    XDamageQueryExtension(QX11Info::display(), &m_damageEventBase, &damageErrorBase);
  }
}

X11Core::~X11Core(void)
{
}

bool X11Core::x11EventFilter(XEvent* event)
{
  if(event->type == m_damageEventBase + XDamageNotify)
  {
    // Repair damaged area.
    XDamageSubtract(QX11Info::display(), reinterpret_cast<XDamageNotifyEvent*>(event)->damage, None, None);
    emit X11Core::instance()->windowDamaged(event->xany.window);
  }
  else
  {
    switch(event->type)
    {
    case DestroyNotify:
      emit windowClosed(event->xdestroywindow.window);
      break;

    case ConfigureNotify:
      emit windowReconfigured(event->xconfigure.window,
                              event->xconfigure.x,
                              event->xconfigure.y,
                              event->xconfigure.width,
                              event->xconfigure.height);
      break;

    case PropertyNotify:
      emit windowPropertyChanged(event->xproperty.window,
                                 event->xproperty.atom);
      break;

    case ClientMessage:
      emit clientMessageReceived(event->xclient.window,
                                 event->xclient.message_type,
                                 event->xclient.data.b);
      break;

    default:
      break;
    }
  }
  return false;
}



Atom X11Core::atom(const char* name)
{
  static QHash<const char*, Atom> atom_cache;

  if(!atom_cache.contains(name))
    atom_cache[name] = XInternAtom(QX11Info::display(), name, False);
  return atom_cache[name];
}


template <Atom Atype>
Atom X11Core::getWindowProperty(const Window wid, const Atom atom, unsigned char** data)
{
  static Atom retType;
  static int retFormat;
  static Atom bytesLeft;
  static Atom numItems;

  if(XGetWindowProperty(QX11Info::display(),
                        wid,
                        atom,
                        0,
                        INT_MAX,
                        False,
                        Atype,
                        &retType,
                        &retFormat,
                        &numItems,
                        &bytesLeft,
                        data
                       ) == Success)
    return numItems;
  return 0;
}

Atom X11Core::getWindowProperty(const Atom Atype, const Window wid, const Atom atom, unsigned char** data)
{
  static Atom retType;
  static int retFormat;
  static Atom bytesLeft;
  static Atom numItems;

  if(XGetWindowProperty(QX11Info::display(),
                        wid,
                        atom,
                        0,
                        INT_MAX,
                        False,
                        Atype,
                        &retType,
                        &retFormat,
                        &numItems,
                        &bytesLeft,
                        data
                       ) == Success)
    return numItems;
  return 0;
}

template <Atom Atype>
AtomV X11Core::getWindowPropertyArray(const WId window, const Atom type)
{
  Atom numItems;
  XFreed<Atom*> data;
  AtomV values;
  if((numItems = getWindowProperty<Atype>(window, type, data)))
  {
    values.resize(numItems);
    for(uint64_t i = 0; i < numItems; i++)
      values[i] = data[i];
  }
  return values;
}


AtomV X11Core::getWindowPropertyCardinalArray(const WId window, const Atom type)
{
  return getWindowPropertyArray<XA_CARDINAL>(window, type);
}

AtomV X11Core::getWindowPropertyWindowArray(const WId window, const Atom type)
{
  return getWindowPropertyArray<XA_WINDOW>(window, type);
}

AtomV X11Core::getWindowPropertyAtomArray(const WId window, const Atom type)
{
  return getWindowPropertyArray<XA_ATOM>(window, type);
}

Atom X11Core::getWindowPropertyWindow(const WId window, const Atom type)
{
  XFreed<Atom*> data;
  if(getWindowProperty<XA_WINDOW>(window, type, data))
    return data[0];
  return 0;
}

QString X11Core::getWindowPropertyUTF8String(const WId window, const Atom type)
{
  XFreed<Atom*> data;
  if(getWindowProperty(UTF8_STRING, window, type, data))
    return QString::fromUtf8(data);
  return QString();
}

QString X11Core::getWindowPropertyLatin1String(const WId window, const Atom type)
{
  XFreed<Atom*> data;
  if(getWindowProperty<XA_STRING>(window, type, data))
    return QString::fromLatin1(data);
  return QString();
}


QString X11Core::getWindowName(const WId window)
{
  QString result = getWindowPropertyUTF8String(window, _NET_WM_VISIBLE_NAME);
  if(!result.isEmpty()) return result;

  result = getWindowPropertyUTF8String(window, _NET_WM_NAME);
  if(!result.isEmpty()) return result;

  result = getWindowPropertyLatin1String(window, WM_NAME);
  if(!result.isEmpty()) return result;

  return "<Unknown>";
}

QIcon X11Core::getWindowIcon(const WId window)
{
  uint64_t numItems;
  XFreed<Atom*> data;

  if((numItems = getWindowProperty<XA_CARDINAL>(window, _NET_WM_ICON, data))) // can it actually return multiple icons???
  {
    uint64_t i, j;
    unsigned int* b16 = data;
    for(i = j = 0; i < numItems; ++j) { b16[i++] = b16[j++]; } // remove padding
    b16 = data; // return to front
    return QIcon(QPixmap::fromImage(QImage(reinterpret_cast<uchar*>(b16 + 2), b16[0], b16[1], QImage::Format_ARGB32))); // assume there is only one icon
  }

  return QIcon();
}

bool X11Core::getWindowUrgency(const WId window)
{
  XFreed<XWMHints*> hints;
  hints = XGetWMHints(QX11Info::display(), window);
  return hints != 0 && ((*hints).flags & 256) != 0; // UrgencyHint
}

void X11Core::sendNETWMMessage(const WId window,
                               const Atom atom,
                               const long l0,
                               const long l1,
                               const long l2,
                               const long l3,
                               const long l4)
{
  XClientMessageEvent event;
  event.type = ClientMessage;
  event.window = window;
  event.message_type = atom;
  event.format = 32;
  event.data.l[0] = l0;
  event.data.l[1] = l1;
  event.data.l[2] = l2;
  event.data.l[3] = l3;
  event.data.l[4] = l4;
  XSendEvent(QX11Info::display(),
             QX11Info::appRootWindow(),
             False,
             SubstructureNotifyMask | SubstructureRedirectMask,
             reinterpret_cast<XEvent*>(&event));
}

void X11Core::activateWindow(const WId window)
{
  XWindowChanges wc;
  wc.stack_mode = Above;
  XConfigureWindow(QX11Info::display(), window, CWStackMode, &wc);

  // Apparently, KWin won't bring window to top with configure request,
  // so we also need to ask it politely by sending a message.
  sendNETWMMessage(window, _NET_ACTIVE_WINDOW, 2, CurrentTime);
}

bool X11Core::makeSystemTray(const WId window)
{
  if(XGetSelectionOwner(QX11Info::display(), _NET_SYSTEM_TRAY_SX) != 0)
    return false;

  XSetSelectionOwner(QX11Info::display(), _NET_SYSTEM_TRAY_SX, window, CurrentTime);
  setWindowProperty<XA_VISUALID>(window, _NET_SYSTEM_TRAY_VISUAL, getARGBVisualId());
  XSync(QX11Info::display(), False);

  // Inform other clients.
  XClientMessageEvent event;
  event.type = ClientMessage;
  event.window = QX11Info::appRootWindow();
  event.message_type = MANAGER;
  event.format = 32;
  event.data.l[0] = CurrentTime;
  event.data.l[1] = _NET_SYSTEM_TRAY_SX;
  event.data.l[2] = window;
  event.data.l[3] = 0;
  event.data.l[4] = 0;
  XSendEvent(QX11Info::display(),
             QX11Info::appRootWindow(),
             False, StructureNotifyMask,
             reinterpret_cast<XEvent*>(&event));

  return true;
}

Atom X11Core::getARGBVisualId()
{
  int numVisuals;
  XFreed<XVisualInfo*> visualInfoList;
  XVisualInfo visualInfoTemplate;
  visualInfoTemplate.screen = QX11Info::appScreen();
  visualInfoTemplate.depth = 32;
  visualInfoTemplate.red_mask   = 0x00FF0000;
  visualInfoTemplate.green_mask = 0x0000FF00;
  visualInfoTemplate.blue_mask  = 0x000000FF;

  visualInfoList = XGetVisualInfo(QX11Info::display(),
                                  VisualScreenMask | VisualDepthMask | VisualRedMaskMask | VisualGreenMaskMask | VisualBlueMaskMask,
                                  &visualInfoTemplate,
                                  &numVisuals);
  return visualInfoList[0].visualid;
}

