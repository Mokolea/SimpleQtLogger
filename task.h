/*
  Test Simple Logger for Qt

  Mario Ban, 05.2015

*/

#ifndef _TASK_H
#define _TASK_H

#include <QObject>

// -------------------------------------------------------------------------------------------------

class Task : public QObject
{
  Q_OBJECT
public:
  explicit Task(QObject *parent = 0);

signals:
  void finished();

public slots:
  void init();
  void slotRun();

private:
  unsigned int factorial(unsigned int n);

};

#endif // _TASK_H
