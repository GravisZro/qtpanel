#-------------------------------------------------
#
# Project created by QtCreator 2011-10-26T03:28:28
#
#-------------------------------------------------

QT += core gui
TEMPLATE        = lib
LIBS           += -lX11
CONFIG         += plugin
CONFIG         += -j4
TARGET          = $$qtLibraryTarget(spacerplugin)
MOC_DIR = .moc
OBJECTS_DIR = .obj
INCLUDEPATH += src
DESTDIR = ../

QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -std=c++0x

HEADERS += \
    src/animationutils.h \
    src/applet.h \
    src/x11core.h \
    src/spacerapplet.h \
    src/xatoms.h

SOURCES += \
    src/applet.cpp \
    src/x11core.cpp \
    src/spacerapplet.cpp
