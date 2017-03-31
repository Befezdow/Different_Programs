#-------------------------------------------------
#
# Project created by QtCreator 2016-11-20T23:52:05
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lets Watch
TEMPLATE = app


SOURCES += main.cpp \
    videomenu.cpp \
    videowidget.cpp

HEADERS  += \
    videowidget.h \
    videomenu.h \
    app.h \
    savewidget.h \
    slider.h

RESOURCES += \
    resources.qrc
