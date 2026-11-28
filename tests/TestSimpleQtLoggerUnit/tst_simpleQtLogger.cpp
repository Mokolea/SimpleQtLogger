/*
  Unit tests for Simple Logger for Qt (Qt Test, needs Qt >= 5.3)

  https://github.com/Mokolea/SimpleQtLogger

  Messages are observed through the signal sink (connected with Qt::DirectConnection)
  and through log-files in a temporary directory.

  GNU Lesser General Public License v2.1
  Copyright (C) 2023 Mario Ban
*/

#include <QtTest>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QRegularExpression>
#include <QTemporaryDir>
#include <QThread>

#include "simpleQtLogger.h"

#include <cstdio>
#ifdef Q_OS_UNIX
#include <unistd.h>
#endif

using namespace simpleqtlogger;

// -------------------------------------------------------------------------------------------------

class LogReceiver : public QObject
{
    Q_OBJECT

  public:
    QList<int> levels;
    QStringList messages;

  public slots:
    void slotLogMessage(simpleqtlogger::LogLevel logLevel, const QString& logMessage)
    {
      levels.append(logLevel);
      messages.append(logMessage);
    }
};

class LogThread : public QThread
{
    Q_OBJECT

  public:
    QString tid;

  protected:
    void run()
    {
      tid = SimpleQtLogger::threadId();
      L_INFO("from worker");
    }
};

// Collects the messages of the qDebug sink
static QStringList qDebugMessages;
static QtMessageHandler previousMessageHandler = 0; // TODO use C++11 nullptr

static void collectingMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
  if (type == QtDebugMsg) {
    qDebugMessages.append(msg);
    return;
  }
  previousMessageHandler(type, context, msg);
}

// -------------------------------------------------------------------------------------------------

class TestSimpleQtLogger : public QObject
{
    Q_OBJECT

  private slots:
    void init();
    void cleanup();

    // EnableLogLevels
    void enableLogLevels_defaults();
    void enableLogLevels_enabled();

    // static helpers
    void timeStamp_format();
    void threadId_format();
    void toHexdump_data();
    void toHexdump();

    // instance
    void instance_createAndDelete();
    void instance_createTwiceReplaces();
    void instance_macrosWithoutInstanceAreNoOp();

    // log-format TAGs
    void format_tags();
    void format_tidAndTs();
    void format_emptyTextAndTrimmed();
    void format_levelChars();
    void format_consoleSink();
    void format_consoleSinkColor();
    void format_qDebugSink();

    // gating
    void gating_globalLogLevels();
    void gating_sinkDisabled();
    void gating_perSinkLogLevels();
    void filter_regex();
    void filter_invalidRegex();

    // macros
    void macros_streaming();
    void macros_noShadowing();

    // function-log
    void func_disabledByDefault();
    void func_stackDepth();
    void func_stackDepthPerThread();
    void func_balancedWhenDisabledInScope();
    void func_withoutStackTrace();

    // threads
    void thread_queuedToSinks();
    void thread_queuedSignalReceiver();

    // file sink
    void file_nameMustEndWithLog();
    void file_writesLinesImmediately();
    void file_logLevelsPerRole();
    void file_rolling();
    void file_rollingMaxNumber();
    void file_rollingWithLogInDirectoryName();
    void file_noRollingBelowRotationSize();
    void file_retryOpenAfterFailure();

  private:
    SinkFileLog* fileSink(int index) const;
    void checkFileActivity(int index = 0) const;
    static QString readFile(const QString& fileName);
    QString captureConsole(void (*logFunc)(SimpleQtLogger*));

    SimpleQtLogger* _logger;
    LogReceiver* _receiver;
    QTemporaryDir* _tmpDir;
};

// -------------------------------------------------------------------------------------------------

