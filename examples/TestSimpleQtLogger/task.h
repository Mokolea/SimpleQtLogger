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

Marios-iMac:Qt mario$ cat testSimpleQtLogger.log
2015-06-06 12:48:26.513 [F] \ (Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:19)
2015-06-06 12:48:26.515 [F] / (Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:19)
2015-06-06 12:48:26.515 [F] \ (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:24)
2015-06-06 12:48:26.515 [I] +++ test Logger (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:26)
2015-06-06 12:48:26.515 [!] LogFatal (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:27)
2015-06-06 12:48:26.515 [E] LogError (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:28)
2015-06-06 12:48:26.515 [W] LogWarning (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:29)
2015-06-06 12:48:26.515 [I] LogInfo (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:30)
2015-06-06 12:48:26.515 [I] --- test Logger (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:32)
2015-06-06 12:48:26.515 [F] / (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:24)
2015-06-06 12:48:26.616 [F] \ (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:47)
2015-06-06 12:48:26.616 [F] .\ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 12:48:26.616 [F] ..\ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 12:48:26.616 [F] ...\ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 12:48:26.617 [F] ....\ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 12:48:26.617 [F] ..../ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 12:48:26.617 [F] .../ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 12:48:26.617 [F] ../ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 12:48:26.617 [F] ./ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 12:48:26.617 [I] Calculate: 5! = 120 (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:49)
2015-06-06 12:48:26.617 [F] / (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:47)
2015-06-06 12:48:29.528 [F] \ (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:47)
2015-06-06 12:48:29.528 [F] .\ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 12:48:29.528 [F] ..\ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 12:48:29.528 [F] ...\ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 12:48:29.528 [F] ....\ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 12:48:29.528 [F] ..../ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 12:48:29.528 [F] .../ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 12:48:29.528 [F] ../ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 12:48:29.528 [F] ./ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 12:48:29.528 [I] Calculate: 5! = 120 (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:49)
2015-06-06 12:48:29.528 [F] / (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:47)
2015-06-06 12:48:31.265 [I] Current log-file size=3335 (checkLogFileRolling@../SimpleQtLogger/simpleQtLogger.cpp:164)
2015-06-06 12:48:32.528 [F] \ (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:47)
2015-06-06 12:48:32.528 [F] .\ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 12:48:32.528 [F] ..\ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 12:48:32.528 [F] ...\ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 12:48:32.528 [F] ....\ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 12:48:32.528 [F] ..../ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 12:48:32.528 [F] .../ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 12:48:32.528 [F] ../ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 12:48:32.528 [F] ./ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:56)
2015-06-06 12:48:32.528 [I] Calculate: 5! = 120 (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:49)
2015-06-06 12:48:32.528 [F] / (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:47)
2015-06-06 12:48:33.169 [F] \ (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:40)
2015-06-06 12:48:33.169 [I] Bye bye (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:41)
2015-06-06 12:48:33.169 [F] / (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:40)
Marios-iMac:Qt mario$
*/
