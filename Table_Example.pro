#-------------------------------------------------
#
# Project created by QtCreator 2016-02-12T19:38:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Table_Example
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        alert_model.cpp

HEADERS  += mainwindow.h \
            alert_model.h

FORMS    += mainwindow.ui

INCLUDEPATH += "/usr/include/"
LIBS += "-L/usr/lib/x86_64-linux-gnu/" -lboost_date_time