void TestSimpleQtLogger::init()
{
  // reset all run-time globals to their defaults, except: signal sink on, file-state output off
  ENABLE_LOG_SINK_FILE = true;
  ENABLE_LOG_SINK_CONSOLE = false;
  ENABLE_LOG_SINK_QDEBUG = false;
  ENABLE_LOG_SINK_SIGNAL = true;
  ENABLE_LOG_SINK_SYSLOG = false;
  ENABLE_LOG_LEVELS = EnableLogLevels();
  ENABLE_FUNCTION_STACK_TRACE = true;
  ENABLE_CONSOLE_COLOR = true;
  ENABLE_CONSOLE_TRIMMED = true;
  ENABLE_CONSOLE_LOG_FILE_STATE = false;

  _logger = SimpleQtLogger::createInstance(qApp);
  _logger->setLogFormat_signal("<LL>|<TEXT>", "<LL>|<TEXT>");
  EnableLogLevels all;
  all.logLevel_DEBUG = true;
  all.logLevel_FUNCTION = true;
  _logger->setLogLevels_signal(all);

  _receiver = new LogReceiver;
  QVERIFY(_logger->connectSinkSignalLog(_receiver, SLOT(slotLogMessage(simpleqtlogger::LogLevel, const QString&)), Qt::DirectConnection));

  _tmpDir = new QTemporaryDir;
  QVERIFY(_tmpDir->isValid());
}

void TestSimpleQtLogger::cleanup()
{
  delete SimpleQtLogger::getInstance(); // closes the log-files
  _logger = 0; // TODO use C++11 nullptr
  delete _receiver;
  _receiver = 0;
  delete _tmpDir;
  _tmpDir = 0;
}

SinkFileLog* TestSimpleQtLogger::fileSink(int index) const
{
  // file sinks are children of the logger, in order of creation ("main" first)
  QList<SinkFileLog*> sinks = _logger->findChildren<SinkFileLog*>();
  if (index >= sinks.size()) {
    return 0;
  }
  return sinks[index];
}

void TestSimpleQtLogger::checkFileActivity(int index) const
{
  // run the activity check (and rolling) now, instead of waiting CHECK_LOG_FILE_ACTIVITY_INTERVAL
  SinkFileLog* sink = fileSink(index);
  QVERIFY(sink);
  QVERIFY(QMetaObject::invokeMethod(sink, "slotCheckLogFileActivity", Qt::DirectConnection));
}

/*static*/ QString TestSimpleQtLogger::readFile(const QString& fileName)
{
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return QString();
  }
  return QString::fromUtf8(file.readAll());
}

// -------------------------------------------------------------------------------------------------

void TestSimpleQtLogger::enableLogLevels_defaults()
{
  EnableLogLevels levels;
  QVERIFY(levels.logLevel_FATAL);
  QVERIFY(levels.logLevel_ERROR);
  QVERIFY(levels.logLevel_WARNING);
  QVERIFY(levels.logLevel_NOTE);
  QVERIFY(levels.logLevel_INFO);
  QVERIFY(!levels.logLevel_DEBUG);
  QVERIFY(!levels.logLevel_FUNCTION);
  QVERIFY(levels.logLevel_INTERNAL);
}

void TestSimpleQtLogger::enableLogLevels_enabled()
{
  EnableLogLevels levels;
  levels.logLevel_FATAL = false;
  levels.logLevel_ERROR = true;
  levels.logLevel_WARNING = false;
  levels.logLevel_NOTE = true;
  levels.logLevel_INFO = false;
  levels.logLevel_DEBUG = true;
  levels.logLevel_FUNCTION = false;
  levels.logLevel_INTERNAL = true;
  QVERIFY(!levels.enabled(LogLevel_FATAL));
  QVERIFY(levels.enabled(LogLevel_ERROR));
  QVERIFY(!levels.enabled(LogLevel_WARNING));
  QVERIFY(levels.enabled(LogLevel_NOTE));
  QVERIFY(!levels.enabled(LogLevel_INFO));
  QVERIFY(levels.enabled(LogLevel_DEBUG));
  QVERIFY(!levels.enabled(LogLevel_FUNCTION));
  QVERIFY(levels.enabled(LogLevel_INTERNAL));
  QVERIFY(!levels.enabled(static_cast<LogLevel>(42)));
}

// -------------------------------------------------------------------------------------------------

void TestSimpleQtLogger::timeStamp_format()
{
  QString ts = SimpleQtLogger::timeStamp();
  QVERIFY2(QRegularExpression("^\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}\\.\\d{3}$").match(ts).hasMatch(), qPrintable(ts));
}

