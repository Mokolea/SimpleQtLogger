/*
  Test Simple Logger for Qt

  Mario Ban, 05.2015
  https://github.com/Mokolea/SimpleQtLogger

  GNU Lesser General Public License v2.1
  Copyright (C) 2015 Mario Ban
*/

#ifndef _TASK_H
#define _TASK_H

#include <QObject>
#include <QString>
#include <QThread>

#include "simpleQtLogger.h"

#define TEST_BURST   0   /* 1: enable, 0: disable */

// -------------------------------------------------------------------------------------------------

class Task : public QObject
{
  Q_OBJECT

public:
  explicit Task(QObject *parent);
  ~Task();

private slots:
  void theEnd();

public slots:
  void init();
  void slotRun();
  void slotResultReady(const QString& result);
  void slotLogForwarding(simpleqtlogger::LogLevel logLevel, const QString& logMessage);

signals:
  void finished();

private:
  void startWorkerThread(const QString& id);
  void testLogLevels(const QString& logMessage, int repeat);
};

// -------------------------------------------------------------------------------------------------

class WorkerThread : public QThread
{
  Q_OBJECT

public:
  WorkerThread(const QString& id, QObject * parent);
  ~WorkerThread();

protected:
  void run();

signals:
  void resultReady(const QString& result);

private:
  static unsigned int factorial(unsigned int n);
  void burst(unsigned int n);

  const QString _id;
};

#endif // _TASK_H

