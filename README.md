# SimpleQtLogger

Simple rolling file logger for Qt.

Facts:
 - supported sinks:
    - rolling file appender
    - qDebug
 - no configuration file
 - thread-safe use of log-macros
 - single source-file
 - specify log-format

## Log-format
The following TAGs are available and expand to:
 - **\<TS\>** --> "YYYY-MM-DD HH:MM:SS.SSS"
 - **\<TID\>** --> Thread-Id, 64bit value in hexadecimal
 - **\<LL\>** --> Log-level, one character: '!', 'E', 'W', 'I', 'D' or 'F'
 - **\<TEXT\>** --> The log-message
 - **\<FUNC\>** --> Function-name
 - **\<FILE\>** --> File-name
 - **\<LINE\>** --> Line-number

Using the default log-format `"<TS> [<TID>] [<LL>] <TEXT> (<FUNC>@<FILE>:<LINE>)"` creates log-entries like:
```
2015-06-20 19:06:03.269 [0000000108bdc000] [I] 03: Calculate: 6! = 720 (run@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:116)
```

**TODO...**

Example log-file content:
```
Marios-iMac:Qt mario$ tail -Fn100 testSimpleQtLogger.log
2015-06-20 19:05:59.614 [00007fff7d752300] [I] Start file-log
2015-06-20 19:05:59.616 [00007fff7d752300] [F] \ (Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:20)
2015-06-20 19:05:59.617 [00007fff7d752300] [F] / (Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:20)
2015-06-20 19:05:59.617 [00007fff7d752300] [F] \ (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:32)
2015-06-20 19:05:59.617 [00007fff7d752300] [I] +++ test Logger (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:34)
2015-06-20 19:05:59.617 [00007fff7d752300] [!] L_FATAL (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:35)
2015-06-20 19:05:59.617 [00007fff7d752300] [E] L_ERROR (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:36)
2015-06-20 19:05:59.617 [00007fff7d752300] [W] L_WARN (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:37)
2015-06-20 19:05:59.617 [00007fff7d752300] [I] L_INFO (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:38)
2015-06-20 19:05:59.617 [00007fff7d752300] [I] --- test Logger (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:40)
2015-06-20 19:05:59.617 [00007fff7d752300] [I] ? (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:42)
2015-06-20 19:05:59.617 [00007fff7d752300] [I] Trimmed (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:43)
2015-06-20 19:05:59.617 [00007fff7d752300] [I] JSON output 1:
{
  "firstName": "Mario",
  "age": 44
} (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:51)
2015-06-20 19:05:59.617 [00007fff7d752300] [I] JSON output 2:
{
  "firstName": "Mario",
  "age": 44
} (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:54)
2015-06-20 19:05:59.617 [00007fff7d752300] [F] / (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:32)
2015-06-20 19:06:02.767 [00007fff7d752300] [F] \ (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:71)
2015-06-20 19:06:02.767 [00007fff7d752300] [F] .\ id='03' (startWorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:85)
2015-06-20 19:06:02.768 [00007fff7d752300] [F] ..\ _id='03' (WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:99)
2015-06-20 19:06:02.768 [00007fff7d752300] [F] ../ _id='03' (WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:99)
2015-06-20 19:06:02.768 [00007fff7d752300] [F] ./ id='03' (startWorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:85)
2015-06-20 19:06:02.768 [00007fff7d752300] [F] / (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:71)
2015-06-20 19:06:02.768 [0000000108bdc000] [F] \ _id='03' (run@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:111)
2015-06-20 19:06:03.269 [0000000108bdc000] [F] .\ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:03.269 [0000000108bdc000] [F] ..\ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:03.269 [0000000108bdc000] [F] ...\ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:03.269 [0000000108bdc000] [F] ....\ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:03.269 [0000000108bdc000] [F] .....\ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:03.269 [0000000108bdc000] [F] ...../ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:03.269 [0000000108bdc000] [F] ..../ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:03.269 [0000000108bdc000] [F] .../ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:03.269 [0000000108bdc000] [F] ../ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:03.269 [0000000108bdc000] [F] ./ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:124)
2015-06-20 19:06:03.269 [0000000108bdc000] [I] 03: Calculate: 6! = 720 (run@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:116)
2015-06-20 19:06:03.774 [00007fff7d752300] [F] \ (slotResultReady@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:79)
2015-06-20 19:06:03.774 [00007fff7d752300] [I] WorkerThread: 03: Calculate: 6! = 720 (slotResultReady@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:80)
2015-06-20 19:06:03.774 [00007fff7d752300] [F] / (slotResultReady@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:79)
2015-06-20 19:06:03.774 [0000000108bdc000] [F] / _id='03' (run@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:111)
2015-06-20 19:06:03.774 [00007fff7d752300] [F] \ _id='03' (~WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:105)
2015-06-20 19:06:03.774 [00007fff7d752300] [F] / _id='03' (~WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:105)
2015-06-20 19:06:04.775 [00007fff7d752300] [I] Current log-file size=11797 (rotation-size=10240) --> rolling
2015-06-20 19:06:04.776 [00007fff7d752300] [I] Log-file rolling done (time elapsed: 2 ms)
2015-06-20 19:06:04.777 [00007fff7d752300] [F] \ (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:64)
2015-06-20 19:06:04.777 [00007fff7d752300] [I] Bye bye (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:65)
2015-06-20 19:06:04.777 [00007fff7d752300] [F] / (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:64)
2015-06-20 19:06:04.777 [00007fff7d752300] [F] \ (~Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:26)
2015-06-20 19:06:04.777 [00007fff7d752300] [F] / (~Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:26)
Marios-iMac:Qt mario$
```

*GNU General Public License v2.0*

-- Mario
