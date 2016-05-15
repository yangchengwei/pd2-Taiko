#-------------------------------------------------
#
# Project created by QtCreator 2016-05-07T15:21:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Taiko
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    game.cpp \
    game2.cpp

HEADERS  += mainwindow.h \
    game.h \
    game2.h

FORMS    += mainwindow.ui \
    game.ui \
    game2.ui

RESOURCES += \
    picture/picture.qrc
