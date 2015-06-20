/*
  Test Simple Logger for Qt

  Mario Ban, 05.2015

*/

#include "task.h"
#include "simpleQtLogger.h"

#include <QTimer>
#include <QThread>
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
    "  \"firstName\": \"Mario\",\n"
    "  \"age\": 44\n"
    "}"
  ;
  L_INFO(formattedOutput1);

  QString formattedOutput2 = "{<br>  \"firstName\": \"Mario\",<br>  \"age\": 44<br>}";
  L_INFO(formattedOutput2.prepend("JSON output 2:<br>").replace("<br>", "\n"));

  QTimer::singleShot(1000, this, SLOT(slotRun()));
  QTimer::singleShot(1000, this, SLOT(slotRun()));
  QTimer::singleShot(3000, this, SLOT(slotRun()));
  QTimer::singleShot(6000, this, SLOT(theEnd()));
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
  static unsigned int id = 0;

  startWorkerThread(QString("%1").arg(++id, 2, 10, QLatin1Char('0')));
}

void Task::slotResultReady(const QString &result)
{
  L_FUNC("");
  L_INFO(QString("WorkerThread: %1").arg(result));
}

void Task::startWorkerThread(const QString &id)
{
  L_FUNC(QString("id='%1'").arg(id));

  WorkerThread *workerThread = new WorkerThread(id, this);
  connect(workerThread, SIGNAL(resultReady(const QString&)), this, SLOT(slotResultReady(const QString&)));
  connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
  workerThread->start();
}

// -------------------------------------------------------------------------------------------------

WorkerThread::WorkerThread(const QString &id, QObject *parent)
  : QThread(parent)
  , _id(id)
{
  L_FUNC(QString("_id='%1'").arg(_id));
  qDebug("WorkerThread::WorkerThread"); // TODO comment this
}

WorkerThread::~WorkerThread()
{
  L_FUNC(QString("_id='%1'").arg(_id));
  qDebug("WorkerThread::~WorkerThread"); // TODO comment this
}

void WorkerThread::run() Q_DECL_OVERRIDE
{
  L_FUNC(QString("_id='%1'").arg(_id));
  qDebug("WorkerThread::run"); // TODO comment this

  msleep(500); // [ms]
  QString result = QString("%1: Calculate: 6! = %2").arg(_id).arg(factorial(6));
  L_INFO(result);
  msleep(500); // [ms]

  emit resultReady(result);
}

unsigned int WorkerThread::factorial(unsigned int n)
{
  L_FUNC(QString("n=%1").arg(n));

  if(n > 2) {
    return n * factorial(n-1);
  }
  return n;
}
