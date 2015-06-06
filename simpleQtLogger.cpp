/*
  Simple Logger for Qt

  Mario Ban, 05.2015

*/

#include "simpleQtLogger.h"

#include <QCoreApplication>
#include <QTimer>
#include <QDateTime>
#include <QFileInfo>
#include <QtDebug>

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

SimpleQtLogger::SimpleQtLogger(QObject *parent)
  : QObject(parent)
  , _logFileSize(0)
  , _logFileMaxNumber(0)
  , _stackDepth(0)
  , _logFile(0)
  , _logFileActivity(false)
{
  qDebug("SimpleQtLogger::SimpleQtLogger");
}

SimpleQtLogger::~SimpleQtLogger()
{
  qDebug("SimpleQtLogger::~SimpleQtLogger");

  // check close log file
  if(_logFile) {
    if(_logFile->isOpen()) {
      _logFile->close();
    }
    delete _logFile;
    _logFile = 0;
  }
}

void SimpleQtLogger::setLogFileName(const QString& logFileName, unsigned int logFileSize, unsigned int logFileMaxNumber)
{
  qDebug("SimpleQtLogger::setLogFileName");

  _logFileName = logFileName;
  _logFileSize = logFileSize;
  _logFileMaxNumber = logFileMaxNumber;

  checkLogFileOpen();
}

void SimpleQtLogger::log(const QString& text, SQT_LOG_Level level, const QString& functionName, const char* fileName, unsigned int lineNumber)
{
  // qDebug("SimpleQtLogger::log");

  // time-stamp
  QDateTime dateTime = QDateTime::currentDateTime(); // or better use QDateTime::currentDateTimeUtc() instead
  QString ts = dateTime.toString("yyyy-MM-dd hh:mm:ss.zzz");

  // stream (append) to log file
  if(_logFile && _logFile->isOpen()) {
    QTextStream out(_logFile);
    out << ts << " [" << LOG_LEVEL_CHAR[level] << "] " << (text.isEmpty() ? "?" : text) << " (" << functionName << "@" << fileName << ":" << lineNumber << ")" << '\n';

    _logFileActivity = true;
  }
  else {
    qDebug("%s", QString("%7: %1 [%2] %3 (%4@%5:%6)").arg(ts).arg(LOG_LEVEL_CHAR[level]).arg(text.isEmpty() ? "?" : text).arg(functionName).arg(fileName).arg(lineNumber).arg(_logFileName).toStdString().c_str());
  }
}

void SimpleQtLogger::logFuncBegin(const QString& text, const QString& functionName, const QString& fileName, unsigned int lineNumber)
{
  // qDebug("SimpleQtLogger::logFuncBegin");

  // TODO stack-trace depth (++ before) ... (thread-id-callback?)

  _stackDepth++; // adjust stack-trace depth

  QString stackDepth("");
  for(unsigned int i=1; i<_stackDepth; ++i) {
    stackDepth += STACK_DEPTH_CHAR;
  }
  if(text.isEmpty()) {
    log(QString("%1\\").arg(stackDepth), SQT_LOG_FUNCTION, functionName, fileName.toStdString().c_str(), lineNumber);
  }
  else {
    log(QString("%1\\ %2").arg(stackDepth).arg(text), SQT_LOG_FUNCTION, functionName, fileName.toStdString().c_str(), lineNumber);
  }
}

void SimpleQtLogger::logFuncEnd(const QString& text, const QString& functionName, const QString& fileName, unsigned int lineNumber)
{
  // qDebug("SimpleQtLogger::logFuncEnd");

  // TODO stack-trace depth (-- after) ... (thread-id-callback?)

  QString stackDepth("");
  for(unsigned int i=1; i<_stackDepth; ++i) {
    stackDepth += STACK_DEPTH_CHAR;
  }
  if(text.isEmpty()) {
    log(QString("%1/").arg(stackDepth), SQT_LOG_FUNCTION, functionName, fileName.toStdString().c_str(), lineNumber);
  }
  else {
    log(QString("%1/ %2").arg(stackDepth).arg(text), SQT_LOG_FUNCTION, functionName, fileName.toStdString().c_str(), lineNumber);
  }

  _stackDepth--; // adjust stack-trace depth
}

void SimpleQtLogger::checkLogFileOpen()
{
  // qDebug("SimpleQtLogger::checkLogFileOpen");

  // check close and open log file
  if(_logFile) {
    if(_logFile->isOpen()) {
      _logFile->close();
    }
    delete _logFile;
  }

  // TODO check existing files ... open latest (modification-time) file

  _logFile = new QFile(_logFileName);
  if(!_logFile->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
    delete _logFile;
    _logFile = 0;
    qWarning() << "Open log-file failed!" << _logFileName;
  }

  if(!_logFile) {
    return;
  }

  QTimer::singleShot(CHECK_LOG_FILE_ACTIVITY_INTERVAL, this, SLOT(slotCheckLogFileActivity()));
}

void SimpleQtLogger::checkLogFileRolling()
{
  // qDebug("SimpleQtLogger::checkLogFileRolling");

  if(!_logFile) {
    return;
  }

  // check current log-file size
  QFileInfo logFileInfo(*_logFile);
  LogInfo(QString("Current log-file size=%1").arg(logFileInfo.size()));

  // TODO: handle (initiate) file rolling

  QTimer::singleShot(CHECK_LOG_FILE_ACTIVITY_INTERVAL, this, SLOT(slotCheckLogFileActivity()));
}

void SimpleQtLogger::slotCheckLogFileActivity()
{
  // qDebug("SimpleQtLogger::slotCheckLogFileActivity");

  if(!_logFile) {
    return;
  }

  if(_logFileActivity) {
    _logFileActivity = false;
    checkLogFileRolling();
    return;
  }

  QTimer::singleShot(CHECK_LOG_FILE_ACTIVITY_INTERVAL, this, SLOT(slotCheckLogFileActivity()));
}

// -------------------------------------------------------------------------------------------------

SimpleQtLoggerFunc::SimpleQtLoggerFunc(const QString& text, const QString& functionName, const QString& fileName, unsigned int lineNumber)
  : _text(text)
  , _functionName(functionName)
  , _fileName(fileName)
  , _lineNumber(lineNumber)
{
  // qDebug("SimpleQtLoggerFunc::SimpleQtLoggerFunc");
  if(ENABLED_SQT_LOG_FUNCTION && SQT_LOG_ENABLE_FUNCTION) simpleQtLogger_.logFuncBegin(_text, _functionName, _fileName, _lineNumber);
}

SimpleQtLoggerFunc::~SimpleQtLoggerFunc()
{
  // qDebug("SimpleQtLoggerFunc::~SimpleQtLoggerFunc");
  if(ENABLED_SQT_LOG_FUNCTION && SQT_LOG_ENABLE_FUNCTION) simpleQtLogger_.logFuncEnd(_text, _functionName, _fileName, _lineNumber);
}
