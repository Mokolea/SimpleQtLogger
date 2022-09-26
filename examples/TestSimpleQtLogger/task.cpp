/*
  Test Simple Logger for Qt

  Mario Ban, 05.2015
  https://github.com/Mokolea/SimpleQtLogger

  GNU Lesser General Public License v2.1
  Copyright (C) 2015 Mario Ban
*/

#include "task.h"

#include <QTimer>
#include <QThread>
#include <QtDebug>

// -------------------------------------------------------------------------------------------------

Task::Task(QObject *parent)
  : QObject(parent)
{
  L_FUNC("");
  // qDebug("Task::Task");
}

Task::~Task()
{
  L_FUNC("");
  // qDebug("Task::~Task");
}

void Task::init()
{
  L_FUNC("");

  L_INFO("+++ test Logger");
  L_FATAL("L_FATAL");
  L_ERROR("L_ERROR");
  L_WARN("L_WARN");
  L_NOTE("L_NOTE");
  L_INFO("L_INFO");
  L_DEBUG("L_DEBUG");
  L_INFO("--- test Logger");

  L_INFO(QString()); // --> "?"
  L_INFO(" \n Trimmed \n\n"); // --> whitespace removed from start and end
  L_INFO("UTF-8 Unicode text: äöü àéè");

  QString formattedOutput1 = "JSON output 1:\n"
    "{\n"
    "  \"firstName\": \"Mario\",\n"
    "  \"age\": 44\n"
    "}"
  ;
  L_INFO(formattedOutput1);

  QString formattedOutput2 = "{<br>  \"firstName\": \"Mario\",<br>  \"age\": 44<br>}";
  L_INFO(formattedOutput2.prepend("JSON output 2:<br>").replace("<br>", "\n"));

  simpleqtlogger::EnableLogLevels enableLogLevels_console = simpleqtlogger::SimpleQtLogger::getInstance()->getLogLevels_console();
  enableLogLevels_console.logLevel_INFO = false;
  simpleqtlogger::SimpleQtLogger::getInstance()->setLogLevels_console(enableLogLevels_console);
  L_INFO("Disabled");
  enableLogLevels_console.logLevel_INFO = true;
  simpleqtlogger::SimpleQtLogger::getInstance()->setLogLevels_console(enableLogLevels_console);

  testLogLevels("1234567890\n1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890\n"
                "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890", 2);

  L_INFO("Test hexdump 1");
  QByteArray ba1;
  L_DEBUG(simpleqtlogger::SimpleQtLogger::toHexdump(ba1)); // size: 0
  ba1.append("1");
  L_DEBUG(simpleqtlogger::SimpleQtLogger::toHexdump(ba1)); // size: 1
  ba1.append("234567");
  L_DEBUG(simpleqtlogger::SimpleQtLogger::toHexdump(ba1)); // size: 7
  ba1.append("8");
  L_DEBUG(simpleqtlogger::SimpleQtLogger::toHexdump(ba1)); // size: 8
  ba1.append("9");
  L_DEBUG(simpleqtlogger::SimpleQtLogger::toHexdump(ba1)); // size: 9
  ba1.append("012345");
  L_DEBUG(simpleqtlogger::SimpleQtLogger::toHexdump(ba1)); // size: 15
  ba1.append("6");
  L_DEBUG(simpleqtlogger::SimpleQtLogger::toHexdump(ba1)); // size: 16
  ba1.append("7");
  L_DEBUG(simpleqtlogger::SimpleQtLogger::toHexdump(ba1)); // size: 17
  ba1.append("890123");
  L_DEBUG(simpleqtlogger::SimpleQtLogger::toHexdump(ba1)); // size: 23
  ba1.append("4");
  L_DEBUG(simpleqtlogger::SimpleQtLogger::toHexdump(ba1)); // size: 24
  ba1.append("5");
  L_DEBUG(simpleqtlogger::SimpleQtLogger::toHexdump(ba1)); // size: 25
  ba1.append("678901");
  L_DEBUG(simpleqtlogger::SimpleQtLogger::toHexdump(ba1)); // size: 31
  ba1.append("2");
  L_DEBUG(simpleqtlogger::SimpleQtLogger::toHexdump(ba1)); // size: 32
  ba1.append("3");
  L_DEBUG(simpleqtlogger::SimpleQtLogger::toHexdump(ba1)); // size: 33

  L_INFO("Test hexdump 2");
  QByteArray ba2("12345678");
  L_DEBUG(simpleqtlogger::SimpleQtLogger::toHexdump(ba2)); // size: 8
  ba2.append("901234567890");
  L_DEBUG(simpleqtlogger::SimpleQtLogger::toHexdump(ba2)); // size: 20
  ba2.append('\0');
  ba2.append('\1');
  ba2.append(30);
  ba2.append(31);
  ba2.append(" abc ABC!");
  L_DEBUG(simpleqtlogger::SimpleQtLogger::toHexdump(ba2)); // size: 33
  ba2.append(" Hello");
  L_DEBUG(simpleqtlogger::SimpleQtLogger::toHexdump(ba2)); // size: 39
  ba2.append(" xyz XYZ!");
  L_DEBUG(simpleqtlogger::SimpleQtLogger::toHexdump(ba2)); // size: 48

  L_INFO("Test hexdump 3");
  QByteArray ba3;
  for (unsigned char i = 32; i <= 126; ++i) {
    ba3.append(i);
  }
  L_DEBUG(simpleqtlogger::SimpleQtLogger::toHexdump(ba3)); // size: 95

  L_INFO("Test hexdump 4");
  QByteArray ba4;
  for (unsigned short i = 0; i < 256; ++i) {
    ba4.append(i);
  }
  L_DEBUG(simpleqtlogger::SimpleQtLogger::toHexdump(ba4)); // size: 256

  L_NOTE("Start");
#if (QT_VERSION >= QT_VERSION_CHECK(5, 4, 0))
  QTimer::singleShot(1000, this, &Task::slotRun);
  QTimer::singleShot(1000, this, &Task::slotRun);
  QTimer::singleShot(3000, this, &Task::slotRun);
  QTimer::singleShot(6000, this, &Task::theEnd);
#else
  QTimer::singleShot(1000, this, SLOT(slotRun()));
  QTimer::singleShot(1000, this, SLOT(slotRun()));
  QTimer::singleShot(3000, this, SLOT(slotRun()));
  QTimer::singleShot(6000, this, SLOT(theEnd()));
#endif
}

