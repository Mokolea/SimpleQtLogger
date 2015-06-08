/*
  Simple Logger for Qt

  Mario Ban, 05.2015

  GNU General Public License v2.0
  Copyright (C) 2015 Mario Ban
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

SimpleQtLogger::SimpleQtLogger(QObject *parent)
  : QObject(parent)
  , _logFileSize(0)
  , _logFileMaxNumber(0)
  , _stackDepth(0)
  , _logFile(0)
  , _logFileActivity(false)
{
  qDebug("SimpleQtLogger::SimpleQtLogger");

  Qt::ConnectionType connectionType = Qt::DirectConnection;
  QObject::connect(this, SIGNAL(signalLog(const QString&, SQT_LOG_Level, const QString&, const QString&, unsigned int)),
    this, SLOT(slotLog(const QString&, SQT_LOG_Level, const QString&, const QString&, unsigned int)), connectionType);
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

  // check valid log-file name ending
  if(_logFileName.right(4) != ".log") {
    qWarning() << "Name of log-file not ending with '.log'" << _logFileName;
    return;
  }

  // check valid number ranges
  if(_logFileSize < 100) {
    _logFileSize = 100;
  }
  if(_logFileMaxNumber < 1) {
    _logFileMaxNumber = 1;
  }
  if(_logFileMaxNumber > 99) {
    _logFileMaxNumber = 99;
  }

  checkLogFileOpen();

  log("Start logger", SQT_LOG_INFO, "", "", 0);
}

void SimpleQtLogger::log(const QString& text, SQT_LOG_Level level, const QString& functionName, const char* fileName, unsigned int lineNumber)
{
  // qDebug("SimpleQtLogger::log");

  emit signalLog(text, level, functionName, fileName, lineNumber);
}

void SimpleQtLogger::slotLog(const QString& text, SQT_LOG_Level level, const QString& functionName, const QString& fileName, unsigned int lineNumber)
{
  // qDebug("SimpleQtLogger::slotLog");

  // time-stamp
  QDateTime dateTime = QDateTime::currentDateTime(); // or better use QDateTime::currentDateTimeUtc() instead
  QString ts = dateTime.toString("yyyy-MM-dd hh:mm:ss.zzz");

  if(functionName.isEmpty()) {
    // stream (append) to log file
    if(_logFile && _logFile->isOpen()) {
      QTextStream out(_logFile);
      out << ts << " [" << LOG_LEVEL_CHAR[level] << "] " << (text.isEmpty() ? "?" : text.trimmed()) << '\n';
      _logFileActivity = true;
    }
    else {
      qDebug("%s", QString("%4: %1 [%2] %3").arg(ts).arg(LOG_LEVEL_CHAR[level]).arg(text.isEmpty() ? "?" : text.trimmed()).arg(_logFileName).toStdString().c_str());
    }
    return;
  }

  // stream (append) to log file
  if(_logFile && _logFile->isOpen()) {
    QTextStream out(_logFile);
    out << ts << " [" << LOG_LEVEL_CHAR[level] << "] " << (text.isEmpty() ? "?" : text.trimmed()) << " (" << functionName << "@" << fileName << ":" << lineNumber << ")" << '\n';
    _logFileActivity = true;
  }
  else {
    qDebug("%s", QString("%7: %1 [%2] %3 (%4@%5:%6)").arg(ts).arg(LOG_LEVEL_CHAR[level]).arg(text.isEmpty() ? "?" : text.trimmed()).arg(functionName).arg(fileName).arg(lineNumber).arg(_logFileName).toStdString().c_str());
  }
}

#if ENABLED_SQT_LOG_FUNCTION > 0

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

#endif

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

  // open log-file
  _logFile = new QFile(_logFileName);
  if(!_logFile->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
    delete _logFile;
    _logFile = 0;
    qWarning() << "Open log-file failed!" << _logFileName;
  }

  if(!_logFile) {
    return;
  }

  qDebug() << "Current log-file:" << _logFileName;

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
  qint64 logFileSize = logFileInfo.size();

  if(logFileSize < _logFileSize) {
    QTimer::singleShot(CHECK_LOG_FILE_ACTIVITY_INTERVAL, this, SLOT(slotCheckLogFileActivity()));
    return;
  }
  log(QString("Current log-file size=%1 (rolling-size=%2) --> rolling").arg(logFileSize).arg(_logFileSize), SQT_LOG_INFO, "", "", 0);

  // handle file rolling

  // delete last file
  QString logFileName = _logFileName;
  logFileName.replace(".log", QString("_%1.log").arg(_logFileMaxNumber, 2, 10, QLatin1Char('0')));
  if(QFile::exists(logFileName)) {
    if(QFile::remove(logFileName)) {
      qDebug() << "Removed" << logFileName;
    }
    else {
      qWarning() << "ERROR: Remove" << logFileName;
    }
  }

  // rolling files
  for(int i=_logFileMaxNumber-1; i>0; --i) {
    QString logFileNameFrom = _logFileName;
    logFileNameFrom.replace(".log", QString("_%1.log").arg(i, 2, 10, QLatin1Char('0')));
    QString logFileNameTo = _logFileName;
    logFileNameTo.replace(".log", QString("_%1.log").arg(i+1, 2, 10, QLatin1Char('0')));
    if(QFile::exists(logFileNameFrom)) {
      if(QFile::rename(logFileNameFrom, logFileNameTo)) {
        qDebug() << "Moved" << logFileNameFrom << "to" << logFileNameTo;
      }
      else {
        qWarning() << "ERROR: Move" << logFileNameFrom << "to" << logFileNameTo;
      }
    }
  }

  _logFile->close();

  // move first file
  QString logFileNameTo = _logFileName;
  logFileNameTo.replace(".log", QString("_%1.log").arg(1, 2, 10, QLatin1Char('0')));
  if(QFile::exists(_logFileName)) {
    if(QFile::rename(_logFileName, logFileNameTo)) {
      qDebug() << "Moved" << _logFileName << "to" << logFileNameTo;
    }
    else {
      qWarning() << "ERROR: Move" << _logFileName << "to" << logFileNameTo;
    }
  }

  checkLogFileOpen();
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

#if ENABLED_SQT_LOG_FUNCTION > 0

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

#endif
