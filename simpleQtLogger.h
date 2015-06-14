/*
  Simple Logger for Qt

  Mario Ban, 05.2015

  Facts:
   - supported sinks:
      - rolling file appender
      - qDebug
   - no configuration file
   - restriction: log-file name has to end with: ".log"

  Usage:
   - moc has to be applied
   - create logger instance in main (set qApp as parent object) and initialize (example):
      SimpleQtLogger::createInstance(qApp)->setLogFileName("testSimpleQtLogger.log", 10*1024*1024, 20);
   - initialize log-levels (example):
      SQTL_LOG_ENABLE_INFO = true;
      SQTL_LOG_ENABLE_DEBUG = false;
      SQTL_LOG_ENABLE_FUNCTION = true;
   - set main task (widget) as parent object for the logger instance (example):
      SimpleQtLogger::getInstance()->setParent(task);

  TODO:
   - enable pedantic-errors, check for no compiler warnings, use e.g.: -Wall -Wextra -Werror -pedantic-errors -Wwrite-strings
   - add different set of log macros to compose messages using stream operator
   - maybe allow message-buffering, processing on idle-time
   - maybe flush periodically on idle-time
   - maybe do file rolling (check file size periodically) on idle-time
   - currently not thread-safe, stack-depth not tracked per thread (thread-id-callback?)

  Tested using:
   - Qt 5.4.2 (Community Open Source), Clang 6.0 (Apple) 64 bit
   - Qt 4.8.6 Debian 8, gcc version 4.9.2 (Debian 4.9.2-10), 64 bit

  GNU General Public License v2.0
  Copyright (C) 2015 Mario Ban
*/

#ifndef _SIMPLE_QT_LOGGER_H
#define _SIMPLE_QT_LOGGER_H

#include <QObject>
#include <QString>
#include <QFile>

/* Log-sinks */
#define ENABLED_SQTL_LOG_SINK_FILE     1   /* 1: enable, 0: disable; log to file (rolling) */
#define ENABLED_SQTL_LOG_SINK_QDEBUG   0   /* 1: enable, 0: disable; log using qDebug; messages are sent to the console, if it is a console application */

/* Log-level (hard; adjust at pre-processor, compile-time) */
#define ENABLED_SQTL_LOG_FATAL      1   /* 1: enable, 0: disable */
#define ENABLED_SQTL_LOG_ERROR      1   /* 1: enable, 0: disable */
#define ENABLED_SQTL_LOG_WARNING    1   /* 1: enable, 0: disable */
#define ENABLED_SQTL_LOG_INFO       1   /* 1: enable, 0: disable */
#define ENABLED_SQTL_LOG_DEBUG      0   /* 1: enable, 0: disable; just for step-by-step testing */
#define ENABLED_SQTL_LOG_FUNCTION   1   /* 1: enable, 0: disable; stack-trace */

#define STACK_DEPTH_CHAR                    '.'   /* use e.g. ' ' or '.' */
#define CHECK_LOG_FILE_ACTIVITY_INTERVAL   5000   /* [ms] */

/* Log-level */
typedef enum {
  SQTL_LOG_FATAL = 0, /* Fatal error, the program execution has to be aborted */
  SQTL_LOG_ERROR,     /* An error, that challenges the core operation */
  SQTL_LOG_WARNING,   /* A warning, signalizing a deformity, without challenging the core operation */
  SQTL_LOG_INFO,      /* Analysis information directed to supporters */
  SQTL_LOG_DEBUG,     /* Analysis debug information directed to developers */
  SQTL_LOG_FUNCTION   /* A trace level for function stack-tracing */
}
SQTL_LOG_Level;

static const char LOG_LEVEL_CHAR[6] = {'!', 'E', 'W', 'I', 'D', 'F'}; /* MUST correspond to enum SQTL_LOG_Level, unchecked array!!! */

/* Log-level (adjust at run-time) */
extern bool SQTL_LOG_ENABLE_FATAL;      /* Log-level: true: enable, false: disable, default: true */
extern bool SQTL_LOG_ENABLE_ERROR;      /* Log-level: true: enable, false: disable, default: true */
extern bool SQTL_LOG_ENABLE_WARNING;    /* Log-level: true: enable, false: disable, default: true */
extern bool SQTL_LOG_ENABLE_INFO;       /* Log-level: true: enable, false: disable, default: true */
extern bool SQTL_LOG_ENABLE_DEBUG;      /* Log-level: true: enable, false: disable, default: false; just for step-by-step testing */
extern bool SQTL_LOG_ENABLE_FUNCTION;   /* Log-level: true: enable, false: disable, default: false; stack-trace */

