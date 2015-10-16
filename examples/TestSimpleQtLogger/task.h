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

#define TEST_BURST   0   /* 1: enable, 0: disable */

// -------------------------------------------------------------------------------------------------

class Task : public QObject
{
  Q_OBJECT

public:
  explicit Task(QObject *parent);
  ~Task();

private slots:
  void init();
  void theEnd();

public slots:
  void slotRun();
  void slotResultReady(const QString &result);

signals:
  void finished();

private:
  void startWorkerThread(const QString &id);
};

// -------------------------------------------------------------------------------------------------

class WorkerThread : public QThread
{
  Q_OBJECT

public:
  WorkerThread(const QString &id, QObject * parent);
  ~WorkerThread();

protected:
  void run();

signals:
  void resultReady(const QString &result);

private:
  static unsigned int factorial(unsigned int n);
  void burst(unsigned int n);

  const QString _id;
};

#endif // _TASK_H

/*
Marios-iMac:Qt mario$ ./build-TestSimpleQtLogger-Desktop_Qt_5_4_2_clang_64bit-Debug/TestSimpleQtLogger
SimpleQtLogger::SimpleQtLogger
SinkFileLog::SinkFileLog
SimpleQtLogger::setLogFileName
SinkFileLog::setLogFileName
Current log-file: "testSimpleQtLogger.log"
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
Removed "testSimpleQtLogger_10.log"
Moved "testSimpleQtLogger_09.log" to "testSimpleQtLogger_10.log"
Moved "testSimpleQtLogger_08.log" to "testSimpleQtLogger_09.log"
Moved "testSimpleQtLogger_07.log" to "testSimpleQtLogger_08.log"
Moved "testSimpleQtLogger_06.log" to "testSimpleQtLogger_07.log"
Moved "testSimpleQtLogger_05.log" to "testSimpleQtLogger_06.log"
Moved "testSimpleQtLogger_04.log" to "testSimpleQtLogger_05.log"
Moved "testSimpleQtLogger_03.log" to "testSimpleQtLogger_04.log"
Moved "testSimpleQtLogger_02.log" to "testSimpleQtLogger_03.log"
Moved "testSimpleQtLogger_01.log" to "testSimpleQtLogger_02.log"
Moved "testSimpleQtLogger.log" to "testSimpleQtLogger_01.log"
Current log-file: "testSimpleQtLogger.log"
Task::~Task
SimpleQtLogger::~SimpleQtLogger
SinkFileLog::~SinkFileLog
Marios-iMac:Qt mario$

Marios-iMac:Qt mario$ tail -Fn100 testSimpleQtLogger.log
2015-06-20 19:05:59.614 [00007fff7d752300] [I] Start file-log
2015-06-20 19:05:59.616 [00007fff7d752300] [F] \ (Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:20)
2015-06-20 19:05:59.617 [00007fff7d752300] [F] / (Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:20)
2015-06-20 19:05:59.617 [00007fff7d752300] [F] \ (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:32)
2015-06-20 19:05:59.617 [00007fff7d752300] [I] +++ test Logger (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:34)
2015-06-20 19:05:59.617 [00007fff7d752300] [!] L_FATAL (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:35)
2015-06-20 19:05:59.617 [00007fff7d752300] [E] L_ERROR (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:36)
2015-06-20 19:05:59.617 [00007fff7d752300] [W] L_WARN (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:37)
2015-06-20 19:05:59.617 [00007fff7d752300] [I] L_INFO (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:38)
2015-06-20 19:05:59.617 [00007fff7d752300] [I] --- test Logger (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:40)
2015-06-20 19:05:59.617 [00007fff7d752300] [I] ? (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:42)
2015-06-20 19:05:59.617 [00007fff7d752300] [I] Trimmed (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:43)
2015-06-20 19:05:59.617 [00007fff7d752300] [I] JSON output 1:
{
  "firstName": "Mario",
  "age": 44
} (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:51)
2015-06-20 19:05:59.617 [00007fff7d752300] [I] JSON output 2:
{
  "firstName": "Mario",
  "age": 44
} (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:54)
2015-06-20 19:05:59.617 [00007fff7d752300] [F] / (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:32)
2015-06-20 19:06:00.622 [00007fff7d752300] [F] \ (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:71)
2015-06-20 19:06:00.622 [00007fff7d752300] [F] .\ id='01' (startWorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:85)
2015-06-20 19:06:00.622 [00007fff7d752300] [F] ..\ _id='01' (WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:99)
2015-06-20 19:06:00.622 [00007fff7d752300] [F] ../ _id='01' (WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:99)
2015-06-20 19:06:00.622 [00007fff7d752300] [F] ./ id='01' (startWorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:85)
2015-06-20 19:06:00.622 [00007fff7d752300] [F] / (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:71)
2015-06-20 19:06:00.622 [00007fff7d752300] [F] \ (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:71)
2015-06-20 19:06:00.622 [00007fff7d752300] [F] .\ id='02' (startWorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:85)
2015-06-20 19:06:00.622 [00007fff7d752300] [F] ..\ _id='02' (WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:99)
2015-06-20 19:06:00.622 [00007fff7d752300] [F] ../ _id='02' (WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:99)
2015-06-20 19:06:00.622 [00007fff7d752300] [F] ./ id='02' (startWorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:85)
2015-06-20 19:06:00.622 [00007fff7d752300] [F] / (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:71)
2015-06-20 19:06:00.622 [0000000108bdc000] [F] \ _id='01' (run@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:111)
2015-06-20 19:06:00.622 [0000000108c5f000] [F] \ _id='02' (run@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:111)
2015-06-20 19:06:01.124 [0000000108bdc000] [F] .\ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:01.125 [0000000108c5f000] [F] .\ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:01.125 [0000000108bdc000] [F] ..\ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:01.125 [0000000108c5f000] [F] ..\ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:01.125 [0000000108bdc000] [F] ...\ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:01.125 [0000000108c5f000] [F] ...\ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:01.125 [0000000108c5f000] [F] ....\ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:01.125 [0000000108bdc000] [F] ....\ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:01.125 [0000000108c5f000] [F] .....\ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:01.125 [0000000108bdc000] [F] .....\ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:01.125 [0000000108c5f000] [F] ...../ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:01.125 [0000000108bdc000] [F] ...../ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:01.125 [0000000108c5f000] [F] ..../ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:01.125 [0000000108bdc000] [F] ..../ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:01.125 [0000000108c5f000] [F] .../ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:01.125 [0000000108bdc000] [F] .../ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:01.125 [0000000108bdc000] [F] ../ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:01.125 [0000000108c5f000] [F] ../ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:01.125 [0000000108bdc000] [F] ./ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:01.125 [0000000108bdc000] [I] 01: Calculate: 6! = 720 (run@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:116)
2015-06-20 19:06:01.125 [0000000108c5f000] [F] ./ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:01.125 [0000000108c5f000] [I] 02: Calculate: 6! = 720 (run@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:116)
2015-06-20 19:06:01.626 [00007fff7d752300] [F] \ (slotResultReady@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:79)
2015-06-20 19:06:01.626 [00007fff7d752300] [I] WorkerThread: 01: Calculate: 6! = 720 (slotResultReady@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:80)
2015-06-20 19:06:01.626 [00007fff7d752300] [F] / (slotResultReady@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:79)
2015-06-20 19:06:01.625 [0000000108bdc000] [F] / _id='01' (run@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:111)
2015-06-20 19:06:01.626 [00007fff7d752300] [F] \ (slotResultReady@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:79)
2015-06-20 19:06:01.626 [00007fff7d752300] [I] WorkerThread: 02: Calculate: 6! = 720 (slotResultReady@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:80)
2015-06-20 19:06:01.626 [00007fff7d752300] [F] / (slotResultReady@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:79)
2015-06-20 19:06:01.626 [0000000108c5f000] [F] / _id='02' (run@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:111)
2015-06-20 19:06:01.626 [00007fff7d752300] [F] \ _id='01' (~WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:105)
2015-06-20 19:06:01.626 [00007fff7d752300] [F] / _id='01' (~WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:105)
2015-06-20 19:06:01.626 [00007fff7d752300] [F] \ _id='02' (~WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:105)
2015-06-20 19:06:01.626 [00007fff7d752300] [F] / _id='02' (~WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:105)
2015-06-20 19:06:02.767 [00007fff7d752300] [F] \ (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:71)
2015-06-20 19:06:02.767 [00007fff7d752300] [F] .\ id='03' (startWorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:85)
2015-06-20 19:06:02.768 [00007fff7d752300] [F] ..\ _id='03' (WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:99)
2015-06-20 19:06:02.768 [00007fff7d752300] [F] ../ _id='03' (WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:99)
2015-06-20 19:06:02.768 [00007fff7d752300] [F] ./ id='03' (startWorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:85)
2015-06-20 19:06:02.768 [00007fff7d752300] [F] / (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:71)
2015-06-20 19:06:02.768 [0000000108bdc000] [F] \ _id='03' (run@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:111)
2015-06-20 19:06:03.269 [0000000108bdc000] [F] .\ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:03.269 [0000000108bdc000] [F] ..\ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:03.269 [0000000108bdc000] [F] ...\ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:03.269 [0000000108bdc000] [F] ....\ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:03.269 [0000000108bdc000] [F] .....\ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:03.269 [0000000108bdc000] [F] ...../ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:03.269 [0000000108bdc000] [F] ..../ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:03.269 [0000000108bdc000] [F] .../ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:03.269 [0000000108bdc000] [F] ../ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:03.269 [0000000108bdc000] [F] ./ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:03.269 [0000000108bdc000] [I] 03: Calculate: 6! = 720 (run@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:116)
2015-06-20 19:06:03.774 [00007fff7d752300] [F] \ (slotResultReady@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:79)
2015-06-20 19:06:03.774 [00007fff7d752300] [I] WorkerThread: 03: Calculate: 6! = 720 (slotResultReady@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:80)
2015-06-20 19:06:03.774 [00007fff7d752300] [F] / (slotResultReady@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:79)
2015-06-20 19:06:03.774 [0000000108bdc000] [F] / _id='03' (run@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:111)
2015-06-20 19:06:03.774 [00007fff7d752300] [F] \ _id='03' (~WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:105)
2015-06-20 19:06:03.774 [00007fff7d752300] [F] / _id='03' (~WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:105)
2015-06-20 19:06:04.775 [00007fff7d752300] [I] Current log-file size=11797 (rotation-size=10240) --> rolling
2015-06-20 19:06:04.776 [00007fff7d752300] [I] Log-file rolling done (time elapsed: 2 ms)
2015-06-20 19:06:04.777 [00007fff7d752300] [F] \ (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:64)
2015-06-20 19:06:04.777 [00007fff7d752300] [I] Bye bye (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:65)
2015-06-20 19:06:04.777 [00007fff7d752300] [F] / (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:64)
2015-06-20 19:06:04.777 [00007fff7d752300] [F] \ (~Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:26)
2015-06-20 19:06:04.777 [00007fff7d752300] [F] / (~Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:26)
Marios-iMac:Qt mario$
*/
