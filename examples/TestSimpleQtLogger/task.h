/*
  Test Simple Logger for Qt

  Mario Ban, 05.2015

*/

#ifndef _TASK_H
#define _TASK_H

#include <QObject>

// -------------------------------------------------------------------------------------------------

class Task : public QObject
{
  Q_OBJECT

public:
  explicit Task(QObject *parent = 0);
  ~Task();

private slots:
  void init();
  void theEnd();

public slots:
  void slotRun();

signals:
  void finished();

private:
  unsigned int factorial(unsigned int n) const;

};

#endif // _TASK_H

/*
Marios-iMac:Qt mario$ ./build-TestSimpleQtLogger-Desktop_Qt_5_4_2_clang_64bit-Debug/TestSimpleQtLogger
SimpleQtLogger::SimpleQtLogger
SimpleQtLogger::setLogFileName
Current log-file: "testSimpleQtLogger.log"
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
SimpleQtLogger::~SimpleQtLogger
Marios-iMac:Qt mario$

Marios-iMac:Qt mario$ tail -Fn100 testSimpleQtLogger.log
2015-06-12 18:20:18.152 [I] Start logger
2015-06-12 18:20:18.154 [F] \ (Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:19)
2015-06-12 18:20:18.154 [F] / (Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:19)
2015-06-12 18:20:18.154 [F] \ (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:24)
2015-06-12 18:20:18.154 [I] +++ test Logger (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:26)
2015-06-12 18:20:18.154 [!] L_FATAL (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:27)
2015-06-12 18:20:18.154 [E] L_ERROR (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:28)
2015-06-12 18:20:18.154 [W] L_WARN (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:29)
2015-06-12 18:20:18.154 [I] L_INFO (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:30)
2015-06-12 18:20:18.154 [I] --- test Logger (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:32)
2015-06-12 18:20:18.154 [I] ? (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:34)
2015-06-12 18:20:18.154 [I] Trimmed (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:35)
2015-06-12 18:20:18.154 [I] JSON output 1:
{
  "firstName": "Mario"
  "age": 44
} (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:43)
2015-06-12 18:20:18.155 [I] JSON output 2:
{
  "firstName": "Mario"
  "age": 44
} (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:46)
2015-06-12 18:20:18.155 [F] / (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:24)
2015-06-12 18:20:18.255 [F] \ (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:61)
2015-06-12 18:20:18.255 [F] .\ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:18.255 [F] ..\ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:18.255 [F] ...\ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:18.255 [F] ....\ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:18.255 [F] .....\ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:18.255 [F] ...../ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:18.255 [F] ..../ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:18.255 [F] .../ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:18.255 [F] ../ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:18.255 [F] ./ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:18.255 [I] Calculate: 6! = 720 (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:63)
2015-06-12 18:20:18.255 [F] / (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:61)
2015-06-12 18:20:21.295 [F] \ (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:61)
2015-06-12 18:20:21.295 [F] .\ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:21.295 [F] ..\ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:21.295 [F] ...\ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:21.295 [F] ....\ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:21.295 [F] .....\ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:21.295 [F] ...../ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:21.295 [F] ..../ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:21.295 [F] .../ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:21.295 [F] ../ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:21.295 [F] ./ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:21.295 [I] Calculate: 6! = 720 (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:63)
2015-06-12 18:20:21.295 [F] / (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:61)
2015-06-12 18:20:23.298 [I] Current log-file size=11948 (rotation-size=10240) --> rolling
2015-06-12 18:20:24.294 [F] \ (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:61)
2015-06-12 18:20:24.295 [F] .\ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:24.295 [F] ..\ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:24.295 [F] ...\ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:24.295 [F] ....\ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:24.295 [F] .....\ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:24.295 [F] ...../ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:24.295 [F] ..../ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:24.295 [F] .../ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:24.295 [F] ../ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:24.295 [F] ./ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:24.295 [I] Calculate: 6! = 720 (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:63)
2015-06-12 18:20:24.295 [F] / (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:61)
2015-06-12 18:20:25.294 [F] \ (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:54)
2015-06-12 18:20:25.294 [I] Bye bye (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:55)
2015-06-12 18:20:25.294 [F] / (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:54)
Marios-iMac:Qt mario$
*/
