# SimpleQtLogger

Simple rolling file logger for C++ applications using the [Qt Framework](http://doc.qt.io).

[![Build Status](https://travis-ci.org/Mokolea/SimpleQtLogger.svg)](https://travis-ci.org/Mokolea/SimpleQtLogger)

Design goals - simple:
 - straightforward usage
 - single source-file
 - no configuration-file

Facts:
 - supported sinks:
    - rolling file appender
    - console, colored (ANSI escape codes)
    - qDebug
 - log-levels, function-log (stack-trace)
 - thread-safe use of log-macros
 - specify log-format
 - log-file encoding: utf-8

**TODO...**

## Log-format
The following TAGs are available and expand to:
 - **\<TS\>** --> Time-stamp, "YYYY-MM-DD HH:MM:SS.SSS"
 - **\<TID\>** --> Thread-Id, 64bit value in hexadecimal
 - **\<TID32\>** --> Thread-Id, 32bit value in hexadecimal
 - **\<LL\>** --> Log-level, one character: '!', 'E', 'W', 'I', 'D' or 'F'
 - **\<TEXT\>** --> The log-message
 - **\<FUNC\>** --> Function-name
 - **\<FILE\>** --> File-name
 - **\<LINE\>** --> Line-number

Using the default log-format `"<TS> [<TID>] [<LL>] <TEXT> (<FUNC>@<FILE>:<LINE>)"` creates log-entries like:
```
2015-10-05 17:27:26.022 [000070000019a000] [I] 03: Calculate: 6! = 720 (run@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:119)
```

Example log-file content:
```
Marios-iMac:Qt mario$ tail -Fn100 testSimpleQtLogger.log
2015-10-05 17:27:22.630 [00007fff7c63d000] [-] Start file-log 'main'
2015-10-05 17:27:22.631 [00007fff7c63d000] [F] \ (Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:22)
2015-10-05 17:27:22.631 [00007fff7c63d000] [F] / (Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:22)
2015-10-05 17:27:22.631 [00007fff7c63d000] [F] \ (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:34)
2015-10-05 17:27:22.631 [00007fff7c63d000] [I] +++ test Logger (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:36)
2015-10-05 17:27:22.631 [00007fff7c63d000] [!] L_FATAL (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:37)
2015-10-05 17:27:22.631 [00007fff7c63d000] [E] L_ERROR (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:38)
2015-10-05 17:27:22.632 [00007fff7c63d000] [W] L_WARN (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:39)
2015-10-05 17:27:22.632 [00007fff7c63d000] [I] L_INFO (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:40)
2015-10-05 17:27:22.632 [00007fff7c63d000] [I] --- test Logger (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:42)
2015-10-05 17:27:22.632 [00007fff7c63d000] [I] ? (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:44)
2015-10-05 17:27:22.632 [00007fff7c63d000] [I] Trimmed (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:45)
2015-10-05 17:27:22.632 [00007fff7c63d000] [I] UTF-8 Unicode text: äöü àéè (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:46)
2015-10-05 17:27:22.632 [00007fff7c63d000] [I] JSON output 1:
{
  "firstName": "Mario",
  "age": 44
} (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:54)
2015-10-05 17:27:22.632 [00007fff7c63d000] [I] JSON output 2:
{
  "firstName": "Mario",
  "age": 44
} (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:57)
2015-10-05 17:27:22.632 [00007fff7c63d000] [F] / (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:34)
2015-10-05 17:27:25.520 [00007fff7c63d000] [F] \ (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:74)
2015-10-05 17:27:25.520 [00007fff7c63d000] [F] .\ id='03' (startWorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:88)
2015-10-05 17:27:25.520 [00007fff7c63d000] [F] ..\ _id='03' (WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:102)
2015-10-05 17:27:25.520 [00007fff7c63d000] [F] ../ _id='03' (WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:102)
2015-10-05 17:27:25.520 [00007fff7c63d000] [F] ./ id='03' (startWorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:88)
2015-10-05 17:27:25.520 [00007fff7c63d000] [F] / (slotRun@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:74)
2015-10-05 17:27:25.520 [000070000019a000] [F] \ _id='03' (run@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:114)
2015-10-05 17:27:26.022 [000070000019a000] [F] .\ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:131)
2015-10-05 17:27:26.022 [000070000019a000] [F] ..\ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:131)
2015-10-05 17:27:26.022 [000070000019a000] [F] ...\ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:131)
2015-10-05 17:27:26.022 [000070000019a000] [F] ....\ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:131)
2015-10-05 17:27:26.022 [000070000019a000] [F] .....\ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:131)
2015-10-05 17:27:26.022 [000070000019a000] [F] ...../ n=2 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:131)
2015-10-05 17:27:26.022 [000070000019a000] [F] ..../ n=3 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:131)
2015-10-05 17:27:26.022 [000070000019a000] [F] .../ n=4 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:131)
2015-10-05 17:27:26.022 [000070000019a000] [F] ../ n=5 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:131)
2015-10-05 17:27:26.022 [000070000019a000] [F] ./ n=6 (factorial@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:131)
2015-10-05 17:27:26.022 [000070000019a000] [I] 03: Calculate: 6! = 720 (run@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:119)
2015-10-05 17:27:26.530 [00007fff7c63d000] [F] \ (slotResultReady@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:82)
2015-10-05 17:27:26.530 [00007fff7c63d000] [I] WorkerThread: 03: Calculate: 6! = 720 (slotResultReady@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:83)
2015-10-05 17:27:26.530 [00007fff7c63d000] [F] / (slotResultReady@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:82)
2015-10-05 17:27:26.530 [000070000019a000] [F] / _id='03' (run@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:114)
2015-10-05 17:27:26.530 [00007fff7c63d000] [F] \ _id='03' (~WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:108)
2015-10-05 17:27:26.530 [00007fff7c63d000] [F] / _id='03' (~WorkerThread@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:108)
2015-10-05 17:27:27.883 [00007fff7c63d000] [-] Current log-file 'main' size=11964 (rotation-size=10240) --> rolling
2015-10-05 17:27:27.898 [00007fff7c63d000] [-] Log-file 'main' rolling done (time elapsed: 15 ms)
2015-10-05 17:27:28.935 [00007fff7c63d000] [F] \ (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:67)
2015-10-05 17:27:28.935 [00007fff7c63d000] [I] Bye bye (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:68)
2015-10-05 17:27:28.936 [00007fff7c63d000] [F] / (theEnd@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:67)
2015-10-05 17:27:28.936 [00007fff7c63d000] [F] \ (~Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:28)
2015-10-05 17:27:28.936 [00007fff7c63d000] [F] / (~Task@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:28)
Marios-iMac:Qt mario$
```

```
Marios-iMac:Qt mario$ tail -Fn100 testSimpleQtLoggerWarn.log
2015-10-05 17:27:22.631 [00007fff7c63d000] [-] Start file-log 'warn'
2015-10-05 17:27:22.631 [00007fff7c63d000] [!] L_FATAL (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:37)
2015-10-05 17:27:22.631 [00007fff7c63d000] [E] L_ERROR (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:38)
2015-10-05 17:27:22.632 [00007fff7c63d000] [W] L_WARN (init@../SimpleQtLogger/examples/TestSimpleQtLogger/task.cpp:39)Marios-iMac:Qt mario$
```

*GNU Lesser General Public License v2.1*

-- Mario
