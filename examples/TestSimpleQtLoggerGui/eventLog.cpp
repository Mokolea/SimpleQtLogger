/*
  Test Simple Logger for Qt

  Mario Ban, 06.2015

*/

#include "eventLog.h"
#include "simpleQtLogger.h"

EventLog::EventLog(QObject *parent)
  : QObject(parent)
{
  L_FUNC("");
  qDebug("EventLog::EventLog"); // TODO comment this
}

EventLog::~EventLog()
{
  L_FUNC("");
  qDebug("EventLog::~EventLog"); // TODO comment this
}

bool EventLog::eventFilter(QObject *obj, QEvent *event)
{
  // L_FUNC("");

  QEvent::Type eventType = event->type();
  QString text = QString("Event type=%1").arg(eventType);
  emit eventInfo(text);

  // standard event processing
  return QObject::eventFilter(obj, event);
}
