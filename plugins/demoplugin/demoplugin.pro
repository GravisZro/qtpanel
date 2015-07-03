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
TARGET          = $$qtLibraryTargetd(demoplugin)
MOC_DIR = .moc
OBJECTS_DIR = .obj
INCLUDEPATH += src
DESTDIR = ../

QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -std=c++0x

HEADERS += \
    src/animationutils.h \
    src/applet.h \
    src/demoplugin.h \
    src/xatoms.h

SOURCES += \
    src/applet.cpp \
    src/demoplugin.cpp
