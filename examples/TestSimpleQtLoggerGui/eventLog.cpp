/*
  Test Simple Logger for Qt

  Mario Ban, 06.2015
  https://github.com/Mokolea/SimpleQtLogger

  GNU Lesser General Public License v2.1
  Copyright (C) 2015 Mario Ban
*/

#include "eventLog.h"
#include "simpleQtLogger.h"

#include <QMetaObject>
#include <QMetaEnum>

EventLog::EventLog(QObject *parent)
  : QObject(parent)
{
  L_FUNC("");
  // qDebug("EventLog::EventLog");
}

EventLog::~EventLog()
{
  L_FUNC("");
  // qDebug("EventLog::~EventLog");
}

bool EventLog::eventFilter(QObject *obj, QEvent *event)
{
  // L_FUNC("");
  static unsigned int eventCount = 0;
  eventCount++;

  if(obj && event) {
    const QMetaObject* metaObject = obj->metaObject();
    QEvent::Type eventType = event->type();

    if(eventType != QEvent::UpdateRequest && eventType != QEvent::MetaCall && eventType != QEvent::Paint /*&& eventType != QEvent::InputMethodQuery*/) {
      int eventTypeEnumIndex = QEvent::staticMetaObject.indexOfEnumerator("Type");
      QString eventTypeName = QEvent::staticMetaObject.enumerator(eventTypeEnumIndex).valueToKey(eventType);

      QString text = QString("%1: %2 event-type = %3 '%4'").arg(eventCount).arg(metaObject->className()).arg(eventType).arg(eventTypeName);
      emit eventInfo(text);
    }
  }
  // standard event processing
  return QObject::eventFilter(obj, event);
}