/* Use these macros to have function-, filename and linenumber set correct */
#define L_FATAL(text)   do { if(ENABLED_SQTL_LOG_FATAL && SQTL_LOG_ENABLE_FATAL) SimpleQtLogger::getInstance()->log(text, SQTL_LOG_FATAL, __FUNCTION__, __FILE__, __LINE__); } while(0)
#define L_ERROR(text)   do { if(ENABLED_SQTL_LOG_ERROR && SQTL_LOG_ENABLE_ERROR) SimpleQtLogger::getInstance()->log(text, SQTL_LOG_ERROR, __FUNCTION__, __FILE__, __LINE__); } while(0)
#define L_WARN(text)    do { if(ENABLED_SQTL_LOG_WARNING && SQTL_LOG_ENABLE_WARNING) SimpleQtLogger::getInstance()->log(text, SQTL_LOG_WARNING, __FUNCTION__, __FILE__, __LINE__); } while(0)
#define L_INFO(text)    do { if(ENABLED_SQTL_LOG_INFO && SQTL_LOG_ENABLE_INFO) SimpleQtLogger::getInstance()->log(text, SQTL_LOG_INFO, __FUNCTION__, __FILE__, __LINE__); } while(0)
#define L_DEBUG(text)   do { if(ENABLED_SQTL_LOG_DEBUG && SQTL_LOG_ENABLE_DEBUG) SimpleQtLogger::getInstance()->log(text, SQTL_LOG_DEBUG, __FUNCTION__, __FILE__, __LINE__); } while(0)
#if ENABLED_SQTL_LOG_FUNCTION > 0
#define L_FUNC(text)    SimpleQtLoggerFunc _simpleQtLoggerFunc_(text, __FUNCTION__, __FILE__, __LINE__)
#else
#define L_FUNC(text)    /* nop */
#endif

// -------------------------------------------------------------------------------------------------

class SimpleQtLogger : public QObject
{
  Q_OBJECT

public:
  static SimpleQtLogger* createInstance(QObject *parent);
  static SimpleQtLogger* getInstance(); // may return NULL pointer!

  ~SimpleQtLogger();

  void setLogFileName(const QString& logFileName, unsigned int logFileRotationSize, unsigned int logFileMaxNumber);
  void log(const QString& text, SQTL_LOG_Level level, const QString& functionName, const char* fileName, unsigned int lineNumber);
#if ENABLED_SQTL_LOG_FUNCTION > 0
  void logFuncBegin(const QString& text, const QString& functionName, const QString& fileName, unsigned int lineNumber);
  void logFuncEnd(const QString& text, const QString& functionName, const QString& fileName, unsigned int lineNumber);
#endif

signals:
  void signalLog(const QString& ts, const QString& text, SQTL_LOG_Level level, const QString& functionName, const QString& fileName, unsigned int lineNumber);

private slots:
  void slotLog_File(const QString& ts, const QString& text, SQTL_LOG_Level level, const QString& functionName, const QString& fileName, unsigned int lineNumber);
  void slotLog_qDebug(const QString& ts, const QString& text, SQTL_LOG_Level level, const QString& functionName, const QString& fileName, unsigned int lineNumber);
  void slotCheckLogFileActivity();

private:
  SimpleQtLogger(QObject *parent = 0);

  void checkLogFileOpen();
  void checkLogFileRolling();

  static SimpleQtLogger* instance;

  QString _logFileName;
  unsigned int _logFileRotationSize; // initiate log-file rolling
  unsigned int _logFileMaxNumber; // max number of rolling log-file history

  unsigned int _stackDepth; // current stack-depth for function-log

  QFile* _logFile;
  bool _logFileActivity; // track log-file write (append) activity
};

// -------------------------------------------------------------------------------------------------

#if ENABLED_SQTL_LOG_FUNCTION > 0

class SimpleQtLoggerFunc
{
public:
  SimpleQtLoggerFunc(const QString& text, const QString& functionName, const QString& fileName, unsigned int lineNumber);
  ~SimpleQtLoggerFunc();

private:
  const QString _text;
  const QString _functionName;
  const QString _fileName;
  unsigned int _lineNumber;
};

#endif

// -------------------------------------------------------------------------------------------------

#endif // _SIMPLE_QT_LOGGER_H
