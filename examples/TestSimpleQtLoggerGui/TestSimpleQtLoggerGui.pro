#-------------------------------------------------
#
# Project created by QtCreator 2015-06-14T18:38:17
#
#-------------------------------------------------

# https://github.com/Mokolea/SimpleQtLogger

# Xcode 8.0 (Qt 5.7.0, Creator 4.1.0), OS X 10.11.6
# QMAKE_MAC_SDK = macosx10.11

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestSimpleQtLoggerGui

#CONFIG += sdk_no_version_check

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
