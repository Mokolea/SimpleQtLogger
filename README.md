# SimpleQtLogger

Simple rolling file logger for Qt.

Facts:
 - supported sinks:
    - rolling file appender
    - qDebug
 - no configuration file

**TODO...**

Example log-file content:
```
Marios-iMac:Qt mario$ tail -Fn100 testSimpleQtLogger.log
2015-06-12 18:20:18.152 [I] Start logger
2015-06-12 18:20:18.154 [F] \ (Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:19)
2015-06-12 18:20:18.154 [F] / (Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:19)
2015-06-12 18:20:18.154 [F] \ (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:24)
2015-06-12 18:20:18.154 [I] +++ test Logger (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:26)
2015-06-12 18:20:18.154 [!] L_FATAL (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:27)
2015-06-12 18:20:18.154 [E] L_ERROR (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:28)
2015-06-12 18:20:18.154 [W] L_WARN (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:29)
2015-06-12 18:20:18.154 [I] L_INFO (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:30)
2015-06-12 18:20:18.154 [I] --- test Logger (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:32)
2015-06-12 18:20:18.154 [I] ? (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:34)
2015-06-12 18:20:18.154 [I] Trimmed (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:35)
2015-06-12 18:20:18.154 [I] JSON output 1:
{
  "firstName": "Mario"
  "age": 44
} (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:43)
2015-06-12 18:20:18.155 [I] JSON output 2:
{
  "firstName": "Mario"
  "age": 44
} (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:46)
2015-06-12 18:20:18.155 [F] / (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:24)
2015-06-12 18:20:18.255 [F] \ (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:61)
2015-06-12 18:20:18.255 [F] .\ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:18.255 [F] ..\ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:18.255 [F] ...\ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:18.255 [F] ....\ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:18.255 [F] .....\ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:18.255 [F] ...../ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:18.255 [F] ..../ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:18.255 [F] .../ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:18.255 [F] ../ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:18.255 [F] ./ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:70)
2015-06-12 18:20:18.255 [I] Calculate: 6! = 720 (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:63)
2015-06-12 18:20:18.255 [F] / (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:61)
2015-06-12 18:20:25.294 [F] \ (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:54)
2015-06-12 18:20:25.294 [I] Bye bye (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:55)
2015-06-12 18:20:25.294 [F] / (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:54)
Marios-iMac:Qt mario$
```

*GNU General Public License v2.0*

-- Mario
