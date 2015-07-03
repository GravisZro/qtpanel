BASE_DIR = /home/gravis/projects/qtpanel4

UI_DIR = $$BASE_DIR/.ui
MOC_DIR = $$BASE_DIR/.moc
OBJECTS_DIR = $$BASE_DIR/.obj
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -std=c++11

QT += core gui widgets x11extras

LIBS    += -lX11
LIBS    += -lXcomposite
LIBS    += -lXdamage
CONFIG  += -j8

INCLUDEPATH += $$BASE_DIR/common

SOURCES += \
    $$BASE_DIR/common/applet.cpp \
    $$BASE_DIR/common/x11core.cpp

HEADERS += \
    $$BASE_DIR/common/applet.h \
    $$BASE_DIR/common/x11core.h \
    $$BASE_DIR/common/xatoms.h
