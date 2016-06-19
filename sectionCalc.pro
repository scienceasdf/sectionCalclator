#-------------------------------------------------
#
# Project created by QtCreator 2016-05-31T23:08:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sectionCalc
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    crossSection.cpp \
    paintwidget.cpp \
    chouxiang.cpp \
    shapeinput.cpp

HEADERS  += widget.h \
    paintwidget.h \
    crossSection.h \
    chouxiang.h \
    shapeinput.h

FORMS    += widget.ui \
    chouxiang.ui \
    shapeinput.ui

RESOURCES +=
RC_FILE = ico.rc 