void TestSimpleQtLogger::threadId_format()
{
  QString tid = SimpleQtLogger::threadId();
  // as wide as a pointer: 16 digits on 64-bit, 8 on 32-bit (a sign-extended value would be too long there)
  QVERIFY2(QRegularExpression(QString("^[0-9a-f]{%1}$").arg(sizeof(void*) * 2)).match(tid).hasMatch(), qPrintable(tid));
  bool ok = false;
  QCOMPARE(tid.toULongLong(&ok, 16), static_cast<qulonglong>(reinterpret_cast<quintptr>(QThread::currentThreadId())));
  QVERIFY(ok);
  QCOMPARE(SimpleQtLogger::threadId(), tid); // stable within a thread
}

void TestSimpleQtLogger::toHexdump_data()
{
  QTest::addColumn<QByteArray>("data");
  QTest::addColumn<QString>("expected");

  QTest::newRow("empty") << QByteArray() << QString("Size: 0");

  // a short last line is padded, so the text column stays aligned
  QTest::newRow("3 bytes") << QByteArray("ABC")
                           << QString("Size: 3\n00000000  41 42 43 %1  ABC").arg(QString(3 * 13, ' '));

  QTest::newRow("16 bytes") << QByteArray("0123456789abcdef")
                            << QString("Size: 16\n00000000  30 31 32 33 34 35 36 37  38 39 61 62 63 64 65 66  01234567 89abcdef");

  QTest::newRow("17 bytes") << QByteArray("0123456789abcdefg")
                            << QString("Size: 17\n00000000  30 31 32 33 34 35 36 37  38 39 61 62 63 64 65 66  01234567 89abcdef"
                                       "\n00000010  67 %1  g").arg(QString(3 * 15, ' '));

  // more than 8 bytes on the last line: the gap after 8 bytes is already there
  QTest::newRow("10 bytes") << QByteArray("0123456789")
                            << QString("Size: 10\n00000000  30 31 32 33 34 35 36 37  38 39%1  01234567 89").arg(QString(3 * 6, ' '));

  // non-printable characters show as '.'
  QTest::newRow("non-printable") << QByteArray("\x00\x1f\x7f\xff" "A", 5)
                                 << QString("Size: 5\n00000000  00 1f 7f ff 41 %1  ....A").arg(QString(3 * 11, ' '));
}

void TestSimpleQtLogger::toHexdump()
{
  QFETCH(QByteArray, data);
  QFETCH(QString, expected);
  QCOMPARE(SimpleQtLogger::toHexdump(data), expected);
}

// -------------------------------------------------------------------------------------------------

void TestSimpleQtLogger::instance_createAndDelete()
{
  QCOMPARE(SimpleQtLogger::getInstance(), _logger);
  QCOMPARE(_logger->parent(), static_cast<QObject*>(qApp));

  delete _logger;
  QVERIFY(SimpleQtLogger::getInstance() == 0); // no dangling pointer
}

void TestSimpleQtLogger::instance_createTwiceReplaces()
{
  QPointer<SimpleQtLogger> first(_logger);
  _logger = SimpleQtLogger::createInstance(qApp);
  QVERIFY(first.isNull()); // the old instance is deleted
  QCOMPARE(SimpleQtLogger::getInstance(), _logger);
}

void TestSimpleQtLogger::instance_macrosWithoutInstanceAreNoOp()
{
  delete _logger;
  QVERIFY(SimpleQtLogger::getInstance() == 0);

  ENABLE_LOG_LEVELS.logLevel_FUNCTION = true;
  {
    L_FUNC("");
  }
  {
    LS_FUNC("x=" << 1);
    L_INFO("lost");
    LS_ERROR("lost " << 2);
  }
  QVERIFY(_receiver->messages.isEmpty());
}

// -------------------------------------------------------------------------------------------------

void TestSimpleQtLogger::format_tags()
{
  _logger->setLogFormat_signal("<LL>|<TEXT>|<FUNC>|<FILE>|<LINE>", "<LL>|<TEXT>");
  _logger->log("hello", LogLevel_WARNING, "myFunc", "my/file.cpp", 42);
  _logger->log("internal", LogLevel_INTERNAL, "ignoredFunc", "ignored.cpp", 7); // internal format, no FUNC/FILE/LINE

  QCOMPARE(_receiver->messages, QStringList() << "W|hello|myFunc|my/file.cpp|42" << "-|internal");
  QCOMPARE(_receiver->levels, QList<int>() << LogLevel_WARNING << LogLevel_INTERNAL);
}

