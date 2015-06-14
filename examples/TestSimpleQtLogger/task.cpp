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
  L_FUNC("");
  qDebug("Task::Task"); // TODO comment this
}

Task::~Task()
{
  L_FUNC("");
  qDebug("Task::~Task"); // TODO comment this
}

void Task::init()
{
  L_FUNC("");

  L_INFO("+++ test Logger");
  L_FATAL("L_FATAL");
  L_ERROR("L_ERROR");
  L_WARN("L_WARN");
  L_INFO("L_INFO");
  L_DEBUG("L_DEBUG");
  L_INFO("--- test Logger");

  L_INFO(QString()); // --> "?"
  L_INFO(" \n Trimmed \n\n"); // --> whitespace removed from start and end

  QString formattedOutput1 = "JSON output 1:\n"
    "{\n"
    "  \"firstName\": \"Mario\"\n"
    "  \"age\": 44\n"
    "}"
  ;
  L_INFO(formattedOutput1);

  QString formattedOutput2 = "{<br>  \"firstName\": \"Mario\"<br>  \"age\": 44<br>}";
  L_INFO(formattedOutput2.prepend("JSON output 2:<br>").replace("<br>", "\n"));

  QTimer::singleShot(100, this, SLOT(slotRun()));
  QTimer::singleShot(7000, this, SLOT(theEnd()));
}

void Task::theEnd()
{
  L_FUNC("");
  L_INFO("Bye bye");
  emit finished();
}

void Task::slotRun()
{
  L_FUNC("");

  L_INFO(QString("Calculate: 6! = %1").arg(factorial(6)));

  QTimer::singleShot(3000, this, SLOT(slotRun()));
}

unsigned int Task::factorial(unsigned int n) const
{
  L_FUNC(QString("n=%1").arg(n));

  if(n > 2) {
    return n * factorial(n-1);
  }
  return n;
}
