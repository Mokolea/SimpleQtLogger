/*
  Simple Logger for Qt

  Mario Ban, 05.2015

  GNU Lesser General Public License v2.1
  Copyright (C) 2015 Mario Ban
*/

#include "simpleQtLogger.h"

#include <QCoreApplication>
#include <QTimer>
#include <QDateTime>
#include <QFileInfo>
#include <QtDebug>

namespace simpleqtlogger {

/* Log-sinks */
bool SQTL_LOG_ENABLE_SINK_FILE = true;
bool SQTL_LOG_ENABLE_SINK_CONSOLE = false;
bool SQTL_LOG_ENABLE_SINK_QDEBUG = false;

/* Log-level */
SQTL_LOG_Level_enable SQTL_LOG_ENABLE = { true, true, true, true, false, false };

/* Log-function stack-trace */
bool SQTL_LOG_ENABLE_FUNCTION_STACK_TRACE = true;

/* Console color */
bool SQTL_LOG_ENABLE_CONSOLE_COLOR = true;

// -------------------------------------------------------------------------------------------------

SinkFileLog::SinkFileLog(QObject *parent, const QString& role)
  : QObject(parent)
  , _role(role)
  , _logFileRotationSize(0)
  , _logFileMaxNumber(0)
  , _logFormat(DEFAULT_LOG_FORMAT)
  , _logFormatInt(DEFAULT_LOG_FORMAT_INTERNAL)
  , _logFile(0)
  , _logFileActivity(false)
{
  // qDebug("SinkFileLog::SinkFileLog");
}

SinkFileLog::~SinkFileLog()
{
  // qDebug("SinkFileLog::~SinkFileLog");

  // check close log file
  if(_logFile) {
    if(_logFile->isOpen()) {
      _logFile->close();
    }
    delete _logFile;
    _logFile = 0;
  }
}

void SinkFileLog::setLogFormat(const QString& logFormat, const QString& logFormatInt)
{
  // qDebug("SinkFileLog::setLogFormat");

  _logFormat = logFormat;
  _logFormatInt = logFormatInt;
}

bool SinkFileLog::setLogFileName(const QString& logFileName, unsigned int logFileRotationSize, unsigned int logFileMaxNumber)
{
  // qDebug("SinkFileLog::setLogFileName");

  // check valid log-file name ending
  if(logFileName.right(4) != ".log") {
    qWarning() << "Name of log-file not ending with '.log'" << logFileName << "role" << _role;
    return false;
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

  return checkLogFileOpen();
}

void SinkFileLog::slotLog_File(const QString& ts, const QString& tid, const QString& text, SQTL_LOG_Level level, const QString& functionName, const QString& fileName, unsigned int lineNumber)
{
  // qDebug("SinkFileLog::slotLog_File");

  if(!SQTL_LOG_ENABLE_SINK_FILE) {
    return;
  }

  QString textIsEmpty("?");
  if(level == SQTL_LOG_FUNCTION) {
    textIsEmpty = "-";
  }

  // stream (append) to log file
  if(_logFile && _logFile->isOpen()) {
    QTextStream out(_logFile);
    out.setCodec("UTF-8");
    if(functionName.isEmpty()) {
      out << QString(_logFormatInt).replace("<TS>", ts).replace("<TID>", tid).replace("<TID32>", tid.right(4*2)).replace("<LL>", QString(LOG_LEVEL_CHAR[level])).replace("<TEXT>", text.isEmpty() ? textIsEmpty : text.trimmed()) << '\n';
    }
    else {
      out << QString(_logFormat).replace("<TS>", ts).replace("<TID>", tid).replace("<TID32>", tid.right(4*2)).replace("<LL>", QString(LOG_LEVEL_CHAR[level])).replace("<FUNC>", functionName).replace("<FILE>", fileName).replace("<LINE>", QString("%1").arg(lineNumber)).replace("<TEXT>", text.isEmpty() ? textIsEmpty : text.trimmed()) << '\n';
    }
    _logFileActivity = true;
  }
}

bool SinkFileLog::checkLogFileOpen()
{
  // qDebug("SinkFileLog::checkLogFileOpen");

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
    qWarning() << "Open log-file failed!" << _logFileName << "role" << _role;
  }

  if(!_logFile) {
    return false;
  }

  qDebug() << "Current log-file:" << _logFileName << "role" << _role;

  QTimer::singleShot(CHECK_LOG_FILE_ACTIVITY_INTERVAL, this, SLOT(slotCheckLogFileActivity()));

  return true;
}

void SinkFileLog::checkLogFileRolling()
{
  // qDebug("SinkFileLog::checkLogFileRolling");

  if(!_logFile) {
    return;
  }

  // check current log-file size
  QFileInfo logFileInfo(*_logFile);
  qint64 logFileSize = logFileInfo.size();

  if(logFileSize < _logFileRotationSize) {
    QTimer::singleShot(CHECK_LOG_FILE_ACTIVITY_INTERVAL, this, SLOT(slotCheckLogFileActivity()));
    return;
  }
  slotLog_File(SimpleQtLogger::timeStamp(), SimpleQtLogger::threadId(), QString("Current log-file '%1' size=%2 (rotation-size=%3) --> rolling").arg(_role).arg(logFileSize).arg(_logFileRotationSize), SQTL_LOG_INFO, "", "", 0);

  QTime timeRolling;
  timeRolling.start();

  // handle file rolling

  // delete last file
  QString logFileName = _logFileName;
  logFileName.replace(".log", QString("_%1.log").arg(_logFileMaxNumber, 2, 10, QLatin1Char('0')));
  if(QFile::exists(logFileName)) {
    if(QFile::remove(logFileName)) {
      qDebug() << "Removed" << logFileName << "role" << _role;
    }
    else {
      qWarning() << "ERROR: Remove" << logFileName << "role" << _role;
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
        qDebug() << "Moved" << logFileNameFrom << "to" << logFileNameTo << "role" << _role;
      }
      else {
        qWarning() << "ERROR: Move" << logFileNameFrom << "to" << logFileNameTo << "role" << _role;
      }
    }
  }

