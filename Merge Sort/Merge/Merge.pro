TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    cat.cpp \
    sorter.cpp \
    finder.cpp

HEADERS += \
    cat.h \
    sorter.h \
    finder.h
