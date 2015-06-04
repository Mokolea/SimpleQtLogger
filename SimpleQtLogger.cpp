/*
  Simple Logger for Qt

  Mario Ban, 05.2015

*/

#include "SimpleQtLogger.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QtDebug>

/* Log-level */
bool SQT_LOG_ENABLE_FATAL = true;
bool SQT_LOG_ENABLE_ERROR = true;
bool SQT_LOG_ENABLE_WARNING = true;
bool SQT_LOG_ENABLE_INFO = true;
bool SQT_LOG_ENABLE_DEBUG = false;
bool SQT_LOG_ENABLE_FUNCTION = false;

// -------------------------------------------------------------------------------------------------

// define one GLOBAL instance in main: SimpleQtLogger simpleQtLogger_;

// -------------------------------------------------------------------------------------------------

SimpleQtLogger::SimpleQtLogger()
  : _logFileSize(0)
  , _logFileNumber(0)
  , _stackDepth(0)
{
  qDebug("SimpleQtLogger::SimpleQtLogger");
}

SimpleQtLogger::~SimpleQtLogger()
{
  qDebug("SimpleQtLogger::~SimpleQtLogger");
  
  // TODO
  
}

void SimpleQtLogger::setLogFileName(const QString& logFileName, unsigned int logFileSize, unsigned int logFileNumber)
{
  qDebug("SimpleQtLogger::setLogFileName");
  _logFileName = logFileName;
  _logFileSize = logFileSize;
  _logFileNumber = logFileNumber;
  
  // TODO
  
}

void SimpleQtLogger::log(const QString& text, SQT_LOG_Level level, const QString& functionName, const char* fileName, unsigned int lineNumber)
{
  qDebug("SimpleQtLogger::log");

  (void)level;
  (void)functionName;
  (void)fileName;
  (void)lineNumber;

  // TODO: log file, rolling

  qDebug("%s", QString("%1: %2").arg(_logFileName).arg(text).toStdString().c_str());
}

void SimpleQtLogger::logFuncBegin(const QString& text, const QString& functionName, const QString& fileName, unsigned int lineNumber)
{
  qDebug("SimpleQtLogger::logFuncBegin");

  // TODO stack-trace depth (++ before) ... (thread-id-callback?)

  _stackDepth++;

  QString stackDepth;
  for(unsigned int i=0; i<_stackDepth; ++i) {
    stackDepth += " ";
  }

  log(QString("%1 \\ %2").arg(stackDepth).arg(text), SQT_LOG_FUNCTION, functionName, fileName.toStdString().c_str(), lineNumber);
}

void SimpleQtLogger::logFuncEnd(const QString& functionName, const QString& fileName, unsigned int lineNumber)
{
  qDebug("SimpleQtLogger::logFuncBegin");

  // TODO stack-trace depth (-- after) ... (thread-id-callback?)

  QString stackDepth;
  for(unsigned int i=0; i<_stackDepth; ++i) {
    stackDepth += " ";
  }

  log(QString("%1 \\ ").arg(stackDepth), SQT_LOG_FUNCTION, functionName, fileName.toStdString().c_str(), lineNumber);

  _stackDepth--;
}

// -------------------------------------------------------------------------------------------------

SimpleQtLoggerFunc::SimpleQtLoggerFunc(const QString& text, const QString& functionName, const QString& fileName, unsigned int lineNumber)
  : _functionName(functionName)
  , _fileName(fileName)
  , _lineNumber(lineNumber)
{
  qDebug("SimpleQtLoggerFunc::SimpleQtLoggerFunc");

  if(ENABLED_SQT_LOG_FUNCTION && SQT_LOG_ENABLE_FUNCTION) simpleQtLogger_.logFuncBegin(text, _functionName, _fileName, _lineNumber);
}

SimpleQtLoggerFunc::~SimpleQtLoggerFunc()
{
  qDebug("SimpleQtLoggerFunc::~SimpleQtLoggerFunc");

  if(ENABLED_SQT_LOG_FUNCTION && SQT_LOG_ENABLE_FUNCTION) simpleQtLogger_.logFuncEnd(_functionName, _fileName, _lineNumber);
}
