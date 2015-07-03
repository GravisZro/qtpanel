include(../../common/common.pri)

TEMPLATE        = lib
CONFIG         += plugin
TARGET          = $$qtLibraryTarget(trayplugin)
DESTDIR = ../
INCLUDEPATH += src

HEADERS += \
    src/trayplugin.h

SOURCES += \
    src/trayplugin.cpp