void TestSimpleQtLogger::format_tidAndTs()
{
  _logger->setLogFormat_signal("<TID>|<TID32>|<TS>", "");
  L_INFO("x");

  QCOMPARE(_receiver->messages.size(), 1);
  QStringList parts = _receiver->messages[0].split('|');
  QCOMPARE(parts.size(), 3);
  QCOMPARE(parts[0], SimpleQtLogger::threadId());
  QCOMPARE(parts[1], QString("<TID32>")); // removed TAG, not expanded
  QVERIFY(QRegularExpression("^\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}\\.\\d{3}$").match(parts[2]).hasMatch());
}

void TestSimpleQtLogger::format_emptyTextAndTrimmed()
{
  L_INFO("");
  L_INFO("  padded \t");
  _logger->log("", LogLevel_FUNCTION, "f", "f.cpp", 1);

  QCOMPARE(_receiver->messages, QStringList() << "I|?" << "I|padded" << "F|-");
}

void TestSimpleQtLogger::format_levelChars()
{
  L_FATAL("a");
  L_ERROR("b");
  L_WARN("c");
  L_NOTE("d");
  L_INFO("e");
  ENABLE_LOG_LEVELS.logLevel_DEBUG = true;
  L_DEBUG("f");

  QCOMPARE(_receiver->messages, QStringList() << "!|a" << "E|b" << "W|c" << "N|d" << "I|e" << "D|f");
  QCOMPARE(_receiver->levels, QList<int>() << LogLevel_FATAL << LogLevel_ERROR << LogLevel_WARNING << LogLevel_NOTE << LogLevel_INFO << LogLevel_DEBUG);
}

// Redirects stdout to a file while logFunc runs, returns what the console sink wrote
QString TestSimpleQtLogger::captureConsole(void (*logFunc)(SimpleQtLogger*))
{
#ifdef Q_OS_UNIX
  const QString fileName = _tmpDir->path() + "/stdout.txt";
  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly)) {
    return "open failed";
  }
  fflush(stdout);
  int savedStdout = dup(STDOUT_FILENO);
  dup2(file.handle(), STDOUT_FILENO);
  logFunc(_logger);
  fflush(stdout);
  dup2(savedStdout, STDOUT_FILENO);
  close(savedStdout);
  file.close();
  return readFile(fileName);
#else
  Q_UNUSED(logFunc);
  return QString();
#endif
}

static void logConsoleMessages(SimpleQtLogger* logger)
{
  logger->log("  warn  ", LogLevel_WARNING, "fn", "f.cpp", 1);
  logger->log("", LogLevel_INFO, "fn", "f.cpp", 2);
  ENABLE_CONSOLE_TRIMMED = false;
  logger->log("  untrimmed  ", LogLevel_INFO, "fn", "f.cpp", 3);
  logger->log("  func  ", LogLevel_FUNCTION, "fn", "f.cpp", 4); // always trimmed, suffix " (<FUNC>)"
  logger->log("", LogLevel_FUNCTION, "fn", "f.cpp", 5);
  logger->log("  internal  ", LogLevel_INTERNAL, "fn", "f.cpp", 6); // always trimmed, no FUNC/FILE/LINE
  ENABLE_CONSOLE_TRIMMED = true;
}

void TestSimpleQtLogger::format_consoleSink()
{
#ifndef Q_OS_UNIX
  QSKIP("stdout capture needs POSIX dup2");
#endif
  ENABLE_LOG_SINK_CONSOLE = true;
  ENABLE_CONSOLE_COLOR = false;
  EnableLogLevels all;
  all.logLevel_DEBUG = true;
  all.logLevel_FUNCTION = true;
  _logger->setLogLevels_console(all);
  _logger->setLogFormat_console("<LL>|<TEXT>|<FUNC>@<FILE>:<LINE>", "<LL>|<TEXT>|<FUNC>");

  QCOMPARE(captureConsole(logConsoleMessages), QString(
             "WARNING: W|warn|fn@f.cpp:1\n"
             "I|?|fn@f.cpp:2\n"
             "I|  untrimmed  |fn@f.cpp:3\n"
             "F|func|fn@f.cpp:4 (fn)\n"
             "F|-|fn@f.cpp:5 (fn)\n"
             "-|internal|<FUNC>\n"));
}

static void logConsoleColorMessages(SimpleQtLogger* logger)
{
  logger->log("e", LogLevel_ERROR, "fn", "f.cpp", 1);
  logger->log("i", LogLevel_INFO, "fn", "f.cpp", 2);
  logger->log("f", LogLevel_FUNCTION, "fn", "f.cpp", 3);
}

