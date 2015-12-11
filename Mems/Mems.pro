#-------------------------------------------------
#
# Project created by QtCreator 2015-12-03T11:11:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


QT += serialport
TARGET = Mems
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dlgrs.cpp \
    console.cpp \
    port.cpp \
    viewport.cpp \
    settingport.cpp \
    writefile.cpp

HEADERS  += mainwindow.h \
    dlgrs.h \
    console.h \
    port.h \
    viewport.h \
    settingport.h \
    writefile.h

FORMS    += mainwindow.ui \
    dlgrs.ui \
    viewport.ui

RESOURCES += \
    qrc.qrc
