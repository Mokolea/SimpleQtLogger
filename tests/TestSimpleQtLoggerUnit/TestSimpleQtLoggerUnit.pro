# Unit tests for SimpleQtLogger (Qt Test, needs Qt >= 5.3)

# https://github.com/Mokolea/SimpleQtLogger

QT += core testlib
QT -= gui

TARGET = TestSimpleQtLoggerUnit

CONFIG += console testcase
CONFIG -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS_DEBUG += -Wextra

# the qDebug sink is disabled at compile-time by default
DEFINES += ENABLE_SQTL_LOG_SINK_QDEBUG=1

INCLUDEPATH += ../..

SOURCES += tst_simpleQtLogger.cpp \
  ../../simpleQtLogger.cpp

HEADERS += \
  ../../simpleQtLogger.h