void TestSimpleQtLogger::format_consoleSinkColor()
{
#ifndef Q_OS_UNIX
  QSKIP("stdout capture needs POSIX dup2");
#endif
  ENABLE_LOG_SINK_CONSOLE = true;
  EnableLogLevels all;
  all.logLevel_FUNCTION = true;
  _logger->setLogLevels_console(all);

  // default console format "<TEXT>", function-log gets the suffix " (<FUNC>)"
  QCOMPARE(captureConsole(logConsoleColorMessages), QString(
             "\033[0;47;31;1mERROR\033[0;31m: e\033[0m\n"
             "i\n"
             "\033[0;32mf (fn)\033[0m\n"));
}

void TestSimpleQtLogger::format_qDebugSink()
{
  ENABLE_LOG_SINK_QDEBUG = true;
  EnableLogLevels all;
  all.logLevel_FUNCTION = true;
  _logger->setLogLevels_qDebug(all);
  _logger->setLogFormat_qDebug("<LL>|<TEXT>|<FUNC>@<FILE>:<LINE>", "<LL>|<TEXT>|<FUNC>");

  qDebugMessages.clear();
  previousMessageHandler = qInstallMessageHandler(collectingMessageHandler);
  _logger->log("  note  ", LogLevel_NOTE, "fn", "f.cpp", 1);
  _logger->log("", LogLevel_FUNCTION, "fn", "f.cpp", 2);
  _logger->log("  internal  ", LogLevel_INTERNAL, "fn", "f.cpp", 3);
  qInstallMessageHandler(previousMessageHandler);

  QCOMPARE(qDebugMessages, QStringList()
           << "N|note|fn@f.cpp:1"
           << "F|-|fn@f.cpp:2"
           << "-|internal|<FUNC>");
}

// -------------------------------------------------------------------------------------------------

void TestSimpleQtLogger::gating_globalLogLevels()
{
  L_DEBUG("debug off by default");
  ENABLE_LOG_LEVELS.logLevel_INFO = false;
  L_INFO("info off");
  LS_INFO("info " << "off");
  ENABLE_LOG_LEVELS.logLevel_DEBUG = true;
  L_DEBUG("debug on");

  QCOMPARE(_receiver->messages, QStringList() << "D|debug on");
}

void TestSimpleQtLogger::gating_sinkDisabled()
{
  ENABLE_LOG_SINK_SIGNAL = false;
  L_ERROR("not forwarded");
  ENABLE_LOG_SINK_SIGNAL = true;
  L_ERROR("forwarded");

  QCOMPARE(_receiver->messages, QStringList() << "E|forwarded");
}

void TestSimpleQtLogger::gating_perSinkLogLevels()
{
  EnableLogLevels levels;
  levels.logLevel_WARNING = false;
  levels.logLevel_INTERNAL = false;
  _logger->setLogLevels_signal(levels);

  EnableLogLevels got = _logger->getLogLevels_signal();
  QVERIFY(!got.logLevel_WARNING);
  QVERIFY(!got.logLevel_INTERNAL);
  QVERIFY(got.logLevel_ERROR);

  L_WARN("dropped");
  L_ERROR("kept");
  _logger->log("dropped internal", LogLevel_INTERNAL, "", "", 0);

  QCOMPARE(_receiver->messages, QStringList() << "E|kept");
}

void TestSimpleQtLogger::filter_regex()
{
  QVERIFY(_logger->addLogFilter_signal(QRegularExpression("^id=")));
  QVERIFY(_logger->addLogFilter_signal(QRegularExpression("needle")));

  L_INFO("id=1");
  L_INFO("other");
  L_INFO("a needle here");
  _logger->log("internal is never filtered", LogLevel_INTERNAL, "", "", 0);

  QCOMPARE(_receiver->messages, QStringList() << "I|id=1" << "I|a needle here" << "-|internal is never filtered");
}

void TestSimpleQtLogger::filter_invalidRegex()
{
  QRegularExpression invalid("(unclosed");
  QVERIFY(!invalid.isValid());
  QVERIFY(!_logger->addLogFilter_signal(invalid));
  QVERIFY(!_logger->addLogFilter_file(invalid));
  QVERIFY(!_logger->addLogFilter_file("no-such-role", QRegularExpression("x")));

  L_INFO("no filter installed");
  QCOMPARE(_receiver->messages, QStringList() << "I|no filter installed");
}

