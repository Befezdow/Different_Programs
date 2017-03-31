#-------------------------------------------------
#
# Project created by QtCreator 2016-08-16T16:49:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ZvezdnoeNebo3
TEMPLATE = app


SOURCES += main.cpp \
    sky.cpp \
    addgalaxy.cpp \
    addmultistar.cpp \
    addstar.cpp \
    addplanet.cpp \
    menubar.cpp \
    outoperator.cpp \
    inoperator.cpp \
    savedata.cpp \
    loaddata.cpp \
    errorinfo.cpp \
    find.cpp

HEADERS  += \
    sky.h \
    galaxycomponents.h \
    addgalaxy.h \
    addmultistar.h \
    addstar.h \
    addplanet.h \
    percentvalidator.h \
    floatvalidator.h \
    menubar.h \
    find.h \
    savedata.h \
    loaddata.h \
    tabledelegate.h \
    errorinfo.h
