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
SimpleQtLogger::~SimpleQtLogger
Marios-iMac:Qt mario$

Marios-iMac:Qt mario$ tail -Fn100 testSimpleQtLogger.log
2015-06-07 10:05:37.220 [I] Start logger
2015-06-07 10:05:37.222 [F] \ (Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:19)
2015-06-07 10:05:37.222 [F] / (Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:19)
2015-06-07 10:05:37.222 [F] \ (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:24)
2015-06-07 10:05:37.222 [I] +++ test Logger (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:26)
2015-06-07 10:05:37.222 [!] LogFatal (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:27)
2015-06-07 10:05:37.222 [E] LogError (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:28)
2015-06-07 10:05:37.222 [W] LogWarning (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:29)
2015-06-07 10:05:37.222 [I] LogInfo (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:30)
2015-06-07 10:05:37.222 [I] --- test Logger (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:32)
2015-06-07 10:05:37.222 [I] ? (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:34)
2015-06-07 10:05:37.222 [I] Trimmed (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:35)
2015-06-07 10:05:37.222 [I] JSON output 1:
{
  "firstName": "Mario"
  "age": 44
} (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:43)
2015-06-07 10:05:37.222 [I] JSON output 2:
{
  "firstName": "Mario"
  "age": 44
} (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:46)
2015-06-07 10:05:37.223 [F] / (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:24)
2015-06-07 10:05:37.323 [F] \ (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:61)
2015-06-07 10:05:37.324 [F] .\ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:37.324 [F] ..\ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:37.324 [F] ...\ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:37.324 [F] ....\ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:37.324 [F] ..../ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:37.324 [F] .../ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:37.324 [F] ../ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:37.324 [F] ./ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:37.324 [I] Calculate: 5! = 120 (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:63)
2015-06-07 10:05:37.324 [F] / (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:61)
2015-06-07 10:05:40.478 [F] \ (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:61)
2015-06-07 10:05:40.478 [F] .\ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:40.478 [F] ..\ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:40.478 [F] ...\ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:40.478 [F] ....\ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:40.478 [F] ..../ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:40.478 [F] .../ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:40.478 [F] ../ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:40.479 [F] ./ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:40.479 [I] Calculate: 5! = 120 (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:63)
2015-06-07 10:05:40.479 [F] / (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:61)
2015-06-07 10:05:42.041 [I] Current log-file size=10650 (rolling-size=10000) --> rolling
2015-06-07 10:05:43.546 [F] \ (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:61)
2015-06-07 10:05:43.546 [F] .\ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:43.546 [F] ..\ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:43.546 [F] ...\ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:43.546 [F] ....\ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:43.546 [F] ..../ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:43.546 [F] .../ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:43.546 [F] ../ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:43.546 [F] ./ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:43.546 [I] Calculate: 5! = 120 (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:63)
2015-06-07 10:05:43.546 [F] / (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:61)
2015-06-07 10:05:44.041 [F] \ (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:54)
2015-06-07 10:05:44.041 [I] Bye bye (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:55)
2015-06-07 10:05:44.041 [F] / (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:54)
Marios-iMac:Qt mario$
*/
