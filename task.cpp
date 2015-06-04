/*
  Test Simple Logger for Qt

  Mario Ban, 05.2015

*/

#include "task.h"

#include <QtDebug>

// -------------------------------------------------------------------------------------------------

Task::Task(QObject *parent)
  : QObject(parent)
{
  qDebug("Task::Task");
}

void Task::init()
{
  qDebug("Task::init");

  QTimer::singleShot(0, this, SLOT(slotRun()));
}

void Task::slotRun()
{
  qDebug("Task::slotRun");

  emit finished();
}