/*
Marios-iMac:Qt mario$ ./build-TestSimpleQtLogger-Desktop_Qt_5_5_0_clang_64bit-Debug/TestSimpleQtLogger
SimpleQtLogger::SimpleQtLogger
Current log-file: "testSimpleQtLogger.log" role "main"
Current log-file: "testSimpleQtLoggerWarn.log" role "warn"
Task::Task
WorkerThread::WorkerThread
WorkerThread::run
WorkerThread::WorkerThread
WorkerThread::run
WorkerThread::~WorkerThread
WorkerThread::~WorkerThread
WorkerThread::WorkerThread
WorkerThread::run
WorkerThread::~WorkerThread
Removed "testSimpleQtLogger_10.log" role "main"
Moved "testSimpleQtLogger_09.log" to "testSimpleQtLogger_10.log" role "main"
Moved "testSimpleQtLogger_08.log" to "testSimpleQtLogger_09.log" role "main"
Moved "testSimpleQtLogger_07.log" to "testSimpleQtLogger_08.log" role "main"
Moved "testSimpleQtLogger_06.log" to "testSimpleQtLogger_07.log" role "main"
Moved "testSimpleQtLogger_05.log" to "testSimpleQtLogger_06.log" role "main"
Moved "testSimpleQtLogger_04.log" to "testSimpleQtLogger_05.log" role "main"
Moved "testSimpleQtLogger_03.log" to "testSimpleQtLogger_04.log" role "main"
Moved "testSimpleQtLogger_02.log" to "testSimpleQtLogger_03.log" role "main"
Moved "testSimpleQtLogger_01.log" to "testSimpleQtLogger_02.log" role "main"
Moved "testSimpleQtLogger.log" to "testSimpleQtLogger_01.log" role "main"
Current log-file: "testSimpleQtLogger.log" role "main"
Task::~Task
SimpleQtLogger::~SimpleQtLogger
Marios-iMac:Qt mario$

Marios-iMac:Qt mario$ tail -Fn100 testSimpleQtLogger.log
2015-10-23 18:39:41.036 [00007fff7c63d000] [-] Start file-log 'main'
2015-10-23 18:39:41.060 [00007fff7c63d000] [F] \ (Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:23)
2015-10-23 18:39:41.061 [00007fff7c63d000] [F] / (Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:23)
2015-10-23 18:39:41.061 [00007fff7c63d000] [F] \ (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:35)
2015-10-23 18:39:41.061 [00007fff7c63d000] [I] +++ test Logger (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:37)
2015-10-23 18:39:41.061 [00007fff7c63d000] [!] L_FATAL (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:38)
2015-10-23 18:39:41.061 [00007fff7c63d000] [E] L_ERROR (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:39)
2015-10-23 18:39:41.061 [00007fff7c63d000] [W] L_WARN (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:40)
2015-10-23 18:39:41.061 [00007fff7c63d000] [I] L_INFO (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:41)
2015-10-23 18:39:41.061 [00007fff7c63d000] [I] --- test Logger (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:43)
2015-10-23 18:39:41.061 [00007fff7c63d000] [I] ? (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:45)
2015-10-23 18:39:41.061 [00007fff7c63d000] [I] Trimmed (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:46)
2015-10-23 18:39:41.061 [00007fff7c63d000] [I] UTF-8 Unicode text: äöü àéè (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:47)
2015-10-23 18:39:41.061 [00007fff7c63d000] [I] JSON output 1:
{
  "firstName": "Mario",
  "age": 44
} (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:55)
2015-10-23 18:39:41.061 [00007fff7c63d000] [I] JSON output 2:
{
  "firstName": "Mario",
  "age": 44
} (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:58)
2015-10-23 18:39:41.061 [00007fff7c63d000] [F] / (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:35)
2015-10-23 18:39:42.064 [00007fff7c63d000] [F] \ (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:75)
2015-10-23 18:39:42.064 [00007fff7c63d000] [F] .\ id='01' (startWorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:89)
2015-10-23 18:39:42.064 [00007fff7c63d000] [F] ..\ _id='01' (WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:103)
2015-10-23 18:39:42.064 [00007fff7c63d000] [F] ../ _id='01' (WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:103)
2015-10-23 18:39:42.064 [00007fff7c63d000] [F] ./ id='01' (startWorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:89)
2015-10-23 18:39:42.064 [00007fff7c63d000] [F] / (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:75)
2015-10-23 18:39:42.064 [00007fff7c63d000] [F] \ (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:75)
2015-10-23 18:39:42.064 [00007fff7c63d000] [F] .\ id='02' (startWorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:89)
2015-10-23 18:39:42.064 [00007fff7c63d000] [F] ..\ _id='02' (WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:103)
2015-10-23 18:39:42.064 [00007fff7c63d000] [F] ../ _id='02' (WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:103)
2015-10-23 18:39:42.065 [00007fff7c63d000] [F] ./ id='02' (startWorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:89)
2015-10-23 18:39:42.065 [00007fff7c63d000] [F] / (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:75)
2015-10-23 18:39:42.064 [000070000019a000] [F] \ _id='01' (run@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:115)
2015-10-23 18:39:42.065 [000070000021d000] [F] \ _id='02' (run@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:115)
2015-10-23 18:39:42.565 [000070000019a000] [F] .\ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:42.565 [000070000019a000] [F] ..\ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:42.565 [000070000019a000] [F] ...\ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:42.565 [000070000019a000] [F] ....\ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:42.565 [000070000019a000] [F] .....\ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:42.565 [000070000019a000] [F] ...../ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:42.565 [000070000019a000] [F] ..../ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:42.565 [000070000019a000] [F] .../ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:42.565 [000070000021d000] [F] .\ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:42.565 [000070000021d000] [F] ..\ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:42.565 [000070000019a000] [F] ../ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:42.565 [000070000019a000] [F] ./ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:42.565 [000070000021d000] [F] ...\ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:42.565 [000070000019a000] [I] 01: Calculate: 6! = 720 (run@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:120)
2015-10-23 18:39:42.565 [000070000021d000] [F] ....\ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:42.565 [000070000021d000] [F] .....\ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:42.565 [000070000021d000] [F] ...../ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:42.565 [000070000021d000] [F] ..../ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:42.565 [000070000021d000] [F] .../ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:42.565 [000070000021d000] [F] ../ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:42.565 [000070000021d000] [F] ./ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:42.565 [000070000021d000] [I] 02: Calculate: 6! = 720 (run@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:120)
2015-10-23 18:39:43.069 [00007fff7c63d000] [F] \ (slotResultReady@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:83)
2015-10-23 18:39:43.069 [00007fff7c63d000] [I] WorkerThread: 01: Calculate: 6! = 720 (slotResultReady@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:84)
2015-10-23 18:39:43.069 [00007fff7c63d000] [F] / (slotResultReady@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:83)
2015-10-23 18:39:43.069 [00007fff7c63d000] [F] \ (slotResultReady@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:83)
2015-10-23 18:39:43.069 [00007fff7c63d000] [I] WorkerThread: 02: Calculate: 6! = 720 (slotResultReady@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:84)
2015-10-23 18:39:43.069 [00007fff7c63d000] [F] / (slotResultReady@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:83)
2015-10-23 18:39:43.069 [000070000021d000] [F] / _id='02' (run@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:115)
2015-10-23 18:39:43.069 [000070000019a000] [F] / _id='01' (run@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:115)
2015-10-23 18:39:43.069 [00007fff7c63d000] [F] \ _id='02' (~WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:109)
2015-10-23 18:39:43.069 [00007fff7c63d000] [F] / _id='02' (~WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:109)
2015-10-23 18:39:43.069 [00007fff7c63d000] [F] \ _id='01' (~WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:109)
2015-10-23 18:39:43.069 [00007fff7c63d000] [F] / _id='01' (~WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:109)
2015-10-23 18:39:43.914 [00007fff7c63d000] [F] \ (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:75)
2015-10-23 18:39:43.914 [00007fff7c63d000] [F] .\ id='03' (startWorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:89)
2015-10-23 18:39:43.914 [00007fff7c63d000] [F] ..\ _id='03' (WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:103)
2015-10-23 18:39:43.914 [00007fff7c63d000] [F] ../ _id='03' (WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:103)
2015-10-23 18:39:43.914 [00007fff7c63d000] [F] ./ id='03' (startWorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:89)
2015-10-23 18:39:43.914 [00007fff7c63d000] [F] / (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:75)
2015-10-23 18:39:43.914 [000070000019a000] [F] \ _id='03' (run@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:115)
2015-10-23 18:39:44.418 [000070000019a000] [F] .\ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:44.418 [000070000019a000] [F] ..\ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:44.418 [000070000019a000] [F] ...\ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:44.418 [000070000019a000] [F] ....\ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:44.418 [000070000019a000] [F] .....\ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:44.418 [000070000019a000] [F] ...../ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:44.418 [000070000019a000] [F] ..../ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:44.418 [000070000019a000] [F] .../ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:44.418 [000070000019a000] [F] ../ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:44.418 [000070000019a000] [F] ./ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:132)
2015-10-23 18:39:44.418 [000070000019a000] [I] 03: Calculate: 6! = 720 (run@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:120)
2015-10-23 18:39:44.925 [00007fff7c63d000] [F] \ (slotResultReady@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:83)
2015-10-23 18:39:44.925 [00007fff7c63d000] [I] WorkerThread: 03: Calculate: 6! = 720 (slotResultReady@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:84)
2015-10-23 18:39:44.925 [00007fff7c63d000] [F] / (slotResultReady@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:83)
2015-10-23 18:39:44.925 [000070000019a000] [F] / _id='03' (run@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:115)
2015-10-23 18:39:44.925 [00007fff7c63d000] [F] \ _id='03' (~WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:109)
2015-10-23 18:39:44.925 [00007fff7c63d000] [F] / _id='03' (~WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:109)
2015-10-23 18:39:45.846 [00007fff7c63d000] [-] Current log-file 'main' size=11963 (rotation-size=10000) --> rolling
2015-10-23 18:39:45.982 [00007fff7c63d000] [-] Log-file 'main' rolling done (time elapsed: 136 ms)
2015-10-23 18:39:46.846 [00007fff7c63d000] [F] \ (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:68)
2015-10-23 18:39:46.847 [00007fff7c63d000] [I] Bye bye (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:69)
2015-10-23 18:39:46.847 [00007fff7c63d000] [F] / (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:68)
2015-10-23 18:39:46.847 [00007fff7c63d000] [F] \ (~Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:29)
2015-10-23 18:39:46.847 [00007fff7c63d000] [F] / (~Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:29)
Marios-iMac:Qt mario$

Marios-iMac:Qt mario$ tail -Fn100 testSimpleQtLoggerWarn.log
2015-10-23 18:39:41.039 [00007fff7c63d000] [-] Start file-log 'warn'
2015-10-23 18:39:41.061 [00007fff7c63d000] [!] L_FATAL (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:38)
2015-10-23 18:39:41.061 [00007fff7c63d000] [E] L_ERROR (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:39)
2015-10-23 18:39:41.061 [00007fff7c63d000] [W] L_WARN (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:40)
Marios-iMac:Qt mario$
*/
