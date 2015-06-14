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
Task::Task
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
Marios-iMac:Qt mario$

Marios-iMac:Qt mario$ tail -Fn100 testSimpleQtLogger.log
2015-06-14 11:27:02.067 [I] Start logger
2015-06-14 11:27:02.069 [F] \ (Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:19)
2015-06-14 11:27:02.069 [F] / (Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:19)
2015-06-14 11:27:02.069 [F] \ (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:31)
2015-06-14 11:27:02.069 [I] +++ test Logger (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:33)
2015-06-14 11:27:02.069 [!] L_FATAL (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:34)
2015-06-14 11:27:02.069 [E] L_ERROR (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:35)
2015-06-14 11:27:02.069 [W] L_WARN (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:36)
2015-06-14 11:27:02.069 [I] L_INFO (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:37)
2015-06-14 11:27:02.069 [I] --- test Logger (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:39)
2015-06-14 11:27:02.069 [I] ? (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:41)
2015-06-14 11:27:02.070 [I] Trimmed (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:42)
2015-06-14 11:27:02.070 [I] JSON output 1:
{
  "firstName": "Mario"
  "age": 44
} (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:50)
2015-06-14 11:27:02.070 [I] JSON output 2:
{
  "firstName": "Mario"
  "age": 44
} (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:53)
2015-06-14 11:27:02.070 [F] / (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:31)
2015-06-14 11:27:02.170 [F] \ (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:68)
2015-06-14 11:27:02.170 [F] .\ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:02.170 [F] ..\ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:02.170 [F] ...\ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:02.170 [F] ....\ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:02.170 [F] .....\ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:02.170 [F] ...../ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:02.170 [F] ..../ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:02.170 [F] .../ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:02.170 [F] ../ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:02.170 [F] ./ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:02.170 [I] Calculate: 6! = 720 (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-14 11:27:02.170 [F] / (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:68)
2015-06-14 11:27:05.127 [F] \ (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:68)
2015-06-14 11:27:05.127 [F] .\ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:05.127 [F] ..\ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:05.127 [F] ...\ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:05.127 [F] ....\ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:05.127 [F] .....\ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:05.127 [F] ...../ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:05.127 [F] ..../ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:05.127 [F] .../ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:05.127 [F] ../ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:05.127 [F] ./ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:05.127 [I] Calculate: 6! = 720 (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-14 11:27:05.127 [F] / (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:68)
2015-06-14 11:27:06.821 [I] Current log-file size=12332 (rotation-size=10240) --> rolling
2015-06-14 11:27:08.127 [F] \ (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:68)
2015-06-14 11:27:08.127 [F] .\ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:08.127 [F] ..\ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:08.127 [F] ...\ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:08.127 [F] ....\ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:08.127 [F] .....\ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:08.127 [F] ...../ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:08.127 [F] ..../ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:08.127 [F] .../ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:08.127 [F] ../ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:08.127 [F] ./ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:08.127 [I] Calculate: 6! = 720 (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-14 11:27:08.127 [F] / (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:68)
2015-06-14 11:27:08.723 [F] \ (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:61)
2015-06-14 11:27:08.723 [I] Bye bye (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:62)
2015-06-14 11:27:08.723 [F] / (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:61)
2015-06-14 11:27:08.723 [F] \ (~Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:25)
2015-06-14 11:27:08.723 [F] / (~Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:25)
Marios-iMac:Qt mario$
*/
