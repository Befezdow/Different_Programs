TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    hash.cpp \
    binarywriter.cpp \
    binaryreader.cpp

HEADERS += \
    hash.h \
    binarywriter.h \
    binaryreader.h
