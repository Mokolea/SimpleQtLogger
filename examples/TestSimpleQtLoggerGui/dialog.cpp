/*
  Test Simple Logger for Qt

  Mario Ban, 06.2015
  https://github.com/Mokolea/SimpleQtLogger

  GNU Lesser General Public License v2.1
  Copyright (C) 2015 Mario Ban
*/

#include "dialog.h"
#include "ui_dialog.h"
#include "simpleQtLogger.h"
#include "eventLog.h"

#include <QMessageBox>

Dialog::Dialog(QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::Dialog)
{
  L_FUNC("");
  // qDebug("Dialog::Dialog");
  ui->setupUi(this);

  EventLog *eventLog = new EventLog(this);
  QObject::connect(eventLog, SIGNAL(eventInfo(const QString&)), this, SLOT(eventInfo(const QString&)), Qt::QueuedConnection); // Qt::QueuedConnection: Qt 5.4.x Debian
  installEventFilter(eventLog);

  L_INFO("+++ test Logger");
  L_FATAL("L_FATAL");
  L_ERROR("L_ERROR");
  L_WARN("L_WARN");
  L_NOTE("L_NOTE");
  L_INFO("L_INFO");
  L_DEBUG("L_DEBUG");
  L_INFO("--- test Logger");

  L_NOTE("Start");
}

Dialog::~Dialog()
{
  L_FUNC("");
  // qDebug("Dialog::~Dialog");
  delete ui;
}

void Dialog::on_pushButtonAboutQt_clicked()
{
  L_FUNC("");
  QMessageBox::aboutQt(this);
}

void Dialog::on_pushButtonQuit_clicked()
{
  L_FUNC("");
  L_NOTE("Bye bye");
  close();
}

void Dialog::eventInfo(const QString& text)
{
  // L_FUNC("");
  ui->textBrowserLog->append(text); // .toHtmlEscaped(), Qt 5.0
  L_INFO(text);
}
