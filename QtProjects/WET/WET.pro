#-------------------------------------------------
#
# Project created by QtCreator 2014-08-15T19:30:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WET
TEMPLATE = app


SOURCES +=\
        mainwindow.cpp \
    arc.cpp \
    digraph.cpp \
    fileparser.cpp \
    htmlpage.cpp \
    timestamp.cpp \
    url.cpp \
    vertexurl.cpp \
    main.cpp \
    wet.cpp

HEADERS  += mainwindow.h \
    wet.h \
    arc.h \
    digraph.h \
    fileparser.h \
    htmlpage.h \
    timestamp.h \
    url.h \
    vertexurl.h \
    vertex.h

FORMS    += mainwindow.ui
