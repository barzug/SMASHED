#-------------------------------------------------
#
# Project created by QtCreator 2016-12-10T13:04:59
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TParkFinal
TEMPLATE = app


SOURCES += main.cpp\
        game.cpp \
    mainmenu.cpp \
    hero.cpp \
    strangerect.cpp \
    gameover.cpp

HEADERS  += game.h \
    mainmenu.h \
    hero.h \
    strangerect.h \
    gameover.h \
    const.h

FORMS    += game.ui \
    mainmenu.ui \
    gameover.ui

CONFIG += mobility
MOBILITY = multimedia

RESOURCES += \
    res.qrc

