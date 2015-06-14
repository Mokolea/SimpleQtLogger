/*
  Test Simple Logger for Qt

  Mario Ban, 06.2015

*/

#ifndef _DIALOG_H
#define _DIALOG_H

#include <QDialog>

namespace Ui {
  class Dialog;
}

class Dialog : public QDialog
{
  Q_OBJECT

public:
  explicit Dialog(QWidget *parent = 0);
  ~Dialog();

private slots:
  void on_pushButtonQuit_clicked();
  void eventInfo(const QString& text);

private:
  Ui::Dialog *ui;

};

#endif // _DIALOG_H
