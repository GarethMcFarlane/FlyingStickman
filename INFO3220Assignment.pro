#-------------------------------------------------
#
# Project created by QtCreator 2015-03-20T19:48:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = INFO3220B1a
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    configreader.cpp \
    stickman.cpp \
    tinystickman.cpp \
    normalstickman.cpp \
    largestickman.cpp \
    giantstickman.cpp \
    background.cpp \
    stickmanfactory.cpp \
    obstacle.cpp \
    compositeobstacle.cpp \
    rectangleobstacle.cpp \
    circleobstacle.cpp \
    triangleobstacle.cpp \
    checkpoint.cpp \
    tinypowerup.cpp \
    normalpowerup.cpp \
    largepowerup.cpp \
    giantpowerup.cpp \
    gamemediator.cpp

HEADERS  += dialog.h \
    configreader.h \
    stickman.h \
    tinystickman.h \
    normalstickman.h \
    largestickman.h \
    giantstickman.h \
    background.h \
    stickmanfactory.h \
    obstacle.h \
    compositeobstacle.h \
    rectangleobstacle.h \
    circleobstacle.h \
    triangleobstacle.h \
    checkpoint.h \
    tinypowerup.h \
    normalpowerup.h \
    largepowerup.h \
    giantpowerup.h \
    gamemediator.h

FORMS    += dialog.ui

RESOURCES += \
    gameresources.qrc

DISTFILES +=

filestocopy.files = game.config \
  background.jpg
filestocopy.path = $$OUT_PWD

INSTALLS += filestocopy