// -------------------------------------------------------------------------------------------------

void TestSimpleQtLogger::macros_streaming()
{
  int n = 7;
  LS_INFO("n=" << n << " pi=" << 3.5 << ' ' << QString("q"));
  QCOMPARE(_receiver->messages, QStringList() << "I|n=7 pi=3.5 q");
}

void TestSimpleQtLogger::macros_noShadowing()
{
  // user variables with names a macro might use internally
  QString s("user-s");
  QString ts("user-ts");
  QString text("user-text");
  SimpleQtLogger* logger = 0; // TODO use C++11 nullptr
  Q_UNUSED(logger);
  LS_INFO(s << ',' << ts << ',' << text);
  L_INFO(s);

  QCOMPARE(_receiver->messages, QStringList() << "I|user-s,user-ts,user-text" << "I|user-s");
}

// -------------------------------------------------------------------------------------------------

void TestSimpleQtLogger::func_disabledByDefault()
{
  {
    L_FUNC("arg");
  }
  QVERIFY(_receiver->messages.isEmpty());
}

static void tracedInner()
{
  LS_FUNC("inner=" << 2);
  L_INFO("in inner");
}

static void tracedOuter()
{
  L_FUNC("outer");
  tracedInner();
}

void TestSimpleQtLogger::func_stackDepth()
{
  ENABLE_LOG_LEVELS.logLevel_FUNCTION = true;
  _logger->setLogFormat_signal("<LL>|<TEXT>|<FUNC>", "");
  tracedOuter();
  {
    L_FUNC("");
  }

  QCOMPARE(_receiver->messages, QStringList()
           << "F|\\ outer|tracedOuter"
           << "F|.\\ inner=2|tracedInner"
           << "I|in inner|tracedInner"
           << "F|./ inner=2|tracedInner"
           << "F|/ outer|tracedOuter"
           << "F|\\|func_stackDepth"
           << "F|/|func_stackDepth");
}

void TestSimpleQtLogger::func_stackDepthPerThread()
{
  ENABLE_LOG_LEVELS.logLevel_FUNCTION = true;
  L_FUNC("main");

  class FuncThread : public QThread
  {
    protected:
      void run()
      {
        L_FUNC("worker"); // own thread: depth starts at the top again
      }
  } thread;
  thread.start();
  QVERIFY(thread.wait(5000));
  QCoreApplication::processEvents(); // deliver the queued messages

  QCOMPARE(_receiver->messages, QStringList() << "F|\\ main" << "F|\\ worker" << "F|/ worker");
}

void TestSimpleQtLogger::func_balancedWhenDisabledInScope()
{
  ENABLE_LOG_LEVELS.logLevel_FUNCTION = true;
  {
    L_FUNC("a");
    ENABLE_LOG_LEVELS.logLevel_FUNCTION = false; // disabled while in the traced scope
  }
  {
    L_FUNC("b"); // not traced at all
    ENABLE_LOG_LEVELS.logLevel_FUNCTION = true; // enabled while in the untraced scope
  }
  {
    L_FUNC("c"); // depth must be back at the top
  }

  QCOMPARE(_receiver->messages, QStringList() << "F|\\ a" << "F|\\ c" << "F|/ c");
}

void TestSimpleQtLogger::func_withoutStackTrace()
{
  ENABLE_LOG_LEVELS.logLevel_FUNCTION = true;
  ENABLE_FUNCTION_STACK_TRACE = false;
  {
    L_FUNC("entry only");
    {
      L_FUNC("nested");
    }
  }
  ENABLE_FUNCTION_STACK_TRACE = true;
  {
    L_FUNC("traced");
  }

  QCOMPARE(_receiver->messages, QStringList() << "F|entry only" << "F|nested" << "F|\\ traced" << "F|/ traced");
}

// -------------------------------------------------------------------------------------------------

void TestSimpleQtLogger::thread_queuedToSinks()
{
  _logger->setLogFormat_signal("<TID>|<TEXT>", "");
  LogThread thread;
  thread.start();
  QVERIFY(thread.wait(5000));

  // the sinks live in the main thread, so the message is queued until the event loop runs
  QVERIFY(_receiver->messages.isEmpty());
  QTRY_COMPARE(_receiver->messages.size(), 1);
  QCOMPARE(_receiver->messages[0], thread.tid + "|from worker");
  QVERIFY(thread.tid != SimpleQtLogger::threadId());
}

