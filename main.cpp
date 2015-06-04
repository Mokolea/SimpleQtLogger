/*
  Test Simple Logger for Qt

  Mario Ban, 05.2015

*/

#include <QCoreApplication>
#include "task.h"

#include "../SimpleQtLogger/SimpleQtLogger.h"
SimpleQtLogger simpleQtLogger_;

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  Task *task = new Task(&a);
  QObject::connect(task, SIGNAL(finished()), &a, SLOT(quit()));
  QTimer::singleShot(0, task, SLOT(init()));

  return a.exec();
}
