/*
  Test Simple Logger for Qt

  Mario Ban, 05.2015

  Tested using:
   - Qt 5.4.2 (Community Open Source), Clang 6.0 (Apple) 64 bit
   - Qt 4.8.6 Debian 8, gcc version 4.9.2 (Debian 4.9.2-10), 64 bit

  GNU Lesser General Public License v2.1
  Copyright (C) 2015 Mario Ban
*/

#include <QCoreApplication>
#include <QTimer>

#include "task.h"
#include "simpleQtLogger.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  // initialize SimpleQtLogger (step 1/2)
  simpleqtlogger::SimpleQtLogger::createInstance(qApp)->setLogFileName("testSimpleQtLogger.log", 10*1024, 10);
  simpleqtlogger::SQTL_LOG_ENABLE_SINK_FILE = true;
  simpleqtlogger::SQTL_LOG_ENABLE_SINK_CONSOLE = false;
  simpleqtlogger::SQTL_LOG_ENABLE_SINK_QDEBUG = false;
  simpleqtlogger::SQTL_LOG_ENABLE_INFO = true;
  simpleqtlogger::SQTL_LOG_ENABLE_DEBUG = false;
  simpleqtlogger::SQTL_LOG_ENABLE_FUNCTION = true;
  simpleqtlogger::SQTL_LOG_ENABLE_FUNCTION_STACK_TRACE = true;

  // start and initialize the main task
  Task *task = new Task(&a);
  QObject::connect(task, SIGNAL(finished()), &a, SLOT(quit()));
  QTimer::singleShot(0, task, SLOT(init()));

  // initialize SimpleQtLogger (step 2/2)
  simpleqtlogger::SimpleQtLogger::getInstance()->setParent(task);

  return a.exec();
}
