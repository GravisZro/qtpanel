#ifndef XATOMS_H
#define XATOMS_H

#include <X11/Xlib.h>
#include <string.h>

static Display* xdisp = const_cast<Display*>(XOpenDisplay(NULL));
static const char default_screen_id[] = {'_','N','E','T','_','S','Y','S','T','E','M','_','T','R','A','Y','_','S', (char)(DefaultScreen(xdisp) + '0')};

static const Atom CLIPBOARD                                    = XInternAtom(xdisp, "CLIPBOARD"                                   , False);
static const Atom MANAGER                                      = XInternAtom(xdisp, "MANAGER"                                     , False);
static const Atom PRIMARY                                      = XInternAtom(xdisp, "PRIMARY"                                     , False);
static const Atom SECONDARY                                    = XInternAtom(xdisp, "SECONDARY"                                   , False);
static const Atom UTF8_STRING                                  = XInternAtom(xdisp, "UTF8_STRING"                                 , False);
static const Atom WM_CLASS                                     = XInternAtom(xdisp, "WM_CLASS"                                    , False);
static const Atom WM_CLIENT_MACHINE                            = XInternAtom(xdisp, "WM_CLIENT_MACHINE"                           , False);
static const Atom WM_HINTS                                     = XInternAtom(xdisp, "WM_HINTS"                                    , False);
static const Atom WM_NAME                                      = XInternAtom(xdisp, "WM_NAME"                                     , False);
static const Atom WM_TRANSIENT_FOR                             = XInternAtom(xdisp, "WM_TRANSIENT_FOR"                            , False);
static const Atom XEMBED_ACTIVATE_ACCELERATOR                  = XInternAtom(xdisp, "XEMBED_ACTIVATE_ACCELERATOR"                 , False);
static const Atom XEMBED_EMBEDDED_NOTIFY                       = XInternAtom(xdisp, "XEMBED_EMBEDDED_NOTIFY"                      , False);
static const Atom XEMBED_FOCUS_IN                              = XInternAtom(xdisp, "XEMBED_FOCUS_IN"                             , False);
static const Atom XEMBED_FOCUS_NEXT                            = XInternAtom(xdisp, "XEMBED_FOCUS_NEXT"                           , False);
static const Atom XEMBED_FOCUS_OUT                             = XInternAtom(xdisp, "XEMBED_FOCUS_OUT"                            , False);
static const Atom XEMBED_FOCUS_PREV                            = XInternAtom(xdisp, "XEMBED_FOCUS_PREV"                           , False);
static const Atom XEMBED_MODALITY_OFF                          = XInternAtom(xdisp, "XEMBED_MODALITY_OFF"                         , False);
static const Atom XEMBED_MODALITY_ON                           = XInternAtom(xdisp, "XEMBED_MODALITY_ON"                          , False);
static const Atom XEMBED_REGISTER_ACCELERATOR                  = XInternAtom(xdisp, "XEMBED_REGISTER_ACCELERATOR"                 , False);
static const Atom XEMBED_REQUEST_FOCUS                         = XInternAtom(xdisp, "XEMBED_REQUEST_FOCUS"                        , False);
static const Atom XEMBED_UNREGISTER_ACCELERATOR                = XInternAtom(xdisp, "XEMBED_UNREGISTER_ACCELERATOR"               , False);
static const Atom XEMBED_WINDOW_ACTIVATE                       = XInternAtom(xdisp, "XEMBED_WINDOW_ACTIVATE"                      , False);
static const Atom XEMBED_WINDOW_DEACTIVATE                     = XInternAtom(xdisp, "XEMBED_WINDOW_DEACTIVATE"                    , False);
static const Atom _NET_ACTIVE_WINDOW                           = XInternAtom(xdisp, "_NET_ACTIVE_WINDOW"                          , False);
static const Atom _NET_CLIENT_LIST                             = XInternAtom(xdisp, "_NET_CLIENT_LIST"                            , False);
static const Atom _NET_CLIENT_LIST_NET_CLIENT_LIST_STACKING    = XInternAtom(xdisp, "_NET_CLIENT_LIST_NET_CLIENT_LIST_STACKING"   , False);
static const Atom _NET_CLIENT_LIST_STACKING                    = XInternAtom(xdisp, "_NET_CLIENT_LIST_STACKING"                   , False);
static const Atom _NET_CLOSE_WINDOW                            = XInternAtom(xdisp, "_NET_CLOSE_WINDOW"                           , False);
static const Atom _NET_CURRENT_DESKTOP                         = XInternAtom(xdisp, "_NET_CURRENT_DESKTOP"                        , False);
static const Atom _NET_DESKTOP_GEOMETRY                        = XInternAtom(xdisp, "_NET_DESKTOP_GEOMETRY"                       , False);
static const Atom _NET_DESKTOP_LAYOUT                          = XInternAtom(xdisp, "_NET_DESKTOP_LAYOUT"                         , False);
static const Atom _NET_DESKTOP_NAMES                           = XInternAtom(xdisp, "_NET_DESKTOP_NAMES"                          , False);
static const Atom _NET_DESKTOP_NAMES_NET_SHOWING_DESKTOP       = XInternAtom(xdisp, "_NET_DESKTOP_NAMES_NET_SHOWING_DESKTOP"      , False);
static const Atom _NET_DESKTOP_VIEWPORT                        = XInternAtom(xdisp, "_NET_DESKTOP_VIEWPORT"                       , False);
static const Atom _NET_FRAME_EXTENTS                           = XInternAtom(xdisp, "_NET_FRAME_EXTENTS"                          , False);
static const Atom _NET_MAX_SELECTION_SIZE                      = XInternAtom(xdisp, "_NET_MAX_SELECTION_SIZE"                     , False);
static const Atom _NET_MOVERESIZE_WINDOW                       = XInternAtom(xdisp, "_NET_MOVERESIZE_WINDOW"                      , False);
static const Atom _NET_NUMBER_OF_DESKTOPS                      = XInternAtom(xdisp, "_NET_NUMBER_OF_DESKTOPS"                     , False);
static const Atom _NET_REQUEST_FRAME_EXTENTS                   = XInternAtom(xdisp, "_NET_REQUEST_FRAME_EXTENTS"                  , False);
static const Atom _NET_RESTACK_WINDOW                          = XInternAtom(xdisp, "_NET_RESTACK_WINDOW"                         , False);
static const Atom _NET_SHOWING_DESKTOP                         = XInternAtom(xdisp, "_NET_SHOWING_DESKTOP"                        , False);
static const Atom _NET_SUPPORTED                               = XInternAtom(xdisp, "_NET_SUPPORTED"                              , False);
static const Atom _NET_SUPPORTING_WM_CHECK                     = XInternAtom(xdisp, "_NET_SUPPORTING_WM_CHECK"                    , False);
static const Atom _NET_SYSTEM_TRAY_OPCODE                      = XInternAtom(xdisp, "_NET_SYSTEM_TRAY_OPCODE"                     , False);
static const Atom _NET_SYSTEM_TRAY_ORIENTATION                 = XInternAtom(xdisp, "_NET_SYSTEM_TRAY_ORIENTATION"                , False);
static const Atom _NET_SYSTEM_TRAY_SX                          = XInternAtom(xdisp, default_screen_id                             , False);
static const Atom _NET_SYSTEM_TRAY_S1                          = XInternAtom(xdisp, "_NET_SYSTEM_TRAY_S1"                         , False);
static const Atom _NET_SYSTEM_TRAY_S2                          = XInternAtom(xdisp, "_NET_SYSTEM_TRAY_S2"                         , False);
static const Atom _NET_SYSTEM_TRAY_S3                          = XInternAtom(xdisp, "_NET_SYSTEM_TRAY_S3"                         , False);
static const Atom _NET_SYSTEM_TRAY_S4                          = XInternAtom(xdisp, "_NET_SYSTEM_TRAY_S4"                         , False);
static const Atom _NET_SYSTEM_TRAY_S5                          = XInternAtom(xdisp, "_NET_SYSTEM_TRAY_S5"                         , False);
static const Atom _NET_SYSTEM_TRAY_S6                          = XInternAtom(xdisp, "_NET_SYSTEM_TRAY_S6"                         , False);
static const Atom _NET_SYSTEM_TRAY_S7                          = XInternAtom(xdisp, "_NET_SYSTEM_TRAY_S7"                         , False);
static const Atom _NET_SYSTEM_TRAY_S8                          = XInternAtom(xdisp, "_NET_SYSTEM_TRAY_S8"                         , False);
static const Atom _NET_SYSTEM_TRAY_VISUAL                      = XInternAtom(xdisp, "_NET_SYSTEM_TRAY_VISUAL"                     , False);
static const Atom _NET_VIRTUAL_ROOTS                           = XInternAtom(xdisp, "_NET_VIRTUAL_ROOTS"                          , False);
static const Atom _NET_WM_ACTION_ABOVE                         = XInternAtom(xdisp, "_NET_WM_ACTION_ABOVE"                        , False);
static const Atom _NET_WM_ACTION_BELOW                         = XInternAtom(xdisp, "_NET_WM_ACTION_BELOW"                        , False);
static const Atom _NET_WM_ACTION_CHANGE_DESKTOP                = XInternAtom(xdisp, "_NET_WM_ACTION_CHANGE_DESKTOP"               , False);
static const Atom _NET_WM_ACTION_CLOSE                         = XInternAtom(xdisp, "_NET_WM_ACTION_CLOSE"                        , False);
static const Atom _NET_WM_ACTION_FULLSCREEN                    = XInternAtom(xdisp, "_NET_WM_ACTION_FULLSCREEN"                   , False);
static const Atom _NET_WM_ACTION_MAXIMIZE_HORZ                 = XInternAtom(xdisp, "_NET_WM_ACTION_MAXIMIZE_HORZ"                , False);
static const Atom _NET_WM_ACTION_MAXIMIZE_VERT                 = XInternAtom(xdisp, "_NET_WM_ACTION_MAXIMIZE_VERT"                , False);
static const Atom _NET_WM_ACTION_MINIMIZE                      = XInternAtom(xdisp, "_NET_WM_ACTION_MINIMIZE"                     , False);
static const Atom _NET_WM_ACTION_MOVE                          = XInternAtom(xdisp, "_NET_WM_ACTION_MOVE"                         , False);
static const Atom _NET_WM_ACTION_RESIZE                        = XInternAtom(xdisp, "_NET_WM_ACTION_RESIZE"                       , False);
static const Atom _NET_WM_ACTION_SHADE                         = XInternAtom(xdisp, "_NET_WM_ACTION_SHADE"                        , False);
static const Atom _NET_WM_ACTION_STICK                         = XInternAtom(xdisp, "_NET_WM_ACTION_STICK"                        , False);
static const Atom _NET_WM_ALLOWED_ACTIONS                      = XInternAtom(xdisp, "_NET_WM_ALLOWED_ACTIONS"                     , False);
static const Atom _NET_WM_BOTTOMLEFT                           = XInternAtom(xdisp, "_NET_WM_BOTTOMLEFT"                          , False);
static const Atom _NET_WM_BOTTOMRIGHT                          = XInternAtom(xdisp, "_NET_WM_BOTTOMRIGHT"                         , False);
static const Atom _NET_WM_CM_S1                                = XInternAtom(xdisp, "_NET_WM_CM_S1"                               , False);
static const Atom _NET_WM_CM_S2                                = XInternAtom(xdisp, "_NET_WM_CM_S2"                               , False);
static const Atom _NET_WM_CM_S3                                = XInternAtom(xdisp, "_NET_WM_CM_S3"                               , False);
static const Atom _NET_WM_CM_S4                                = XInternAtom(xdisp, "_NET_WM_CM_S4"                               , False);
static const Atom _NET_WM_CM_S5                                = XInternAtom(xdisp, "_NET_WM_CM_S5"                               , False);
static const Atom _NET_WM_CM_S6                                = XInternAtom(xdisp, "_NET_WM_CM_S6"                               , False);
static const Atom _NET_WM_CM_S7                                = XInternAtom(xdisp, "_NET_WM_CM_S7"                               , False);
static const Atom _NET_WM_CM_S8                                = XInternAtom(xdisp, "_NET_WM_CM_S8"                               , False);
static const Atom _NET_WM_DESKTOP                              = XInternAtom(xdisp, "_NET_WM_DESKTOP"                             , False);
static const Atom _NET_WM_FULLSCREEN_MONITORS                  = XInternAtom(xdisp, "_NET_WM_FULLSCREEN_MONITORS"                 , False);
static const Atom _NET_WM_FULL_PLACEMENT                       = XInternAtom(xdisp, "_NET_WM_FULL_PLACEMENT"                      , False);
static const Atom _NET_WM_HANDLED_ICONS                        = XInternAtom(xdisp, "_NET_WM_HANDLED_ICONS"                       , False);
static const Atom _NET_WM_ICON                                 = XInternAtom(xdisp, "_NET_WM_ICON"                                , False);
static const Atom _NET_WM_ICON_GEOMETRY                        = XInternAtom(xdisp, "_NET_WM_ICON_GEOMETRY"                       , False);
static const Atom _NET_WM_ICON_NAME                            = XInternAtom(xdisp, "_NET_WM_ICON_NAME"                           , False);
static const Atom _NET_WM_ICON_NET_WM_PID_NET_WM_HANDLED_ICONS = XInternAtom(xdisp, "_NET_WM_ICON_NET_WM_PID_NET_WM_HANDLED_ICONS", False);
static const Atom _NET_WM_MOVERESIZE                           = XInternAtom(xdisp, "_NET_WM_MOVERESIZE"                          , False);
static const Atom _NET_WM_MOVERESIZE_CANCEL                    = XInternAtom(xdisp, "_NET_WM_MOVERESIZE_CANCEL"                   , False);
static const Atom _NET_WM_MOVERESIZE_MOVE                      = XInternAtom(xdisp, "_NET_WM_MOVERESIZE_MOVE"                     , False);
static const Atom _NET_WM_MOVERESIZE_MOVE_KEYBOARD             = XInternAtom(xdisp, "_NET_WM_MOVERESIZE_MOVE_KEYBOARD"            , False);
static const Atom _NET_WM_MOVERESIZE_SIZE_BOTTOM               = XInternAtom(xdisp, "_NET_WM_MOVERESIZE_SIZE_BOTTOM"              , False);
static const Atom _NET_WM_MOVERESIZE_SIZE_BOTTOMLEFT           = XInternAtom(xdisp, "_NET_WM_MOVERESIZE_SIZE_BOTTOMLEFT"          , False);
static const Atom _NET_WM_MOVERESIZE_SIZE_BOTTOMRIGHT          = XInternAtom(xdisp, "_NET_WM_MOVERESIZE_SIZE_BOTTOMRIGHT"         , False);
static const Atom _NET_WM_MOVERESIZE_SIZE_KEYBOARD             = XInternAtom(xdisp, "_NET_WM_MOVERESIZE_SIZE_KEYBOARD"            , False);
static const Atom _NET_WM_MOVERESIZE_SIZE_LEFT                 = XInternAtom(xdisp, "_NET_WM_MOVERESIZE_SIZE_LEFT"                , False);
static const Atom _NET_WM_MOVERESIZE_SIZE_RIGHT                = XInternAtom(xdisp, "_NET_WM_MOVERESIZE_SIZE_RIGHT"               , False);
static const Atom _NET_WM_MOVERESIZE_SIZE_TOP                  = XInternAtom(xdisp, "_NET_WM_MOVERESIZE_SIZE_TOP"                 , False);
static const Atom _NET_WM_MOVERESIZE_SIZE_TOPLEFT              = XInternAtom(xdisp, "_NET_WM_MOVERESIZE_SIZE_TOPLEFT"             , False);
static const Atom _NET_WM_MOVERESIZE_SIZE_TOPRIGHT             = XInternAtom(xdisp, "_NET_WM_MOVERESIZE_SIZE_TOPRIGHT"            , False);
static const Atom _NET_WM_NAME                                 = XInternAtom(xdisp, "_NET_WM_NAME"                                , False);
static const Atom _NET_WM_NAME_NET_CURRENT_DESKTOP             = XInternAtom(xdisp, "_NET_WM_NAME_NET_CURRENT_DESKTOP"            , False);
static const Atom _NET_WM_ORIENTATION_HORZ                     = XInternAtom(xdisp, "_NET_WM_ORIENTATION_HORZ"                    , False);
static const Atom _NET_WM_ORIENTATION_VERT                     = XInternAtom(xdisp, "_NET_WM_ORIENTATION_VERT"                    , False);
static const Atom _NET_WM_PID                                  = XInternAtom(xdisp, "_NET_WM_PID"                                 , False);
static const Atom _NET_WM_PING                                 = XInternAtom(xdisp, "_NET_WM_PING"                                , False);
static const Atom _NET_WM_SOURCE_APP                           = XInternAtom(xdisp, "_NET_WM_SOURCE_APP"                          , False);
static const Atom _NET_WM_SOURCE_UNKNOWN                       = XInternAtom(xdisp, "_NET_WM_SOURCE_UNKNOWN"                      , False);
static const Atom _NET_WM_SOURCE_USER                          = XInternAtom(xdisp, "_NET_WM_SOURCE_USER"                         , False);
static const Atom _NET_WM_STATE                                = XInternAtom(xdisp, "_NET_WM_STATE"                               , False);
static const Atom _NET_WM_STATE_ABOVE                          = XInternAtom(xdisp, "_NET_WM_STATE_ABOVE"                         , False);
static const Atom _NET_WM_STATE_ADD                            = XInternAtom(xdisp, "_NET_WM_STATE_ADD"                           , False);
static const Atom _NET_WM_STATE_BELOW                          = XInternAtom(xdisp, "_NET_WM_STATE_BELOW"                         , False);
static const Atom _NET_WM_STATE_DEMANDS_ATTENTION              = XInternAtom(xdisp, "_NET_WM_STATE_DEMANDS_ATTENTION"             , False);
static const Atom _NET_WM_STATE_FULLSCREEN                     = XInternAtom(xdisp, "_NET_WM_STATE_FULLSCREEN"                    , False);
static const Atom _NET_WM_STATE_HIDDEN                         = XInternAtom(xdisp, "_NET_WM_STATE_HIDDEN"                        , False);
static const Atom _NET_WM_STATE_MAXIMIZED_HORZ                 = XInternAtom(xdisp, "_NET_WM_STATE_MAXIMIZED_HORZ"                , False);
static const Atom _NET_WM_STATE_MAXIMIZED_VERT                 = XInternAtom(xdisp, "_NET_WM_STATE_MAXIMIZED_VERT"                , False);
static const Atom _NET_WM_STATE_MODAL                          = XInternAtom(xdisp, "_NET_WM_STATE_MODAL"                         , False);
static const Atom _NET_WM_STATE_REMOVE                         = XInternAtom(xdisp, "_NET_WM_STATE_REMOVE"                        , False);
static const Atom _NET_WM_STATE_SHADED                         = XInternAtom(xdisp, "_NET_WM_STATE_SHADED"                        , False);
static const Atom _NET_WM_STATE_SKIP_PAGER                     = XInternAtom(xdisp, "_NET_WM_STATE_SKIP_PAGER"                    , False);
static const Atom _NET_WM_STATE_SKIP_TASKBAR                   = XInternAtom(xdisp, "_NET_WM_STATE_SKIP_TASKBAR"                  , False);
static const Atom _NET_WM_STATE_STICKY                         = XInternAtom(xdisp, "_NET_WM_STATE_STICKY"                        , False);
static const Atom _NET_WM_STATE_TOGGLE                         = XInternAtom(xdisp, "_NET_WM_STATE_TOGGLE"                        , False);
static const Atom _NET_WM_STRUT                                = XInternAtom(xdisp, "_NET_WM_STRUT"                               , False);
static const Atom _NET_WM_STRUT_PARTIAL                        = XInternAtom(xdisp, "_NET_WM_STRUT_PARTIAL"                       , False);
static const Atom _NET_WM_SYNC_REQUEST                         = XInternAtom(xdisp, "_NET_WM_SYNC_REQUEST"                        , False);
static const Atom _NET_WM_TOPLEFT                              = XInternAtom(xdisp, "_NET_WM_TOPLEFT"                             , False);
static const Atom _NET_WM_TOPRIGHT                             = XInternAtom(xdisp, "_NET_WM_TOPRIGHT"                            , False);
static const Atom _NET_WM_USER_TIME                            = XInternAtom(xdisp, "_NET_WM_USER_TIME"                           , False);
static const Atom _NET_WM_USER_TIME_WINDOW                     = XInternAtom(xdisp, "_NET_WM_USER_TIME_WINDOW"                    , False);
static const Atom _NET_WM_VISIBLE_ICON_NAME                    = XInternAtom(xdisp, "_NET_WM_VISIBLE_ICON_NAME"                   , False);
static const Atom _NET_WM_VISIBLE_NAME                         = XInternAtom(xdisp, "_NET_WM_VISIBLE_NAME"                        , False);
static const Atom _NET_WM_WINDOW_OPACITY                       = XInternAtom(xdisp, "_NET_WM_WINDOW_OPACITY"                      , False);
static const Atom _NET_WM_WINDOW_TYPE                          = XInternAtom(xdisp, "_NET_WM_WINDOW_TYPE"                         , False);
static const Atom _NET_WM_WINDOW_TYPE_DESKTOP                  = XInternAtom(xdisp, "_NET_WM_WINDOW_TYPE_DESKTOP"                 , False);
static const Atom _NET_WM_WINDOW_TYPE_DIALOG                   = XInternAtom(xdisp, "_NET_WM_WINDOW_TYPE_DIALOG"                  , False);
static const Atom _NET_WM_WINDOW_TYPE_DOCK                     = XInternAtom(xdisp, "_NET_WM_WINDOW_TYPE_DOCK"                    , False);
static const Atom _NET_WM_WINDOW_TYPE_MENU                     = XInternAtom(xdisp, "_NET_WM_WINDOW_TYPE_MENU"                    , False);
static const Atom _NET_WM_WINDOW_TYPE_NORMAL                   = XInternAtom(xdisp, "_NET_WM_WINDOW_TYPE_NORMAL"                  , False);
static const Atom _NET_WM_WINDOW_TYPE_SPLASH                   = XInternAtom(xdisp, "_NET_WM_WINDOW_TYPE_SPLASH"                  , False);
static const Atom _NET_WM_WINDOW_TYPE_TOOLBAR                  = XInternAtom(xdisp, "_NET_WM_WINDOW_TYPE_TOOLBAR"                 , False);
static const Atom _NET_WM_WINDOW_TYPE_UTILITY                  = XInternAtom(xdisp, "_NET_WM_WINDOW_TYPE_UTILITY"                 , False);
static const Atom _NET_WORKAREA                                = XInternAtom(xdisp, "_NET_WORKAREA"                               , False);
static const Atom _WM_WINDOW_TYPE_DESKTOP                      = XInternAtom(xdisp, "_WM_WINDOW_TYPE_DESKTOP"                     , False);
static const Atom _WM_WINDOW_TYPE_DIALOG                       = XInternAtom(xdisp, "_WM_WINDOW_TYPE_DIALOG"                      , False);
static const Atom _WM_WINDOW_TYPE_DOCK                         = XInternAtom(xdisp, "_WM_WINDOW_TYPE_DOCK"                        , False);
static const Atom _WM_WINDOW_TYPE_MENU                         = XInternAtom(xdisp, "_WM_WINDOW_TYPE_MENU"                        , False);
static const Atom _WM_WINDOW_TYPE_NORMAL                       = XInternAtom(xdisp, "_WM_WINDOW_TYPE_NORMAL"                      , False);
static const Atom _WM_WINDOW_TYPE_SPLASH                       = XInternAtom(xdisp, "_WM_WINDOW_TYPE_SPLASH"                      , False);
static const Atom _WM_WINDOW_TYPE_TOOLBAR                      = XInternAtom(xdisp, "_WM_WINDOW_TYPE_TOOLBAR"                     , False);
static const Atom _WM_WINDOW_TYPE_UTILITY                      = XInternAtom(xdisp, "_WM_WINDOW_TYPE_UTILITY"                     , False);
static const Atom _KDE_NET_WM_BLUR_BEHIND_REGION               = XInternAtom(xdisp, "_KDE_NET_WM_BLUR_BEHIND_REGION"              , False);


