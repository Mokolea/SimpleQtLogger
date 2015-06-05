/*
  Test Simple Logger for Qt

  Mario Ban, 05.2015

*/

#include <QCoreApplication>
#include <QTimer>

#include "task.h"
#include "simpleQtLogger.h"

SimpleQtLogger simpleQtLogger_;

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  simpleQtLogger_.setLogFileName("testSimpleQtLogger.log", 20, 4); // TODO test
  SQT_LOG_ENABLE_FUNCTION = true;

  Task *task = new Task(&a);
  QObject::connect(task, SIGNAL(finished()), &a, SLOT(quit()));
  QTimer::singleShot(0, task, SLOT(init()));

  return a.exec();
}

/*
Marios-iMac:Qt mario$ ./build-TestSimpleQtLogger-Desktop_Qt_5_4_2_clang_64bit-Debug/TestSimpleQtLogger
SimpleQtLogger::SimpleQtLogger
SimpleQtLogger::setLogFileName
SimpleQtLogger::~SimpleQtLogger
Marios-iMac:Qt mario$

Marios-iMac:Qt mario$ cat testSimpleQtLogger.log
2015-06-05 21:10:36.245 [F] \ (Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:19)
2015-06-05 21:10:36.248 [F] / (Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:19)
2015-06-05 21:10:36.248 [F] \ (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:24)
2015-06-05 21:10:36.248 [I] +++ test Logger (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:26)
2015-06-05 21:10:36.248 [!] LogFatal (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:27)
2015-06-05 21:10:36.248 [E] LogError (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:28)
2015-06-05 21:10:36.248 [W] LogWarning (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:29)
2015-06-05 21:10:36.248 [I] LogInfo (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:30)
2015-06-05 21:10:36.248 [I] --- test Logger (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:32)
2015-06-05 21:10:36.248 [F] / (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:24)
2015-06-05 21:10:36.248 [F] \ (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:39)
2015-06-05 21:10:36.248 [F] .\ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:48)
2015-06-05 21:10:36.248 [F] ..\ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:48)
2015-06-05 21:10:36.248 [F] ...\ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:48)
2015-06-05 21:10:36.248 [F] ....\ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:48)
2015-06-05 21:10:36.248 [F] ..../ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:48)
2015-06-05 21:10:36.248 [F] .../ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:48)
2015-06-05 21:10:36.248 [F] ../ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:48)
2015-06-05 21:10:36.248 [F] ./ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:48)
2015-06-05 21:10:36.248 [I] Calculate: 5! = 120 (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:41)
2015-06-05 21:10:36.248 [F] / (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:39)
Marios-iMac:Qt mario$
*/