void Task::theEnd()
{
  L_FUNC("");
  L_NOTE("Bye bye");
  emit finished();
}

void Task::slotRun()
{
  L_FUNC("");
  static unsigned int id = 0;

  startWorkerThread(QString("%1").arg(++id, 2, 10, QLatin1Char('0')));
}

void Task::slotResultReady(const QString& result)
{
  LS_FUNC("");
  LS_INFO("WorkerThread: " << result);
}

void Task::slotLogForwarding(simpleqtlogger::LogLevel logLevel, const QString& logMessage)
{
  QTextStream out(stdout);
  out << "Log forwarding (" << logLevel << "): " << logMessage << '\n';
}

void Task::startWorkerThread(const QString& id)
{
  L_FUNC(QString("id='%1'").arg(id));

  WorkerThread *workerThread = new WorkerThread(id, this);
  connect(workerThread, SIGNAL(resultReady(const QString&)), this, SLOT(slotResultReady(const QString&)));
  connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
  workerThread->start();
}

void Task::testLogLevels(const QString& logMessage, int repeat)
{
  L_FUNC("");
  for(int i=0; i<repeat; ++i) { L_FATAL(logMessage); }
  for(int i=0; i<repeat; ++i) { L_ERROR(logMessage); }
  for(int i=0; i<repeat; ++i) { L_WARN(logMessage); }
  for(int i=0; i<repeat; ++i) { L_NOTE(logMessage); }
  for(int i=0; i<repeat; ++i) { L_INFO(logMessage); }
  for(int i=0; i<repeat; ++i) { L_DEBUG(logMessage); }
}

// -------------------------------------------------------------------------------------------------

WorkerThread::WorkerThread(const QString& id, QObject *parent)
  : QThread(parent)
  , _id(id)
{
  L_FUNC(QString("_id='%1'").arg(_id));
  // qDebug("WorkerThread::WorkerThread");
}

WorkerThread::~WorkerThread()
{
  L_FUNC(QString("_id='%1'").arg(_id));
  // qDebug("WorkerThread::~WorkerThread");
}

void WorkerThread::run()
{
  L_FUNC(QString("_id='%1'").arg(_id));
  // qDebug("WorkerThread::run");

  msleep(500); // [ms]
  QString result = QString("%1: Calculate: 6! = %2").arg(_id).arg(factorial(6));
  L_INFO(result);
  msleep(250); // [ms]
#if TEST_BURST > 0
  burst(10*1000); // queue full at ~49'000 ?!
#endif
  msleep(250); // [ms]

  emit resultReady(result);
}

unsigned int WorkerThread::factorial(unsigned int n)
{
  LS_FUNC("n=" << n);

  if(n > 2) {
    return n * factorial(n-1);
  }
  return n;
}

void WorkerThread::burst(unsigned int n)
{
  LS_FUNC("n=" << n);
  for(unsigned int i=0; i<n; ++i){
    L_INFO(QString("%1: Burst: %2").arg(_id).arg(i, 6, 10, QLatin1Char('0')));
  }
}
