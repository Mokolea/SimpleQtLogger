#-------------------------------------------------
#
# Project created by QtCreator 2015-06-04T20:06:32
#
#-------------------------------------------------

QT += core
QT -= gui

TARGET = TestSimpleQtLogger

CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS_DEBUG += -Wextra
#QMAKE_CXXFLAGS_DEBUG += -std=c++11
QMAKE_CXXFLAGS_DEBUG += -pedantic-errors -Wc++11-long-long

INCLUDEPATH += ../..

SOURCES += main.cpp \
  task.cpp \
  ../../simpleQtLogger.cpp

HEADERS += \
  task.h \
  ../../simpleQtLogger.h
