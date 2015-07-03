include(../../common/common.pri)

TEMPLATE        = lib
CONFIG         += plugin
TARGET          = $$qtLibraryTarget(dockplugin)
DESTDIR = ../
INCLUDEPATH += src

HEADERS += \
    src/dockapplet.h \

SOURCES += \
    src/dockapplet.cpp
