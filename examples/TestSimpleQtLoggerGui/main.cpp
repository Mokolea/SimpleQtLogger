/*
  Test Simple Logger for Qt

  Mario Ban, 06.2015

  GNU Lesser General Public License v2.1
  Copyright (C) 2015 Mario Ban
*/

#include <QApplication>
#include <QDir>

#include "dialog.h"
#include "simpleQtLogger.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  // initialize SimpleQtLogger (step 1/2)
  simpleqtlogger::SimpleQtLogger::createInstance(qApp)->setLogFormat_file("<TS> [<LL>] <TEXT> (<FUNC>@<FILE>:<LINE>)", "<TS> [<LL>] <TEXT>");
  simpleqtlogger::SimpleQtLogger::getInstance()->setLogFileName(QDir::home().filePath("Documents/Qt/testSimpleQtLoggerGui.log"), 10*1024, 10);
  simpleqtlogger::ENABLE_LOG_SINK_FILE = true;
  simpleqtlogger::ENABLE_LOG_SINK_CONSOLE = false;
  simpleqtlogger::ENABLE_LOG_SINK_QDEBUG = false;
  simpleqtlogger::ENABLE_LOG_LEVELS.logLevel_INFO = true;
  simpleqtlogger::ENABLE_LOG_LEVELS.logLevel_DEBUG = false;
  simpleqtlogger::ENABLE_LOG_LEVELS.logLevel_FUNCTION = true;
  simpleqtlogger::SimpleQtLogger::getInstance()->setLogLevels_file(simpleqtlogger::ENABLE_LOG_LEVELS);
  simpleqtlogger::SimpleQtLogger::getInstance()->setLogLevels_console(simpleqtlogger::ENABLE_LOG_LEVELS);
  simpleqtlogger::SimpleQtLogger::getInstance()->setLogLevels_qDebug(simpleqtlogger::ENABLE_LOG_LEVELS);
  simpleqtlogger::ENABLE_FUNCTION_STACK_TRACE = true;

  // start and initialize the main widget
  Dialog w(0);
  w.show();

  // initialize SimpleQtLogger (step 2/2)
  // simpleqtlogger::SimpleQtLogger::getInstance()->setParent(&w);

  return a.exec();
}
