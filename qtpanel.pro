include(common/common.pri)

QT += sql

TARGET   = qtpanel4
TEMPLATE = app
INCLUDEPATH += src

SOURCES += \
    src/panelwindow.cpp \
    src/panelapplication.cpp \
    src/main.cpp

HEADERS  += \
    src/panelwindow.h \
    src/panelapplication.h \
    src/pluginloader.h
