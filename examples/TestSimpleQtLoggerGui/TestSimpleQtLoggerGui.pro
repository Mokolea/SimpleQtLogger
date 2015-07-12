#-------------------------------------------------
#
# Project created by QtCreator 2015-06-14T18:38:17
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestSimpleQtLoggerGui

TEMPLATE = app

QMAKE_CXXFLAGS_DEBUG += -Wextra
#QMAKE_CXXFLAGS_DEBUG += -std=c++11
#QMAKE_CXXFLAGS_DEBUG += -pedantic-errors -Wc++11-long-long

INCLUDEPATH += ../..

SOURCES += main.cpp \
  dialog.cpp \
  eventLog.cpp \
  ../../simpleQtLogger.cpp

HEADERS += dialog.h \
  eventLog.h \
  ../../simpleQtLogger.h

FORMS += dialog.ui
