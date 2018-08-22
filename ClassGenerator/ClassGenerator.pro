#-------------------------------------------------
#
# Project created by QtCreator 2015-05-20T02:07:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ClassGenerator
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    pugixml.cpp \
    ClassParser.cpp \
    SourceFileCreator.cpp \
    CGUtils.cpp \
    Variable.cpp \
    Classe.cpp \
    HeaderFileCreator.cpp \
    mainwindowv2.cpp \
    Fonction.cpp

HEADERS  += mainwindow.h \
    pugiconfig.hpp \
    pugixml.hpp \
    ClassParser.h \
    SourceFileCreator.h \
    CGUtils.h \
    Classe.h \
    Variable.h \
    HeaderFileCreator.h \
    mainwindowv2.h \
    Fonction.h

FORMS    += mainwindow.ui \
    mainwindowv2.ui

#INCLUDEPATH += "B:\Xerces\xerces-c-3.1.2\src" \
#               "B:\Xerces\xerces-c-3.1.2\src\.libs"

#LIBS += -L"B:\Xerces\xerces-c-3.1.2\src\.libs" \
#        -lxerces-c
