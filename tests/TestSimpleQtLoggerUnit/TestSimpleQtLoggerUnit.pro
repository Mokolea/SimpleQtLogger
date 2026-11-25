# Unit tests for SimpleQtLogger (Qt Test, needs Qt >= 5.3)

# https://github.com/Mokolea/SimpleQtLogger

QT += core testlib
QT -= gui

TARGET = TestSimpleQtLoggerUnit

CONFIG += console testcase
CONFIG -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS_DEBUG += -Wextra

INCLUDEPATH += ../..

SOURCES += tst_simpleQtLogger.cpp \
  ../../simpleQtLogger.cpp

HEADERS += \
  ../../simpleQtLogger.h
