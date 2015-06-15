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

/*
Marios-iMac:Qt mario$ ./build-TestSimpleQtLoggerGui-Desktop_Qt_5_4_2_clang_64bit-Debug/TestSimpleQtLoggerGui.app/Contents/MacOS/TestSimpleQtLoggerGui
SimpleQtLogger::SimpleQtLogger
SimpleQtLogger::setLogFileName
Current log-file: "/Users/mario/Documents/Qt/testSimpleQtLoggerGui.log"
Dialog::Dialog
EventLog::EventLog
Dialog::~Dialog
EventLog::~EventLog
SimpleQtLogger::~SimpleQtLogger
Marios-iMac:Qt mario$

Marios-iMac:Qt mario$ tail -Fn100 testSimpleQtLoggerGui.log
2015-06-15 10:24:23.022 [I] Start logger
2015-06-15 10:24:23.022 [F] \ (Dialog@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:17)
2015-06-15 10:24:23.190 [F] .\ (EventLog@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/eventLog.cpp:17)
2015-06-15 10:24:23.190 [F] ./ (EventLog@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/eventLog.cpp:17)
2015-06-15 10:24:23.190 [F] / (Dialog@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:17)
2015-06-15 10:24:23.227 [I] 1: Dialog event-type = 203 'WinIdChange' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:23.227 [I] 2: Dialog event-type = 75 'Polish' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:23.227 [I] 3: Dialog event-type = 69 'ChildPolished' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:23.227 [I] 4: Dialog event-type = 69 'ChildPolished' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:23.231 [I] 5: Dialog event-type = 13 'Move' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:23.231 [I] 6: Dialog event-type = 14 'Resize' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:23.231 [I] 7: Dialog event-type = 17 'Show' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:23.232 [I] 8: Dialog event-type = 12 'Paint' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:23.249 [I] 9: Dialog event-type = 26 'ShowToParent' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:23.249 [I] 10: Dialog event-type = 8 'FocusIn' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:23.291 [I] 11: Dialog event-type = 74 'PolishRequest' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:23.291 [I] 12: Dialog event-type = 76 'LayoutRequest' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:23.291 [I] 13: Dialog event-type = 78 'UpdateLater' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:23.296 [I] 15: Dialog event-type = 12 'Paint' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:23.302 [I] 16: Dialog event-type = 24 'WindowActivate' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:23.302 [I] 17: Dialog event-type = 99 'ActivationChange' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:23.321 [I] 18: Dialog event-type = 76 'LayoutRequest' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:23.324 [I] 20: Dialog event-type = 12 'Paint' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:23.325 [I] 21: Dialog event-type = 12 'Paint' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:29.158 [I] 23: Dialog event-type = 51 'ShortcutOverride' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:29.158 [I] 24: Dialog event-type = 51 'ShortcutOverride' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:29.158 [I] 25: Dialog event-type = 6 'KeyPress' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:29.506 [I] 27: Dialog event-type = 51 'ShortcutOverride' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:29.506 [I] 28: Dialog event-type = 51 'ShortcutOverride' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:29.506 [I] 29: Dialog event-type = 6 'KeyPress' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:39.420 [I] 31: Dialog event-type = 7 'KeyRelease' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:39.420 [I] 32: Dialog event-type = 7 'KeyRelease' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:43.238 [I] 34: Dialog event-type = 10 'Enter' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:43.742 [I] 36: Dialog event-type = 11 'Leave' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:44.264 [I] 40: Dialog event-type = 10 'Enter' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:44.692 [I] 44: Dialog event-type = 12 'Paint' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:44.759 [I] 48: Dialog event-type = 12 'Paint' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:44.759 [F] \ (on_pushButtonQuit_clicked@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:35)
2015-06-15 10:24:44.759 [I] Bye bye (on_pushButtonQuit_clicked@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:36)
2015-06-15 10:24:44.759 [I] 49: Dialog event-type = 19 'Close' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:44.760 [I] 50: Dialog event-type = 25 'WindowDeactivate' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:44.760 [I] 51: Dialog event-type = 99 'ActivationChange' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:44.761 [I] 52: Dialog event-type = 18 'Hide' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:44.762 [I] 53: Dialog event-type = 27 'HideToParent' (eventInfo@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:44)
2015-06-15 10:24:44.762 [F] / (on_pushButtonQuit_clicked@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:35)
2015-06-15 10:24:44.765 [F] \ (~Dialog@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:28)
2015-06-15 10:24:44.765 [F] / (~Dialog@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/dialog.cpp:28)
2015-06-15 10:24:44.765 [F] \ (~EventLog@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/eventLog.cpp:23)
2015-06-15 10:24:44.765 [F] / (~EventLog@../SimpleQtLogger/examples/TestSimpleQtLoggerGui/eventLog.cpp:23)
Marios-iMac:Qt mario$
*/
