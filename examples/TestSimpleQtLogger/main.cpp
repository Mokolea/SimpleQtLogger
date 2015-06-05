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
2015-06-05 19:25:31.366 [F] \ (Task@../TestSimpleQtLogger/task.cpp:19)
2015-06-05 19:25:31.368 [F] / (Task@../TestSimpleQtLogger/task.cpp:19)
2015-06-05 19:25:31.368 [F] \ (init@../TestSimpleQtLogger/task.cpp:24)
2015-06-05 19:25:31.368 [I] +++ test Logger (init@../TestSimpleQtLogger/task.cpp:26)
2015-06-05 19:25:31.368 [!] LogFatal (init@../TestSimpleQtLogger/task.cpp:27)
2015-06-05 19:25:31.368 [E] LogError (init@../TestSimpleQtLogger/task.cpp:28)
2015-06-05 19:25:31.368 [W] LogWarning (init@../TestSimpleQtLogger/task.cpp:29)
2015-06-05 19:25:31.368 [I] LogInfo (init@../TestSimpleQtLogger/task.cpp:30)
2015-06-05 19:25:31.368 [I] --- test Logger (init@../TestSimpleQtLogger/task.cpp:32)
2015-06-05 19:25:31.368 [F] / (init@../TestSimpleQtLogger/task.cpp:24)
2015-06-05 19:25:31.368 [F] \ (slotRun@../TestSimpleQtLogger/task.cpp:39)
2015-06-05 19:25:31.368 [F] .\ n=5 (factorial@../TestSimpleQtLogger/task.cpp:48)
2015-06-05 19:25:31.368 [F] ..\ n=4 (factorial@../TestSimpleQtLogger/task.cpp:48)
2015-06-05 19:25:31.368 [F] ...\ n=3 (factorial@../TestSimpleQtLogger/task.cpp:48)
2015-06-05 19:25:31.368 [F] ....\ n=2 (factorial@../TestSimpleQtLogger/task.cpp:48)
2015-06-05 19:25:31.368 [F] ..../ n=2 (factorial@../TestSimpleQtLogger/task.cpp:48)
2015-06-05 19:25:31.368 [F] .../ n=3 (factorial@../TestSimpleQtLogger/task.cpp:48)
2015-06-05 19:25:31.368 [F] ../ n=4 (factorial@../TestSimpleQtLogger/task.cpp:48)
2015-06-05 19:25:31.368 [F] ./ n=5 (factorial@../TestSimpleQtLogger/task.cpp:48)
2015-06-05 19:25:31.368 [I] Calculate: 5! = 120 (slotRun@../TestSimpleQtLogger/task.cpp:41)
2015-06-05 19:25:31.368 [F] / (slotRun@../TestSimpleQtLogger/task.cpp:39)
Marios-iMac:Qt mario$
*/
