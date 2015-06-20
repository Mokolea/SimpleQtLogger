# SimpleQtLogger

Simple rolling file logger for Qt.

Facts:
 - supported sinks:
    - rolling file appender
    - qDebug
 - no configuration file
 - thread-safe use of log-macros

**TODO...**

Example log-file content:
```
Marios-iMac:Qt mario$ tail -Fn100 testSimpleQtLogger.log
2015-06-14 11:27:02.067 [I] Start logger
2015-06-14 11:27:02.069 [F] \ (Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:19)
2015-06-14 11:27:02.069 [F] / (Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:19)
2015-06-14 11:27:02.069 [F] \ (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:31)
2015-06-14 11:27:02.069 [I] +++ test Logger (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:33)
2015-06-14 11:27:02.069 [!] L_FATAL (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:34)
2015-06-14 11:27:02.069 [E] L_ERROR (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:35)
2015-06-14 11:27:02.069 [W] L_WARN (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:36)
2015-06-14 11:27:02.069 [I] L_INFO (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:37)
2015-06-14 11:27:02.069 [I] --- test Logger (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:39)
2015-06-14 11:27:02.069 [I] ? (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:41)
2015-06-14 11:27:02.070 [I] Trimmed (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:42)
2015-06-14 11:27:02.070 [I] JSON output 1:
{
  "firstName": "Mario",
  "age": 44
} (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:50)
2015-06-14 11:27:02.070 [I] JSON output 2:
{
  "firstName": "Mario",
  "age": 44
} (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:53)
2015-06-14 11:27:02.070 [F] / (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:31)
2015-06-14 11:27:02.170 [F] \ (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:68)
2015-06-14 11:27:02.170 [F] .\ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:02.170 [F] ..\ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:02.170 [F] ...\ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:02.170 [F] ....\ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:02.170 [F] .....\ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:02.170 [F] ...../ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:02.170 [F] ..../ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:02.170 [F] .../ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:02.170 [F] ../ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:02.170 [F] ./ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:77)
2015-06-14 11:27:02.170 [I] Calculate: 6! = 720 (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-14 11:27:02.170 [F] / (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:68)
2015-06-14 11:27:08.723 [F] \ (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:61)
2015-06-14 11:27:08.723 [I] Bye bye (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:62)
2015-06-14 11:27:08.723 [F] / (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:61)
2015-06-14 11:27:08.723 [F] \ (~Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:25)
2015-06-14 11:27:08.723 [F] / (~Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:25)
Marios-iMac:Qt mario$
```

*GNU General Public License v2.0*

-- Mario
