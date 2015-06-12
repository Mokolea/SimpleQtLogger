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
bool SQTL_LOG_ENABLE_FATAL = true;
bool SQTL_LOG_ENABLE_ERROR = true;
bool SQTL_LOG_ENABLE_WARNING = true;
bool SQTL_LOG_ENABLE_INFO = true;
bool SQTL_LOG_ENABLE_DEBUG = false;
bool SQTL_LOG_ENABLE_FUNCTION = false;

// -------------------------------------------------------------------------------------------------

SimpleQtLogger::SimpleQtLogger(QObject *parent)
  : QObject(parent)
  , _logFileRotationSize(0)
  , _logFileMaxNumber(0)
  , _stackDepth(0)
  , _logFile(0)
  , _logFileActivity(false)
{
  qDebug("SimpleQtLogger::SimpleQtLogger");

  Qt::ConnectionType connectionType = Qt::DirectConnection;
#if ENABLED_SQTL_LOG_SINK_FILE > 0
  QObject::connect(this, SIGNAL(signalLog(const QString&, const QString&, SQTL_LOG_Level, const QString&, const QString&, unsigned int)),
    this, SLOT(slotLog_File(const QString&, const QString&, SQTL_LOG_Level, const QString&, const QString&, unsigned int)), connectionType);
#endif
#if ENABLED_SQTL_LOG_SINK_QDEBUG > 0
  QObject::connect(this, SIGNAL(signalLog(const QString&, const QString&, SQTL_LOG_Level, const QString&, const QString&, unsigned int)),
    this, SLOT(slotLog_qDebug(const QString&, const QString&, SQTL_LOG_Level, const QString&, const QString&, unsigned int)), connectionType);
#endif
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

void SimpleQtLogger::setLogFileName(const QString& logFileName, unsigned int logFileRotationSize, unsigned int logFileMaxNumber)
{
  qDebug("SimpleQtLogger::setLogFileName");

  // check valid log-file name ending
  if(logFileName.right(4) != ".log") {
    qWarning() << "Name of log-file not ending with '.log'" << logFileName;
    return;
  }

  _logFileName = logFileName;
  _logFileRotationSize = logFileRotationSize;
  _logFileMaxNumber = logFileMaxNumber;

  // check valid number ranges
  if(_logFileRotationSize < 100) {
    _logFileRotationSize = 100;
  }
  if(_logFileMaxNumber < 1) {
    _logFileMaxNumber = 1;
  }
  if(_logFileMaxNumber > 99) {
    _logFileMaxNumber = 99;
  }

  checkLogFileOpen();

  log("Start logger", SQTL_LOG_INFO, "", "", 0);
}

void SimpleQtLogger::log(const QString& text, SQTL_LOG_Level level, const QString& functionName, const char* fileName, unsigned int lineNumber)
{
  // qDebug("SimpleQtLogger::log");

  // time-stamp
  QDateTime dateTime = QDateTime::currentDateTime(); // or better use QDateTime::currentDateTimeUtc() instead
  QString ts = dateTime.toString("yyyy-MM-dd hh:mm:ss.zzz");

  emit signalLog(ts, text, level, functionName, fileName, lineNumber);
}

void SimpleQtLogger::slotLog_File(const QString& ts, const QString& text, SQTL_LOG_Level level, const QString& functionName, const QString& fileName, unsigned int lineNumber)
{
  // qDebug("SimpleQtLogger::slotLog_File");

  if(functionName.isEmpty()) {
    // stream (append) to log file
    if(_logFile && _logFile->isOpen()) {
      QTextStream out(_logFile);
      out << ts << " [" << LOG_LEVEL_CHAR[level] << "] " << (text.isEmpty() ? "?" : text.trimmed()) << '\n';
      _logFileActivity = true;
    }
    return;
  }

  // stream (append) to log file
  if(_logFile && _logFile->isOpen()) {
    QTextStream out(_logFile);
    out << ts << " [" << LOG_LEVEL_CHAR[level] << "] " << (text.isEmpty() ? "?" : text.trimmed()) << " (" << functionName << "@" << fileName << ":" << lineNumber << ")" << '\n';
    _logFileActivity = true;
  }
}

void SimpleQtLogger::slotLog_qDebug(const QString& ts, const QString& text, SQTL_LOG_Level level, const QString& functionName, const QString& fileName, unsigned int lineNumber)
{
  // qDebug("SimpleQtLogger::slotLog_qDebug");

  if(functionName.isEmpty()) {
    qDebug("%s", QString("%1 [%2] %3").arg(ts).arg(LOG_LEVEL_CHAR[level]).arg(text.isEmpty() ? "?" : text.trimmed()).toStdString().c_str());
    return;
  }

  qDebug("%s", QString("%1 [%2] %3 (%4@%5:%6)").arg(ts).arg(LOG_LEVEL_CHAR[level]).arg(text.isEmpty() ? "?" : text.trimmed()).arg(functionName).arg(fileName).arg(lineNumber).toStdString().c_str());
}

#if ENABLED_SQTL_LOG_FUNCTION > 0

void SimpleQtLogger::logFuncBegin(const QString& text, const QString& functionName, const QString& fileName, unsigned int lineNumber)
{
  // qDebug("SimpleQtLogger::logFuncBegin");

  _stackDepth++; // adjust stack-trace depth

  QString stackDepth("");
  for(unsigned int i=1; i<_stackDepth; ++i) {
    stackDepth += STACK_DEPTH_CHAR;
  }
  if(text.isEmpty()) {
    log(QString("%1\\").arg(stackDepth), SQTL_LOG_FUNCTION, functionName, fileName.toStdString().c_str(), lineNumber);
  }
  else {
    log(QString("%1\\ %2").arg(stackDepth).arg(text), SQTL_LOG_FUNCTION, functionName, fileName.toStdString().c_str(), lineNumber);
  }
}

void SimpleQtLogger::logFuncEnd(const QString& text, const QString& functionName, const QString& fileName, unsigned int lineNumber)
{
  // qDebug("SimpleQtLogger::logFuncEnd");

  QString stackDepth("");
  for(unsigned int i=1; i<_stackDepth; ++i) {
    stackDepth += STACK_DEPTH_CHAR;
  }
  if(text.isEmpty()) {
    log(QString("%1/").arg(stackDepth), SQTL_LOG_FUNCTION, functionName, fileName.toStdString().c_str(), lineNumber);
  }
  else {
    log(QString("%1/ %2").arg(stackDepth).arg(text), SQTL_LOG_FUNCTION, functionName, fileName.toStdString().c_str(), lineNumber);
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
  qint64 logFileRotationSize = logFileInfo.size();

  if(logFileRotationSize < _logFileRotationSize) {
    QTimer::singleShot(CHECK_LOG_FILE_ACTIVITY_INTERVAL, this, SLOT(slotCheckLogFileActivity()));
    return;
  }
  log(QString("Current log-file size=%1 (rolling-size=%2) --> rolling").arg(logFileRotationSize).arg(_logFileRotationSize), SQTL_LOG_INFO, "", "", 0);

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

#if ENABLED_SQTL_LOG_FUNCTION > 0

SimpleQtLoggerFunc::SimpleQtLoggerFunc(const QString& text, const QString& functionName, const QString& fileName, unsigned int lineNumber)
  : _text(text)
  , _functionName(functionName)
  , _fileName(fileName)
  , _lineNumber(lineNumber)
{
  // qDebug("SimpleQtLoggerFunc::SimpleQtLoggerFunc");
  if(ENABLED_SQTL_LOG_FUNCTION && SQTL_LOG_ENABLE_FUNCTION) simpleQtLogger_.logFuncBegin(_text, _functionName, _fileName, _lineNumber);
}

SimpleQtLoggerFunc::~SimpleQtLoggerFunc()
{
  // qDebug("SimpleQtLoggerFunc::~SimpleQtLoggerFunc");
  if(ENABLED_SQTL_LOG_FUNCTION && SQTL_LOG_ENABLE_FUNCTION) simpleQtLogger_.logFuncEnd(_text, _functionName, _fileName, _lineNumber);
}

#endif
