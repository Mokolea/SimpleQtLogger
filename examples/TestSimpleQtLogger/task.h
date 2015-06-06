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
2015-06-06 19:55:11.667 [I] Start logger
2015-06-06 19:55:11.669 [F] \ (Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:19)
2015-06-06 19:55:11.669 [F] / (Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:19)
2015-06-06 19:55:11.669 [F] \ (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:24)
2015-06-06 19:55:11.669 [I] +++ test Logger (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:26)
2015-06-06 19:55:11.669 [!] LogFatal (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:27)
2015-06-06 19:55:11.669 [E] LogError (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:28)
2015-06-06 19:55:11.669 [W] LogWarning (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:29)
2015-06-06 19:55:11.669 [I] LogInfo (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:30)
2015-06-06 19:55:11.669 [I] --- test Logger (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:32)
2015-06-06 19:55:11.669 [F] / (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:24)
2015-06-06 19:55:11.773 [F] \ (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:47)
2015-06-06 19:55:11.774 [F] .\ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 19:55:11.774 [F] ..\ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 19:55:11.774 [F] ...\ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 19:55:11.774 [F] ....\ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 19:55:11.774 [F] ..../ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 19:55:11.774 [F] .../ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 19:55:11.774 [F] ../ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 19:55:11.774 [F] ./ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 19:55:11.774 [I] Calculate: 5! = 120 (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:49)
2015-06-06 19:55:11.774 [F] / (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:47)
2015-06-06 19:55:14.929 [F] \ (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:47)
2015-06-06 19:55:14.929 [F] .\ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 19:55:14.929 [F] ..\ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 19:55:14.929 [F] ...\ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 19:55:14.929 [F] ....\ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 19:55:14.929 [F] ..../ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 19:55:14.929 [F] .../ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 19:55:14.929 [F] ../ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 19:55:14.929 [F] ./ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 19:55:14.929 [I] Calculate: 5! = 120 (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:49)
2015-06-06 19:55:14.929 [F] / (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:47)
2015-06-06 19:55:16.512 [I] Current log-file size=14511 (rolling-size=10000) --> rolling
2015-06-06 19:55:18.008 [F] \ (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:47)
2015-06-06 19:55:18.008 [F] .\ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 19:55:18.008 [F] ..\ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 19:55:18.008 [F] ...\ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 19:55:18.008 [F] ....\ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 19:55:18.008 [F] ..../ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 19:55:18.008 [F] .../ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 19:55:18.008 [F] ../ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 19:55:18.008 [F] ./ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 19:55:18.008 [I] Calculate: 5! = 120 (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:49)
2015-06-06 19:55:18.008 [F] / (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:47)
2015-06-06 19:55:18.509 [F] \ (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:40)
2015-06-06 19:55:18.509 [I] Bye bye (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:41)
2015-06-06 19:55:18.509 [F] / (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:40)
Marios-iMac:Qt mario$
*/
