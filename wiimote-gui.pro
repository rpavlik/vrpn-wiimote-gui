#-------------------------------------------------
#
# Project created by QtCreator 2011-02-21T11:11:54
#
#-------------------------------------------------

QT       += core gui

TARGET = wiimote-gui
TEMPLATE = app


SOURCES += main.cpp \
        mainwindow.cpp \
    VRPNObjects.cpp

HEADERS  += mainwindow.h \
    VRPNObjects.h

FORMS    += mainwindow.ui

LIBS += -lvrpn \
    -lquat
