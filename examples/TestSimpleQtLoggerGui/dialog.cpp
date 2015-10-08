/*
  Test Simple Logger for Qt

  Mario Ban, 06.2015

  GNU Lesser General Public License v2.1
  Copyright (C) 2015 Mario Ban
*/

#include "dialog.h"
#include "ui_dialog.h"
#include "simpleQtLogger.h"
#include "eventLog.h"

Dialog::Dialog(QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::Dialog)
{
  L_FUNC("");
  qDebug("Dialog::Dialog"); // TODO comment this
  ui->setupUi(this);

  EventLog *eventLog = new EventLog(this);
  QObject::connect(eventLog, SIGNAL(eventInfo(const QString&)), this, SLOT(eventInfo(const QString&)), Qt::QueuedConnection); // Qt::QueuedConnection: Qt 5.4.x Debian
  installEventFilter(eventLog);
}

Dialog::~Dialog()
{
  L_FUNC("");
  qDebug("Dialog::~Dialog"); // TODO comment this
  delete ui;
}

void Dialog::on_pushButtonQuit_clicked()
{
  L_FUNC("");
  L_INFO("Bye bye");
  close();
}

void Dialog::eventInfo(const QString& text)
{
  // L_FUNC("");
  ui->textBrowserLog->append(text); // .toHtmlEscaped(), Qt 5.0
  L_INFO(text);
}
