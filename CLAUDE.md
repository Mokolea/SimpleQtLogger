# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project

SimpleQtLogger is a rolling-file logger library for Qt C++ applications. The whole library is a single header/source pair at the repo root: `simpleQtLogger.h` and `simpleQtLogger.cpp`. Design goals are deliberately minimal: straightforward usage, single source file, no configuration file. Users compile the two files directly into their project (moc must run on the header). There is no separate library build.

The big comment block at the top of `simpleQtLogger.h` is the user documentation: usage, restrictions, log-format TAGs, TODO/Done lists, and the "Tested using" list. Keep it (and `README.md`) in sync when behavior changes. The version is in `SQTL_VERSION_STR` / `SQTL_VERSION` in the header.

## Build and run

The only buildable targets are the two qmake example apps under `examples/`, and they double as the test suite (there are no unit tests). Build out-of-source in `examples/build*`, which is gitignored:

```sh
# Console example (also what CI runs, three times, to exercise log-file rolling)
mkdir -p examples/build-console && cd examples/build-console
qmake ../TestSimpleQtLogger && make && ./TestSimpleQtLogger

# GUI example (dialog widget)
mkdir -p examples/build-gui && cd examples/build-gui
qmake ../TestSimpleQtLoggerGui && make && ./TestSimpleQtLoggerGui
```

Use `qmake6` (or `qmake -qt=qt6`) to build against Qt 6. Generated `testSimpleQtLogger*log` files are gitignored. Each `.pro` adds `../../simpleQtLogger.cpp` to SOURCES and `../..` to INCLUDEPATH, and debug builds use `-Wextra`. Recent commits focus on removing compiler warnings, so new code should build warning-free.

`.travis.yml` is legacy (Travis CI, Qt 4) and is not actively used.

## Compatibility constraints

The code supports Qt 4.8 through Qt 6 at the same time. Version-dependent code is guarded with `#if (QT_VERSION >= QT_VERSION_CHECK(...))`. Examples: regex log-filters (`QRegularExpression`) need Qt ≥ 5.0, and functor-based `QTimer::singleShot` needs Qt ≥ 5.4, with a string-based `SLOT()` fallback for older versions. Preserve these fallbacks and add new guards instead of dropping older Qt support. Syslog support is `#ifdef Q_OS_LINUX` only. Code avoids C++11 features (null pointers are `0`, marked `// TODO use C++11 nullptr`; no `auto`). Formatting follows AStyle with 2-space indentation.

## Architecture

- **Singleton `SimpleQtLogger`** (`createInstance(qApp)` / `getInstance()`, which may return NULL) owns all sinks as QObject children.
- **Sinks** derive from `Sink` (a QObject): `SinkFileLog` (rolling file, one per *role*; `"main"` always exists, and more are added with `addSinkFileLog(role)`), `SinkConsoleLog` (ANSI colors), `SinkQDebugLog`, `SinkSignalLog` (re-emits `signalLogMessage` for app consumption via `connectSinkSignalLog`), and `SinkSyslogLog`. Only one instance of each sink type exists, except for file sinks.
- **Dispatch / thread-safety:** `SimpleQtLogger::log()` only stamps the time and thread-id, then `emit signalLog(...)`. Every sink's `slotLog` is connected with `Qt::AutoConnection`, so logging from worker threads is queued to the sinks' (main) thread. This is why `LogLevel` is registered with `qRegisterMetaType`. Shared mutable state, such as per-thread function stack depth, is protected by `_mutex`.
- **Three layers of log-level gating:** a message is logged only if all three allow it:
  1. Compile-time `ENABLE_SQTL_LOG_LEVEL_*` / `ENABLE_SQTL_LOG_SINK_*` macros (overridable via `-D`)
  2. The run-time global `simpleqtlogger::ENABLE_LOG_LEVELS` and `ENABLE_LOG_SINK_*` flags, checked in the macros
  3. Per-sink levels (`setLogLevels_file/console/...`) plus optional per-sink regex filters
- **Macros:** `L_*` take a QString, `LS_*` take a `QTextStream` `<<` expression, and `L_FUNC` / `LS_FUNC` create an RAII `SimpleQtLoggerFunc` that logs function entry/exit (`\` and `/`) with per-thread stack-depth indentation.
- **File rolling:** `SinkFileLog` re-arms a `QTimer::singleShot` every `CHECK_LOG_FILE_ACTIVITY_INTERVAL` ms to flush and check the size. When the size exceeds the rotation size, it shifts `name.log` → `name_01.log` → `name_02.log` … up to the configured count. Log-file names must end in `.log`.
- **Log format** is a template string with `<TS>`, `<TID>`, `<TID32>`, `<LL>`, `<TEXT>`, `<FUNC>`, `<FILE>` and `<LINE>` TAGs. Each sink has a normal format and an "internal" format used for the logger's own messages (level `-`).
