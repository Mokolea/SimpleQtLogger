/*
  Test Simple Logger for Qt

  Mario Ban, 05.2015
  https://github.com/Mokolea/SimpleQtLogger

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

  Q_ASSERT_X(SQTL_VERSION >= SQTL_VERSION_CHECK(1, 1, 0), "main", "SimpleQtLogger version");

  // set log-features
  simpleqtlogger::ENABLE_LOG_SINK_FILE = true;
  simpleqtlogger::ENABLE_LOG_SINK_CONSOLE = false;
  simpleqtlogger::ENABLE_LOG_SINK_QDEBUG = false;
  simpleqtlogger::ENABLE_LOG_SINK_SIGNAL = true;
  simpleqtlogger::ENABLE_FUNCTION_STACK_TRACE = true;
  // set log-levels
  simpleqtlogger::ENABLE_LOG_LEVELS.logLevel_INFO = true;
  simpleqtlogger::ENABLE_LOG_LEVELS.logLevel_DEBUG = false;
  simpleqtlogger::ENABLE_LOG_LEVELS.logLevel_FUNCTION = true;
  simpleqtlogger::EnableLogLevels enableLogLevelsWarn = simpleqtlogger::ENABLE_LOG_LEVELS;
  enableLogLevelsWarn.logLevel_INFO = false;
  enableLogLevelsWarn.logLevel_FUNCTION = false;

  // initialize SimpleQtLogger (step 1/2)
  simpleqtlogger::SimpleQtLogger::createInstance(qApp)->setLogFileName("testSimpleQtLogger.log", 10*1000, 10);
  simpleqtlogger::SimpleQtLogger::getInstance()->setLogLevels_file(simpleqtlogger::ENABLE_LOG_LEVELS);
  //simpleqtlogger::SimpleQtLogger::getInstance()->setLogLevels_console(simpleqtlogger::ENABLE_LOG_LEVELS);
  simpleqtlogger::SimpleQtLogger::getInstance()->setLogLevels_qDebug(simpleqtlogger::ENABLE_LOG_LEVELS);
  simpleqtlogger::SimpleQtLogger::getInstance()->setLogLevels_signal(simpleqtlogger::ENABLE_LOG_LEVELS);
  //simpleqtlogger::SimpleQtLogger::getInstance()->addLogFilter_file(QRegularExpression("_id="));
  //simpleqtlogger::SimpleQtLogger::getInstance()->addLogFilter_file(QRegularExpression("n="));
  // 2nd file-log (levels: warn..fatal)
  simpleqtlogger::SimpleQtLogger::getInstance()->addSinkFileLog("warn");
  simpleqtlogger::SimpleQtLogger::getInstance()->setLogFileName("warn", "testSimpleQtLoggerWarn.log", 10*1000, 10);
  simpleqtlogger::SimpleQtLogger::getInstance()->setLogLevels_file("warn", enableLogLevelsWarn);

  // start and initialize the main task
  Task *task = new Task(&a);
  QObject::connect(task, SIGNAL(finished()), &a, SLOT(quit()));
  QTimer::singleShot(0, task, SLOT(init()));

  // test log forwarding (ENABLE_LOG_SINK_SIGNAL)
  //simpleqtlogger::SimpleQtLogger::getInstance()->connectSinkSignalLog(task, SLOT(slotLogForwarding(const QString&)));

  // initialize SimpleQtLogger (step 2/2)
  simpleqtlogger::SimpleQtLogger::getInstance()->setParent(task);

  return a.exec();
}
