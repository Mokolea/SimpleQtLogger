/*
  Test Simple Logger for Qt

  Mario Ban, 06.2015

*/

#ifndef _EVENTLOG_H
#define _EVENTLOG_H

#include <QObject>
#include <QEvent>

class EventLog : public QObject
{
  Q_OBJECT

public:
  explicit EventLog(QObject *parent);
  ~EventLog();

protected:
  bool eventFilter(QObject *obj, QEvent *event);

signals:
  void eventInfo(const QString& text);

};

#endif // _EVENTLOG_H