void TestSimpleQtLogger::thread_queuedSignalReceiver()
{
  // a queued connection needs the meta-type "simpleqtlogger::LogLevel"
  LogReceiver queued;
  QVERIFY(_logger->connectSinkSignalLog(&queued, SLOT(slotLogMessage(simpleqtlogger::LogLevel, const QString&)), Qt::QueuedConnection));
  L_WARN("queued");
  QVERIFY(queued.messages.isEmpty());
  QTRY_COMPARE(queued.messages, QStringList() << "W|queued");
  QCOMPARE(queued.levels, QList<int>() << LogLevel_WARNING);
}

// -------------------------------------------------------------------------------------------------

void TestSimpleQtLogger::file_nameMustEndWithLog()
{
  QTest::ignoreMessage(QtWarningMsg, QRegularExpression("^Name of log-file not ending with '.log'"));
  QVERIFY(!_logger->setLogFileName(_tmpDir->path() + "/app.txt", 1000, 1));
  QVERIFY(!QFile::exists(_tmpDir->path() + "/app.txt"));

  QVERIFY(!_logger->setLogFileName("no-such-role", _tmpDir->path() + "/app.log", 1000, 1));
  QVERIFY(!QFile::exists(_tmpDir->path() + "/app.log"));
}

void TestSimpleQtLogger::file_writesLinesImmediately()
{
  const QString fileName = _tmpDir->path() + "/app.log";
  _logger->setLogFormat_file("<LL> <TEXT> (<FUNC>:<LINE>)", "<LL> <TEXT>");
  QVERIFY(_logger->setLogFileName(fileName, 10*1024, 3));

  const int line = __LINE__ + 1;
  L_INFO("first");
  _logger->log(QString::fromUtf8("UTF-8: \xc3\xa4\xc3\xb6\xc3\xbc"), LogLevel_ERROR, "fn", "f.cpp", 12);

  // no flush needed: each message is handed to the file right away
  QCOMPARE(readFile(fileName), QString::fromUtf8("- Start file-log 'main'\n"
                                                 "I first (file_writesLinesImmediately:%1)\n"
                                                 "E UTF-8: \xc3\xa4\xc3\xb6\xc3\xbc (fn:12)\n").arg(line));

  ENABLE_LOG_SINK_FILE = false;
  L_INFO("not written");
  QVERIFY(!readFile(fileName).contains("not written"));
}

void TestSimpleQtLogger::file_logLevelsPerRole()
{
  const QString mainName = _tmpDir->path() + "/main.log";
  const QString warnName = _tmpDir->path() + "/warn.log";

  _logger->addSinkFileLog("warn");
  _logger->addSinkFileLog("warn"); // adding the same role again is ignored
  QCOMPARE(_logger->findChildren<SinkFileLog*>().size(), 2);

  EnableLogLevels warnLevels;
  warnLevels.logLevel_NOTE = false;
  warnLevels.logLevel_INFO = false;
  _logger->setLogLevels_file("warn", warnLevels);
  QVERIFY(!_logger->getLogLevels_file("warn").logLevel_INFO);
  QVERIFY(_logger->getLogLevels_file().logLevel_INFO);

  _logger->setLogFormat_file("<LL> <TEXT>", "<LL> <TEXT>");
  _logger->setLogFormat_file("warn", "<LL> <TEXT>", "<LL> <TEXT>");
  QVERIFY(_logger->setLogFileName(mainName, 10*1024, 3));
  QVERIFY(_logger->setLogFileName("warn", warnName, 10*1024, 3));

  L_INFO("info");
  L_WARN("warn");

  QCOMPARE(readFile(mainName), QString("- Start file-log 'main'\nI info\nW warn\n"));
  QCOMPARE(readFile(warnName), QString("- Start file-log 'warn'\nW warn\n"));
}

