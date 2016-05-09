#-------------------------------------------------
#
# Project created by QtCreator 2016-05-08T15:54:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = stock_analyze
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    stock_diagram.cpp

HEADERS  += mainwindow.h \
    stock_diagram.h

FORMS    += mainwindow.ui
