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

  simpleQtLogger_.setLogFileName("testSimpleQtLogger.log", 10000, 10); // TODO test
  SQT_LOG_ENABLE_FUNCTION = true;

  Task *task = new Task(&a);
  QObject::connect(task, SIGNAL(finished()), &a, SLOT(quit()));
  QTimer::singleShot(0, task, SLOT(init()));

  return a.exec();
}
