/*
  Test Simple Logger for Qt

  Mario Ban, 05.2015

*/

#include <QCoreApplication>
#include <QTimer>

#include "task.h"
#include "SimpleQtLogger.h"

SimpleQtLogger simpleQtLogger_;

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  simpleQtLogger_.setLogFileName("test.log", 100, 10);
  SQT_LOG_ENABLE_FUNCTION = true;

  Task *task = new Task(&a);
  QObject::connect(task, SIGNAL(finished()), &a, SLOT(quit()));
  QTimer::singleShot(0, task, SLOT(init()));

  return a.exec();
}

/*
Marios-iMac:build-TestSimpleQtLogger-Desktop_Qt_5_4_2_clang_64bit-Debug mario$ ./TestSimpleQtLogger
SimpleQtLogger::SimpleQtLogger
SimpleQtLogger::setLogFileName
test.log: [F] \ Task::Task (Task@../TestSimpleQtLogger/task.cpp:19)
test.log: [F] / Task::Task (Task@../TestSimpleQtLogger/task.cpp:19)
test.log: [F] \ Task::init (init@../TestSimpleQtLogger/task.cpp:24)
test.log: [I] +++ test Logger (init@../TestSimpleQtLogger/task.cpp:26)
test.log: [!] LogFatal (init@../TestSimpleQtLogger/task.cpp:27)
test.log: [E] LogError (init@../TestSimpleQtLogger/task.cpp:28)
test.log: [W] LogWarning (init@../TestSimpleQtLogger/task.cpp:29)
test.log: [I] LogInfo (init@../TestSimpleQtLogger/task.cpp:30)
test.log: [I] --- test Logger (init@../TestSimpleQtLogger/task.cpp:32)
test.log: [F] / Task::init (init@../TestSimpleQtLogger/task.cpp:24)
test.log: [F] \ Task::slotRun (slotRun@../TestSimpleQtLogger/task.cpp:39)
test.log: [F]  \ Task::factorial(5) (factorial@../TestSimpleQtLogger/task.cpp:48)
test.log: [F]   \ Task::factorial(4) (factorial@../TestSimpleQtLogger/task.cpp:48)
test.log: [F]    \ Task::factorial(3) (factorial@../TestSimpleQtLogger/task.cpp:48)
test.log: [F]     \ Task::factorial(2) (factorial@../TestSimpleQtLogger/task.cpp:48)
test.log: [F]     / Task::factorial(2) (factorial@../TestSimpleQtLogger/task.cpp:48)
test.log: [F]    / Task::factorial(3) (factorial@../TestSimpleQtLogger/task.cpp:48)
test.log: [F]   / Task::factorial(4) (factorial@../TestSimpleQtLogger/task.cpp:48)
test.log: [F]  / Task::factorial(5) (factorial@../TestSimpleQtLogger/task.cpp:48)
test.log: [I] Calculate: 5! = 120 (slotRun@../TestSimpleQtLogger/task.cpp:41)
test.log: [F] / Task::slotRun (slotRun@../TestSimpleQtLogger/task.cpp:39)
SimpleQtLogger::~SimpleQtLogger
Marios-iMac:build-TestSimpleQtLogger-Desktop_Qt_5_4_2_clang_64bit-Debug mario$
*/
