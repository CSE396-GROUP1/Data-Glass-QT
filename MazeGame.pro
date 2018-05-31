#-------------------------------------------------
#
# Project created by QtCreator 2018-04-23T00:06:28
#
#-------------------------------------------------

QT       += core gui network
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MazeGame
TEMPLATE = app

CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    gamedes.cpp \
    mapp.cpp \
    player.cpp \
    myserver.cpp \
    mythread.cpp \
    buttons.cpp \
    someonewon.cpp \
    options.cpp

HEADERS  += mainwindow.h \
    gamedes.h \
    mapp.h \
    player.h\
    myserver.h \
    mythread.h \
    playerstate.h \
    buttons.h \
    states.h \
    someonewon.h \
    options.h

FORMS    += \
    gamedes.ui \
    buttons.ui \
    mainwindow.ui \
    someonewon.ui \
    options.ui

RESOURCES += \
    img.qrc
