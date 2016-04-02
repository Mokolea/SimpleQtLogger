/*
  Test Simple Logger for Qt

  Mario Ban, 06.2015
  https://github.com/Mokolea/SimpleQtLogger

  GNU Lesser General Public License v2.1
  Copyright (C) 2015 Mario Ban
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
  explicit Dialog(QWidget *parent);
  ~Dialog();

private slots:
  void on_pushButtonAboutQt_clicked();
  void on_pushButtonQuit_clicked();
  void eventInfo(const QString& text);

private:
  Ui::Dialog *ui;

};

#endif // _DIALOG_H

/*
Marios-iMac:Qt mario$ ./build-TestSimpleQtLoggerGui-Desktop_Qt_5_5_0_clang_64bit-Debug/TestSimpleQtLoggerGui.app/Contents/MacOS/TestSimpleQtLoggerGui
SimpleQtLogger::SimpleQtLogger
Current log-file: "/Users/mario/Documents/Qt/testSimpleQtLoggerGui.log" role "main"
Current log-file: "/Users/mario/Documents/Qt/testSimpleQtLoggerGuiWarn.log" role "warn"
Dialog::Dialog
EventLog::EventLog
Dialog::~Dialog
EventLog::~EventLog
SimpleQtLogger::~SimpleQtLogger
Marios-iMac:Qt mario$

Marios-iMac:Qt mario$ tail -Fn100 testSimpleQtLoggerGui.log
2015-10-23 18:45:09.995 [-] Start file-log 'main'
2015-10-23 18:45:10.028 [F] \ (Dialog@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:20)
2015-10-23 18:45:10.401 [F] .\ (EventLog@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/eventLog.cpp:20)
2015-10-23 18:45:10.402 [F] ./ (EventLog@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/eventLog.cpp:20)
2015-10-23 18:45:10.402 [F] / (Dialog@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:20)
2015-10-23 18:45:10.863 [I] 1: Dialog event-type = 203 'WinIdChange' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:10.863 [I] 2: Dialog event-type = 75 'Polish' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:10.863 [I] 3: Dialog event-type = 69 'ChildPolished' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:10.863 [I] 4: Dialog event-type = 69 'ChildPolished' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:10.864 [I] 5: Dialog event-type = 13 'Move' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:10.864 [I] 6: Dialog event-type = 14 'Resize' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:10.864 [I] 7: Dialog event-type = 17 'Show' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:10.864 [I] 8: Dialog event-type = 13 'Move' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:10.864 [I] 9: Dialog event-type = 12 'Paint' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:10.865 [I] 10: Dialog event-type = 26 'ShowToParent' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:10.865 [I] 11: Dialog event-type = 8 'FocusIn' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:10.999 [I] 12: Dialog event-type = 74 'PolishRequest' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:10.999 [I] 13: Dialog event-type = 76 'LayoutRequest' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:10.999 [I] 22: Dialog event-type = 78 'UpdateLater' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:11.000 [I] 27: Dialog event-type = 12 'Paint' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:11.000 [I] 28: Dialog event-type = 24 'WindowActivate' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:11.000 [I] 29: Dialog event-type = 99 'ActivationChange' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:11.041 [I] 32: Dialog event-type = 76 'LayoutRequest' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:11.041 [I] 38: Dialog event-type = 12 'Paint' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:11.041 [I] 39: Dialog event-type = 12 'Paint' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:11.063 [I] 44: Dialog event-type = 10 'Enter' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:12.483 [I] 47: Dialog event-type = 11 'Leave' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:14.964 [I] 50: Dialog event-type = 10 'Enter' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:16.852 [I] 53: Dialog event-type = 110 'ToolTip' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:20.662 [I] 57: Dialog event-type = 12 'Paint' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:20.830 [F] \ (on_pushButtonQuit_clicked@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:38)
2015-10-23 18:45:20.830 [I] Bye bye (on_pushButtonQuit_clicked@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:39)
2015-10-23 18:45:20.832 [F] / (on_pushButtonQuit_clicked@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:38)
2015-10-23 18:45:20.835 [I] 61: Dialog event-type = 12 'Paint' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:20.835 [I] 62: Dialog event-type = 19 'Close' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:20.836 [I] 63: Dialog event-type = 25 'WindowDeactivate' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:20.836 [I] 64: Dialog event-type = 99 'ActivationChange' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:20.836 [I] 65: Dialog event-type = 18 'Hide' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:20.836 [I] 66: Dialog event-type = 27 'HideToParent' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:47)
2015-10-23 18:45:20.837 [F] \ (~Dialog@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:31)
2015-10-23 18:45:20.837 [F] / (~Dialog@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:31)
2015-10-23 18:45:20.837 [F] \ (~EventLog@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/eventLog.cpp:26)
2015-10-23 18:45:20.837 [F] / (~EventLog@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/eventLog.cpp:26)
Marios-iMac:Qt mario$

Marios-iMac:Qt mario$ tail -Fn100 testSimpleQtLoggerGuiWarn.log
2015-10-23 18:45:09.995 [-] Start file-log 'warn'
Marios-iMac:Qt mario$
*/