  _logFile->close();

  // move first file
  QString logFileNameTo = _logFileName;
  logFileNameTo.replace(".log", QString("_%1.log").arg(1, 2, 10, QLatin1Char('0')));
  if(QFile::exists(_logFileName)) {
    if(QFile::rename(_logFileName, logFileNameTo)) {
      qDebug() << "Moved" << _logFileName << "to" << logFileNameTo << "role" << _role;
    }
    else {
      qWarning() << "ERROR: Move" << _logFileName << "to" << logFileNameTo << "role" << _role;
    }
  }

  checkLogFileOpen();

  slotLog_File(SimpleQtLogger::timeStamp(), SimpleQtLogger::threadId(), QString("Log-file '%1' rolling done (time elapsed: %2 ms)").arg(_role).arg(timeRolling.elapsed()), SQTL_LOG_INFO, "", "", 0);
}

void SinkFileLog::slotCheckLogFileActivity()
{
  // qDebug("SinkFileLog::slotCheckLogFileActivity");

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

SimpleQtLogger* SimpleQtLogger::instance = 0;

SimpleQtLogger* SimpleQtLogger::createInstance(QObject *parent)
{
  if(instance) {
    delete instance;
  }
  instance = new SimpleQtLogger(parent);
  return instance;
}

SimpleQtLogger* SimpleQtLogger::getInstance()
{
  return instance;
}

SimpleQtLogger::SimpleQtLogger(QObject *parent)
  : QObject(parent)
  , _logFormat_console(DEFAULT_LOG_FORMAT)
  , _logFormat_qDebug(DEFAULT_LOG_FORMAT)
  , _logFormatInt_console(DEFAULT_LOG_FORMAT_INTERNAL)
  , _logFormatInt_qDebug(DEFAULT_LOG_FORMAT_INTERNAL)
{
  qDebug("SimpleQtLogger::SimpleQtLogger"); // TODO comment this

  qRegisterMetaType<SQTL_LOG_Level>("SQTL_LOG_Level"); // to use type in Qt::QueuedConnection

  // Qt::ConnectionType is Qt::AutoConnection (Default)
  // If the receiver lives in the thread that emits the signal, Qt::DirectConnection is used.
  // Otherwise, Qt::QueuedConnection is used. The connection type is determined when the signal is emitted.
#if ENABLED_SQTL_LOG_SINK_CONSOLE > 0
  QObject::connect(this, SIGNAL(signalLog(const QString&, const QString&, const QString&, SQTL_LOG_Level, const QString&, const QString&, unsigned int)),
    this, SLOT(slotLog_console(const QString&, const QString&, const QString&, SQTL_LOG_Level, const QString&, const QString&, unsigned int)));
#endif
#if ENABLED_SQTL_LOG_SINK_QDEBUG > 0
  QObject::connect(this, SIGNAL(signalLog(const QString&, const QString&, const QString&, SQTL_LOG_Level, const QString&, const QString&, unsigned int)),
    this, SLOT(slotLog_qDebug(const QString&, const QString&, const QString&, SQTL_LOG_Level, const QString&, const QString&, unsigned int)));
#endif

  addSinkFileLog("main");
}

SimpleQtLogger::~SimpleQtLogger()
{
  qDebug("SimpleQtLogger::~SimpleQtLogger"); // TODO comment this
}

void SimpleQtLogger::addSinkFileLog(const QString& role)
{
  // qDebug("SimpleQtLogger::addSinkFileLog");

  if(_sinkFileLogMap.contains(role)) {
    return;
  }

  _sinkFileLogMap[role] = new SinkFileLog(this, role);

#if ENABLED_SQTL_LOG_SINK_FILE > 0
  QObject::connect(this, SIGNAL(signalLog(const QString&, const QString&, const QString&, SQTL_LOG_Level, const QString&, const QString&, unsigned int)),
    _sinkFileLogMap[role], SLOT(slotLog_File(const QString&, const QString&, const QString&, SQTL_LOG_Level, const QString&, const QString&, unsigned int)));
#endif
}

void SimpleQtLogger::setLogFormat_file(const QString& logFormat, const QString& logFormatInt)
{
  // qDebug("SimpleQtLogger::setLogFormat_file");

  setLogFormat_file("main", logFormat, logFormatInt);
}

void SimpleQtLogger::setLogFormat_file(const QString& role, const QString& logFormat, const QString& logFormatInt)
{
  // qDebug("SimpleQtLogger::setLogFormat_file");

  if(_sinkFileLogMap.contains(role)) {
    _sinkFileLogMap[role]->setLogFormat(logFormat, logFormatInt);
  }
}

void SimpleQtLogger::setLogFormat_console(const QString& logFormat, const QString& logFormatInt)
{
  // qDebug("SimpleQtLogger::setLogFormat_console");

  _logFormat_console = logFormat;
  _logFormatInt_console = logFormatInt;
}

void SimpleQtLogger::setLogFormat_qDebug(const QString& logFormat, const QString& logFormatInt)
{
  // qDebug("SimpleQtLogger::setLogFormat_qDebug");

  _logFormat_qDebug = logFormat;
  _logFormatInt_qDebug = logFormatInt;
}

bool SimpleQtLogger::setLogFileName(const QString& logFileName, unsigned int logFileRotationSize, unsigned int logFileMaxNumber)
{
  // qDebug("SimpleQtLogger::setLogFileName");

  return setLogFileName("main", logFileName, logFileRotationSize, logFileMaxNumber);
}

bool SimpleQtLogger::setLogFileName(const QString& role, const QString& logFileName, unsigned int logFileRotationSize, unsigned int logFileMaxNumber)
{
  // qDebug("SimpleQtLogger::setLogFileName");

  if(_sinkFileLogMap.contains(role) && _sinkFileLogMap[role]->setLogFileName(logFileName, logFileRotationSize, logFileMaxNumber)) {
    log(QString("Start file-log '%1'").arg(role), SQTL_LOG_INFO, "", "", 0);
    return true;
  }
  return false;
}

QString SimpleQtLogger::timeStamp()
{
  // qDebug("SimpleQtLogger::timeStamp");

  // time-stamp
  QDateTime dateTime = QDateTime::currentDateTime(); // or better use QDateTime::currentDateTimeUtc() instead
  return dateTime.toString("yyyy-MM-dd hh:mm:ss.zzz");
}

QString SimpleQtLogger::threadId()
{
  // qDebug("SimpleQtLogger::threadId");

  // thread-id in hexadecimal
  return QString("%1").arg((unsigned long int)QThread::currentThreadId(),16,16,QLatin1Char('0')); // field-with for 64bit
}

void SimpleQtLogger::log(const QString& text, SQTL_LOG_Level level, const QString& functionName, const char* fileName, unsigned int lineNumber)
{
  // qDebug("SimpleQtLogger::log");

  // thread-safe

  emit signalLog(timeStamp(), threadId(), text, level, functionName, fileName, lineNumber);
}

#if ENABLED_SQTL_LOG_FUNCTION > 0

void SimpleQtLogger::logFuncBegin(const QString& text, const QString& functionName, const QString& fileName, unsigned int lineNumber)
{
  // qDebug("SimpleQtLogger::logFuncBegin");

  // thread-safe

  if(!SQTL_LOG_ENABLE_FUNCTION_STACK_TRACE) {
    log(QString("%1").arg(text), SQTL_LOG_FUNCTION, functionName, fileName.toStdString().c_str(), lineNumber);
    return;
  }

  unsigned int stackDepthThread;
  {
    QMutexLocker locker(&_mutex);
    // adjust stack-trace depth (++ before log)
    unsigned int& value = _stackDepth[(unsigned long int)QThread::currentThreadId()];
    stackDepthThread = ++value;
  }

  QString stackDepth("");
  for(unsigned int i=1; i<stackDepthThread; ++i) {
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

  // thread-safe

  if(!SQTL_LOG_ENABLE_FUNCTION_STACK_TRACE) {
    return;
  }

  unsigned int stackDepthThread;
  {
    QMutexLocker locker(&_mutex);
    // adjust stack-trace depth (-- after log)
    unsigned int& value = _stackDepth[(unsigned long int)QThread::currentThreadId()];
    stackDepthThread = value--;
  }

  QString stackDepth("");
  for(unsigned int i=1; i<stackDepthThread; ++i) {
    stackDepth += STACK_DEPTH_CHAR;
  }
  if(text.isEmpty()) {
    log(QString("%1/").arg(stackDepth), SQTL_LOG_FUNCTION, functionName, fileName.toStdString().c_str(), lineNumber);
  }
  else {
    log(QString("%1/ %2").arg(stackDepth).arg(text), SQTL_LOG_FUNCTION, functionName, fileName.toStdString().c_str(), lineNumber);
  }
}

#endif

void SimpleQtLogger::slotLog_console(const QString& ts, const QString& tid, const QString& text, SQTL_LOG_Level level, const QString& functionName, const QString& fileName, unsigned int lineNumber)
{
  // qDebug("SimpleQtLogger::slotLog_console");

  if(!SQTL_LOG_ENABLE_SINK_CONSOLE) {
    return;
  }

  QString textIsEmpty("?");
  if(level == SQTL_LOG_FUNCTION) {
    textIsEmpty = "-";
  }

  QTextStream out(stdout);
  // out.setCodec("UTF-8");
  if(SQTL_LOG_ENABLE_CONSOLE_COLOR) {
    // change some foreground (background) colors
    if(level == SQTL_LOG_FATAL) {
      out << CONSOLE_COLOR_ANSI_ESC_CODES_FATAL;
    }
    else if(level == SQTL_LOG_ERROR) {
      out << CONSOLE_COLOR_ANSI_ESC_CODES_ERROR;
    }
    else if(level == SQTL_LOG_WARNING) {
      out << CONSOLE_COLOR_ANSI_ESC_CODES_WARNING;
    }
    else if(level == SQTL_LOG_DEBUG) {
      out << CONSOLE_COLOR_ANSI_ESC_CODES_DEBUG;
    }
    else if(level == SQTL_LOG_FUNCTION) {
      out << CONSOLE_COLOR_ANSI_ESC_CODES_FUNCTION;
    }
  }
  if(functionName.isEmpty()) {
    out << QString(_logFormatInt_console).replace("<TS>", ts).replace("<TID>", tid).replace("<TID32>", tid.right(4*2)).replace("<LL>", QString(LOG_LEVEL_CHAR[level])).replace("<TEXT>", text.isEmpty() ? textIsEmpty : text.trimmed());
  }
  else {
    out << QString(_logFormat_console).replace("<TS>", ts).replace("<TID>", tid).replace("<TID32>", tid.right(4*2)).replace("<LL>", QString(LOG_LEVEL_CHAR[level])).replace("<FUNC>", functionName).replace("<FILE>", fileName).replace("<LINE>", QString("%1").arg(lineNumber)).replace("<TEXT>", text.isEmpty() ? textIsEmpty : text.trimmed());
  }
  if(SQTL_LOG_ENABLE_CONSOLE_COLOR) {
    if(level != SQTL_LOG_INFO) {
      out << CONSOLE_COLOR_ANSI_ESC_CODES_RESET;
    }
  }
  out << '\n';
}

void SimpleQtLogger::slotLog_qDebug(const QString& ts, const QString& tid, const QString& text, SQTL_LOG_Level level, const QString& functionName, const QString& fileName, unsigned int lineNumber)
{
  // qDebug("SimpleQtLogger::slotLog_qDebug");

  if(!SQTL_LOG_ENABLE_SINK_QDEBUG) {
    return;
  }

  QString textIsEmpty("?");
  if(level == SQTL_LOG_FUNCTION) {
    textIsEmpty = "-";
  }

  if(functionName.isEmpty()) {
    qDebug("%s", QString(_logFormatInt_qDebug).replace("<TS>", ts).replace("<TID>", tid).replace("<TID32>", tid.right(4*2)).replace("<LL>", QString(LOG_LEVEL_CHAR[level])).replace("<TEXT>", text.isEmpty() ? textIsEmpty : text.trimmed()).toStdString().c_str());
  }
  else {
    qDebug("%s", QString(_logFormat_qDebug).replace("<TS>", ts).replace("<TID>", tid).replace("<TID32>", tid.right(4*2)).replace("<LL>", QString(LOG_LEVEL_CHAR[level])).replace("<FUNC>", functionName).replace("<FILE>", fileName).replace("<LINE>", QString("%1").arg(lineNumber)).replace("<TEXT>", text.isEmpty() ? textIsEmpty : text.trimmed()).toStdString().c_str());
  }
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
  if(ENABLED_SQTL_LOG_FUNCTION && SQTL_LOG_ENABLE.FUNCTION) SimpleQtLogger::getInstance()->logFuncBegin(_text, _functionName, _fileName, _lineNumber);
}

SimpleQtLoggerFunc::~SimpleQtLoggerFunc()
{
  // qDebug("SimpleQtLoggerFunc::~SimpleQtLoggerFunc");
  if(ENABLED_SQTL_LOG_FUNCTION && SQTL_LOG_ENABLE.FUNCTION) SimpleQtLogger::getInstance()->logFuncEnd(_text, _functionName, _fileName, _lineNumber);
}

#endif

} // namespace simpleqtlogger
