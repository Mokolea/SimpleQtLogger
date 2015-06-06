/*
  Test Simple Logger for Qt

  Mario Ban, 05.2015

*/

#include "task.h"
#include "simpleQtLogger.h"

#include <QTimer>
#include <QtDebug>

// -------------------------------------------------------------------------------------------------

Task::Task(QObject *parent)
  : QObject(parent)
{
  LogFunction("");
}

void Task::init()
{
  LogFunction("");

  LogInfo("+++ test Logger");
  LogFatal("LogFatal");
  LogError("LogError");
  LogWarning("LogWarning");
  LogInfo("LogInfo");
  LogDebug("LogDebug");
  LogInfo("--- test Logger");

  QTimer::singleShot(100, this, SLOT(slotRun()));
  QTimer::singleShot(7000, this, SLOT(theEnd()));
}

void Task::theEnd()
{
  LogFunction("");
  LogInfo("Bye bye");
  emit finished();
}

void Task::slotRun()
{
  LogFunction("");

  LogInfo(QString("Calculate: 5! = %1").arg(factorial(5)));

  QTimer::singleShot(3000, this, SLOT(slotRun()));
}

unsigned int Task::factorial(unsigned int n) const
{
  LogFunction(QString("n=%1").arg(n));

  if(n > 2) {
    return n * factorial(n-1);
  }
  return n;
}
