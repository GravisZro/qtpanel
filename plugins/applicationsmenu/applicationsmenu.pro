include(../../common/common.pri)

QT += x11extras
TEMPLATE        = lib
CONFIG         += plugin
TARGET          = $$qtLibraryTarget(applicationsmenuplugin)
DESTDIR = ../
INCLUDEPATH += src

HEADERS += \
    src/applicationsmenuapplet.h \
    src/standards.h

SOURCES += \
    src/applicationsmenuapplet.cpp \
    src/standards.cpp
