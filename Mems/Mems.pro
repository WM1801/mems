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
#INCLUDEPATH += absolute_path(F:\Qt\mems\Mems\eigenFolder\eigen)

QT += widgets printsupport

SOURCES += main.cpp\
        mainwindow.cpp \
    dlgrs.cpp \
    console.cpp \
    port.cpp \
    viewport.cpp \
    settingport.cpp \
    writefile.cpp \
    parsdata.cpp \
    formatmsg.cpp \
    logmems.cpp \
    calibracc.cpp \
    msgbox.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    dlgrs.h \
    console.h \
    port.h \
    viewport.h \
    settingport.h \
    writefile.h \
    parsdata.h \
    formatmsg.h \
    logmems.h \
    calibracc.h \
    msgbox.h \
    qcustomplot.h

FORMS    += mainwindow.ui \
    dlgrs.ui \
    viewport.ui \
    parsdata.ui \
    logmems.ui \
    calibracc.ui \
    msgbox.ui

RESOURCES += \
    qrc.qrc