void TestSimpleQtLogger::file_rolling()
{
  const QString fileName = _tmpDir->path() + "/app.log";
  const QString rolled1 = _tmpDir->path() + "/app_01.log";
  _logger->setLogFormat_file("<TEXT>", "<TEXT>");
  QVERIFY(_logger->setLogFileName(fileName, 100, 3)); // 100 is the minimum rotation size

  for (int i = 0; i < 10; ++i) {
    LS_INFO("message " << i << " with some padding text");
  }
  QVERIFY(QFileInfo(fileName).size() > 100);
  QVERIFY(!QFile::exists(rolled1));

  checkFileActivity();

  QVERIFY(QFile::exists(rolled1));
  QString old = readFile(rolled1);
  QVERIFY(old.startsWith("Start file-log 'main'\nmessage 0"));
  QVERIFY(old.contains("message 9"));
  QVERIFY(old.contains("--> rolling"));

  QString current = readFile(fileName);
  QVERIFY2(current.startsWith("Log-file 'main' rolling done"), qPrintable(current));
  QVERIFY(!current.contains("message"));

  L_INFO("after rolling");
  QVERIFY(readFile(fileName).contains("after rolling"));
}

void TestSimpleQtLogger::file_rollingMaxNumber()
{
  const QString fileName = _tmpDir->path() + "/app.log";
  _logger->setLogFormat_file("<TEXT>", "<TEXT>");
  QVERIFY(_logger->setLogFileName(fileName, 100, 2));

  for (int round = 1; round <= 3; ++round) {
    for (int i = 0; i < 5; ++i) {
      LS_INFO("round " << round << " message " << i << " padding padding");
    }
    checkFileActivity();
  }

  // oldest file is dropped: _02 holds round 2, _01 holds round 3
  QVERIFY(QFile::exists(_tmpDir->path() + "/app_01.log"));
  QVERIFY(QFile::exists(_tmpDir->path() + "/app_02.log"));
  QVERIFY(!QFile::exists(_tmpDir->path() + "/app_03.log"));
  QVERIFY(readFile(_tmpDir->path() + "/app_02.log").contains("round 2 message 0"));
  QVERIFY(readFile(_tmpDir->path() + "/app_01.log").contains("round 3 message 0"));
  QVERIFY(!readFile(fileName).contains("round"));
}

void TestSimpleQtLogger::file_rollingWithLogInDirectoryName()
{
  QDir tmp(_tmpDir->path());
  QVERIFY(tmp.mkdir("logs.log"));
  const QString fileName = tmp.filePath("logs.log/app.log");
  QVERIFY(_logger->setLogFileName(fileName, 100, 3));

  for (int i = 0; i < 10; ++i) {
    L_INFO("message with some padding text");
  }
  checkFileActivity();

  // the rolling number goes in front of the trailing ".log" only
  QVERIFY(QFile::exists(tmp.filePath("logs.log/app_01.log")));
  QVERIFY(!QFile::exists(tmp.filePath("logs_01.log/app.log")));
  QVERIFY(QFile::exists(fileName));
}

void TestSimpleQtLogger::file_noRollingBelowRotationSize()
{
  const QString fileName = _tmpDir->path() + "/app.log";
  QVERIFY(_logger->setLogFileName(fileName, 10*1024, 3));
  L_INFO("small");
  checkFileActivity();
  checkFileActivity(); // no activity since the last check
  QVERIFY(!QFile::exists(_tmpDir->path() + "/app_01.log"));
  QVERIFY(readFile(fileName).contains("small"));
}

void TestSimpleQtLogger::file_retryOpenAfterFailure()
{
  const QString dirName = _tmpDir->path() + "/later";
  const QString fileName = dirName + "/app.log";
  _logger->setLogFormat_file("<TEXT>", "<TEXT>");

  QTest::ignoreMessage(QtWarningMsg, QRegularExpression("^Open log-file failed! Retrying every"));
  QVERIFY(!_logger->setLogFileName(fileName, 10*1024, 3));

  L_INFO("lost while closed");
  checkFileActivity(); // still failing; warned only once (an extra warning fails the test)

  QVERIFY(QDir().mkpath(dirName));
  checkFileActivity(); // retry succeeds
  L_INFO("after re-open");

  QString content = readFile(fileName);
  QVERIFY2(content.startsWith("Start file-log 'main'\nLog-file 'main' re-opened after open failure"), qPrintable(content));
  QVERIFY(!content.contains("lost while closed"));
  QVERIFY(content.endsWith("after re-open\n"));
}

// -------------------------------------------------------------------------------------------------

QTEST_GUILESS_MAIN(TestSimpleQtLogger)

#include "tst_simpleQtLogger.moc"
