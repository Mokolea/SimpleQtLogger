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
  simpleqtlogger::SQTL_LOG_ENABLE_SINK_FILE = true;
  simpleqtlogger::SQTL_LOG_ENABLE_SINK_CONSOLE = false;
  simpleqtlogger::SQTL_LOG_ENABLE_SINK_QDEBUG = false;
  simpleqtlogger::SQTL_LOG_ENABLE.INFO = true;
  simpleqtlogger::SQTL_LOG_ENABLE.DEBUG = false;
  simpleqtlogger::SQTL_LOG_ENABLE.FUNCTION = true;
  simpleqtlogger::SQTL_LOG_ENABLE_FUNCTION_STACK_TRACE = true;

  // start and initialize the main widget
  Dialog w(0);
  w.show();

  // initialize SimpleQtLogger (step 2/2)
  // simpleqtlogger::SimpleQtLogger::getInstance()->setParent(&w);

  return a.exec();
}
