# SimpleQtLogger

Simple rolling file logger for Qt.

Facts:
 - rolling file appender
 - no configuration file

**TODO...**

Example log-file content:
```
Marios-iMac:Qt mario$ tail -Fn100 testSimpleQtLogger.log
2015-06-07 10:05:37.220 [I] Start logger
2015-06-07 10:05:37.222 [F] \ (Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:19)
2015-06-07 10:05:37.222 [F] / (Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:19)
2015-06-07 10:05:37.222 [F] \ (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:24)
2015-06-07 10:05:37.222 [I] +++ test Logger (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:26)
2015-06-07 10:05:37.222 [!] L_FATAL (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:27)
2015-06-07 10:05:37.222 [E] L_ERROR (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:28)
2015-06-07 10:05:37.222 [W] L_WARN (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:29)
2015-06-07 10:05:37.222 [I] L_INFO (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:30)
2015-06-07 10:05:37.222 [I] --- test Logger (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:32)
2015-06-07 10:05:37.222 [I] ? (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:34)
2015-06-07 10:05:37.222 [I] Trimmed (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:35)
2015-06-07 10:05:37.222 [I] JSON output 1:
{
  "firstName": "Mario"
  "age": 44
} (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:43)
2015-06-07 10:05:37.222 [I] JSON output 2:
{
  "firstName": "Mario"
  "age": 44
} (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:46)
2015-06-07 10:05:37.223 [F] / (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:24)
2015-06-07 10:05:37.323 [F] \ (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:61)
2015-06-07 10:05:37.324 [F] .\ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:37.324 [F] ..\ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:37.324 [F] ...\ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:37.324 [F] ....\ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:37.324 [F] ..../ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:37.324 [F] .../ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:37.324 [F] ../ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:37.324 [F] ./ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-07 10:05:37.324 [I] Calculate: 5! = 120 (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:63)
2015-06-07 10:05:37.324 [F] / (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:61)
2015-06-07 10:05:44.041 [F] \ (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:54)
2015-06-07 10:05:44.041 [I] Bye bye (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:55)
2015-06-07 10:05:44.041 [F] / (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:54)
Marios-iMac:Qt mario$
```

*GNU General Public License v2.0*

-- Mario