struct _NET_DESKTOP_GEOMETRY_t
{
  Atom width;
  Atom height;
  _NET_DESKTOP_GEOMETRY_t(void) : width(0), height(0) {}
};

struct _NET_DESKTOP_VIEWPORT_t
{
  Atom x;
  Atom y;
  _NET_DESKTOP_VIEWPORT_t(void) : x(0), y(0) {}
};

struct _NET_WORKAREA_t
{
  Atom x;
  Atom y;
  Atom width;
  Atom height;
  _NET_WORKAREA_t(void) : x(0), y(0), width(0), height(0) {}
};

struct _NET_DESKTOP_LAYOUT_t
{
  Atom orientation;
  Atom columns;
  Atom rows;
  Atom starting_corner;
  _NET_DESKTOP_LAYOUT_t(void) : orientation(0), columns(0), rows(0), starting_corner(0) {}
};

struct _NET_WM_STRUT_t
{
  Atom left;
  Atom right;
  Atom top;
  Atom bottom;
  _NET_WM_STRUT_t(void) : left(0), right(0), top(0), bottom(0) {}
};

struct _NET_WM_STRUT_PARTIAL_t
{
  Atom left;
  Atom right;
  Atom top;
  Atom bottom;

  Atom left_start;
  Atom left_end;

  Atom right_start;
  Atom right_end;

  Atom top_start;
  Atom top_end;

  Atom bottom_start;
  Atom bottom_end;
  _NET_WM_STRUT_PARTIAL_t(void) { memset(this, 0, sizeof(_NET_WM_STRUT_PARTIAL_t)); }
};

typedef _NET_WORKAREA_t _NET_WM_ICON_GEOMETRY_t;
typedef _NET_WM_STRUT_t _NET_FRAME_EXTENTS_t;

#endif // XATOMS_H
