#-------------------------------------------------
#
# Project created by QtCreator 2015-06-04T20:06:32
#
#-------------------------------------------------

# https://github.com/Mokolea/SimpleQtLogger

# Xcode 8.0 (Qt 5.7.0, Creator 4.1.0), OS X 10.11.6
# QMAKE_MAC_SDK = macosx10.11

QT += core
QT -= gui

TARGET = TestSimpleQtLogger

CONFIG += console
CONFIG -= app_bundle
#CONFIG += sdk_no_version_check

TEMPLATE = app

QMAKE_CXXFLAGS_DEBUG += -Wextra
#QMAKE_CXXFLAGS_DEBUG += -std=c++11
#QMAKE_CXXFLAGS_DEBUG += -pedantic-errors -Wc++11-long-long

INCLUDEPATH += ../..

SOURCES += main.cpp \
  task.cpp \
  ../../simpleQtLogger.cpp

HEADERS += \
  task.h \
  ../../simpleQtLogger.h
