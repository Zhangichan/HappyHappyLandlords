#-------------------------------------------------
#
# Project created by QtCreator 2017-12-26T10:47:10
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LandLords
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        interface.cpp \
    login.cpp \
    maininterface.cpp \
    cardpicture.cpp \
    card.cpp \
    gameprocess.cpp \
    robot.cpp \
    userplayer.cpp \
    gameplayer.cpp \
    method.cpp \
    hand.cpp

HEADERS += \
        interface.h \
    login.h \
    maininterface.h \
    cardpicture.h \
    card.h \
    gameprocess.h \
    robot.h \
    userplayer.h \
    gameplayer.h \
    method.h \
    hand.h

FORMS += \
        interface.ui \
    login.ui \
    maininterface.ui

DISTFILES +=

RESOURCES += \
    img.qrc
