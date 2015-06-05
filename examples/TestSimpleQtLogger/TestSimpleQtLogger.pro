#-------------------------------------------------
#
# Project created by QtCreator 2015-06-04T20:06:32
#
#-------------------------------------------------

QT       += core
QT       -= gui

TARGET = TestSimpleQtLogger

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../..

SOURCES += main.cpp \
    task.cpp \
    ../../simpleQtLogger.cpp

HEADERS += \
    task.h \
    ../../simpleQtLogger.h
