include(../../common/common.pri)

TEMPLATE        = lib
CONFIG         += plugin
TARGET          = $$qtLibraryTarget(clockplugin)
DESTDIR = ../
INCLUDEPATH += src

HEADERS += \
    src/clockapplet.h

SOURCES += \
    src/clockapplet.cpp
