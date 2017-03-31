TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    binarytree.cpp \
    treeitem.cpp \
    binarywriter.cpp \
    symbolscounter.cpp \
    binaryreader.cpp

HEADERS += \
    binarytree.h \
    treeitem.h \
    binarywriter.h \
    symbolscounter.h \
    binaryreader.h
