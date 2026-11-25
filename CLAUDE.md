# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project

SimpleQtLogger is a rolling-file logger library for Qt C++ applications. The whole library is a single header/source pair at the repo root: `simpleQtLogger.h` and `simpleQtLogger.cpp`. Design goals are deliberately minimal: straightforward usage, single source file, no configuration file. Users compile the two files directly into their project (moc must run on the header). There is no separate library build.

The big comment block at the top of `simpleQtLogger.h` is the user documentation: usage, restrictions, log-format TAGs, TODO/Done lists, and the "Tested using" list. Keep it in sync with `README.md` when behavior changes: the "Facts" list and the log-format TAG table appear in both. The version is in `SQTL_VERSION_STR` / `SQTL_VERSION` in the header.

## Build and run

The buildable targets are the Qt Test unit tests under `tests/` and the two qmake example apps under `examples/`. Build out-of-source in `tests/build*` or `examples/build*`, which are gitignored:

```sh
# Unit tests (Qt Test, needs Qt >= 5.3): runs in well under a second
mkdir -p tests/build-unit && cd tests/build-unit
qmake CONFIG+=debug ../TestSimpleQtLoggerUnit && make && ./TestSimpleQtLoggerUnit
```

```sh
# Console example: exits by itself after ~6 s
mkdir -p examples/build-console && cd examples/build-console
qmake CONFIG+=debug ../TestSimpleQtLogger && make && ./TestSimpleQtLogger

# GUI example (dialog widget): runs until its window is closed (Quit button or window close), so start it in the background or with a timeout
mkdir -p examples/build-gui && cd examples/build-gui
qmake CONFIG+=debug ../TestSimpleQtLoggerGui && make && ./TestSimpleQtLoggerGui
```

Use `qmake6` (or `qmake -qt=qt6`) to build against Qt 6. Each `.pro` adds `../../simpleQtLogger.cpp` to SOURCES and `../..` to INCLUDEPATH. Only debug builds add `-Wextra` (`QMAKE_CXXFLAGS_DEBUG`), so pass `CONFIG+=debug` when you check for warnings. Recent commits focus on removing compiler warnings, so new code should build warning-free.

Run a single unit test by naming it, e.g. `./TestSimpleQtLoggerUnit file_rolling` (`-functions` lists them). The tests (`tests/TestSimpleQtLoggerUnit/tst_simpleQtLogger.cpp`) create a fresh logger in `init()` and reset all run-time globals. They watch messages through the signal sink (with `Qt::DirectConnection`) and through log-files in a `QTemporaryDir`. They start file rolling without waiting 5 s by calling the private slot `slotCheckLogFileActivity` with `QMetaObject::invokeMethod`. Add a test there for each behavior change or bug fix. The tests need Qt 5.3 or later, but the library itself still has to build with Qt 4.8.

To verify log-file rolling, run the console app three times in a row, as the legacy CI did. It writes `testSimpleQtLogger.log` (role `main`) and `testSimpleQtLoggerWarn.log` (role `warn`) into the current directory with a small 10 KB rotation size and at most 10 rolled files, so `_01.log`, `_02.log`, … files should appear. One run isn't enough: the size is checked only every `CHECK_LOG_FILE_ACTIVITY_INTERVAL` (5000 ms) and a run lasts about 6 s, so each run does about one check and the files roll across runs. Generated `testSimpleQtLogger*log` files are gitignored. Qt Creator shadow-build dirs (`examples/build-TestSimpleQtLogger-Desktop_Qt_…`) may also exist locally; they are gitignored and are not part of the source.

### Linux

- Distro Qt packages provide `qmake6`, or `qmake -qt=qt6` through qtchooser on Debian/Ubuntu. Recorded test platforms include Qt 6.4.2 on Debian 12 and Qt 5.15.3 on Ubuntu 22.04. The legacy CI also ran on Linux.
- The syslog sink writes to journald. Check the examples' messages with e.g. `journalctl -t TestSimpleQtLogger`.

### macOS

- The Qt online installer does not put Qt on `PATH`. Call qmake by its full path, e.g. `~/Qt/<version>/macos/bin/qmake6`.
- The console example builds a plain binary (`CONFIG -= app_bundle`). The GUI example builds an app bundle, so start it as `./TestSimpleQtLoggerGui.app/Contents/MacOS/TestSimpleQtLoggerGui` from the build directory. Its log-file names are relative to the current directory, and `open` starts the app with `/` as its current directory, so the log files can't be created there.
- The syslog sink writes to the unified log through `os_log`, which Console.app and `log` show. FATAL becomes a Fault and ERROR an Error, both stored and shown as errors by default. WARN and NOTE become Default, INFO (plus function-trace and internal messages) becomes Info, and DEBUG becomes Debug. Debug isn't stored, so it shows only live in `log stream --level debug`, not in `log show`.
- Viewing the unified log:
  - **Live, including Debug:** `log stream --level debug --predicate 'process == "TestSimpleQtLogger"'`
  - **Stored messages after a run** (no Debug): `log show --last 5m --info --predicate 'process == "TestSimpleQtLogger"'`
  - **Only FATAL and ERROR:** `log show --last 1h --predicate 'process == "TestSimpleQtLogger" AND messageType IN {"error", "fault"}'`
  - macOS logs its own system messages under the app's process name too. Add `AND senderImagePath ENDSWITH "/TestSimpleQtLogger"` to keep only the logger's messages. If `NAME_LOG_SINK_SYSLOG` is set, filter with `subsystem == "<name>"` instead. For the GUI example, use the process name `TestSimpleQtLoggerGui`.
  - To check the levels in a script, use `--style json` and read the `messageType` field.
- Editor clang diagnostics such as `'QObject' file not found` come from missing Qt include paths in the editor setup, not from the code. Use the qmake build as the source of truth.

`.travis.yml` is legacy (Travis CI, Qt 4) and is not actively used.

## Releasing

Bump `SQTL_VERSION_STR` and `SQTL_VERSION` (`0xMMmmpp`) in `simpleQtLogger.h`, and the `Q_ASSERT_X(SQTL_VERSION >= SQTL_VERSION_CHECK(...))` line in both examples' `main.cpp`. Build the examples with `CONFIG+=debug` so that assert is checked.

Entries in the header's "Tested using" list go newest Qt version first, in the form `Qt <version> <OS> (<compiler>, <arch>)`.

## Compatibility constraints

The code supports Qt 4.8 through Qt 6 at the same time. Version-dependent code is guarded with `#if (QT_VERSION >= QT_VERSION_CHECK(...))`. Examples: regex log-filters (`QRegularExpression`) need Qt ≥ 5.0, and functor-based `connect` (`&Class::slot`) needs Qt ≥ 5.0, with a string-based `SIGNAL()`/`SLOT()` fallback for Qt 4. Preserve these fallbacks and add new guards instead of dropping older Qt support. Syslog support is guarded by `#ifdef SQTL_SYSLOG_AVAILABLE`, which the header defines for `Q_OS_LINUX` and `Q_OS_DARWIN`. Don't use `Q_OS_MACOS`, because it doesn't exist before Qt 5.8. The os_log path (`SQTL_SYSLOG_USE_OSLOG`) is defined only when the macOS deployment target is 10.12 or later (`MAC_OS_X_VERSION_MIN_REQUIRED`). Older macOS targets and iOS fall back to `syslog()`. Code avoids C++11 features (null pointers are `0`, marked `// TODO use C++11 nullptr`; no `auto`). Formatting follows AStyle with 2-space indentation.

## Architecture

- **Singleton `SimpleQtLogger`** (`createInstance(qApp)` / `getInstance()`, which may return NULL) owns all sinks as QObject children. `~SimpleQtLogger` resets the stored instance pointer, so logging after the logger (or its parent) is deleted is a no-op instead of a use-after-free. Keep that behavior.
- **Sinks** derive from `Sink` (a QObject): `SinkFileLog` (rolling file, one per *role*; `"main"` always exists, and more are added with `addSinkFileLog(role)`), `SinkConsoleLog` (ANSI colors), `SinkQDebugLog`, `SinkSignalLog` (re-emits `signalLogMessage` for app consumption via `connectSinkSignalLog`), and `SinkSyslogLog`. Only one instance of each sink type exists, except for file sinks.
- **Syslog sink** (Linux and macOS): `ENABLE_SQTL_LOG_SINK_SYSLOG` defaults to 1 there, and both examples enable it at run time with an empty `NAME_LOG_SINK_SYSLOG`, so messages are tagged with the program name. `openlog()` is called lazily in `SinkSyslogLog::slotLog`, on the first message that passes the syslog sink's checks, and `closelog()` only if it was opened. So the sink doesn't touch an application's own syslog setup while it is disabled. `NAME_LOG_SINK_SYSLOG` and `FACILITY_LOG_SINK_SYSLOG` must be set before that first message. The name is copied into the `_ident` member because `openlog()` keeps the pointer instead of copying the string. On macOS (`SQTL_SYSLOG_USE_OSLOG`), the same lazy step calls `os_log_create()` instead. A non-empty `NAME_LOG_SINK_SYSLOG` becomes the os_log subsystem (category `"SimpleQtLogger"`), an empty one uses `OS_LOG_DEFAULT`, and `FACILITY_LOG_SINK_SYSLOG` has no effect. Messages are logged with `%{public}s` so they aren't redacted as `<private>`. The format and TAG code is shared by both paths, and only the output call and level mapping differ.
- **Dispatch / thread-safety:** `SimpleQtLogger::log()` only stamps the time and thread-id, then `emit signalLog(...)`. Every sink's `slotLog` is connected with `Qt::AutoConnection`, so logging from worker threads is queued to the sinks' (main) thread. This is why `LogLevel` is registered with `qRegisterMetaType`, under both `"LogLevel"` and `"simpleqtlogger::LogLevel"`, because the type names used in signal signatures must match. Shared mutable state, such as per-thread function stack depth, is protected by `_mutex`.
- **Three layers of log-level gating:** a message is logged only if all three allow it:
  1. Compile-time `ENABLE_SQTL_LOG_LEVEL_*` / `ENABLE_SQTL_LOG_SINK_*` macros (overridable via `-D`)
  2. The run-time global `simpleqtlogger::ENABLE_LOG_LEVELS` and `ENABLE_LOG_SINK_*` flags, checked in the macros
  3. Per-sink levels (`setLogLevels_file/console/...`) plus optional per-sink regex filters
- **Macros:** `L_*` take a QString, `LS_*` take a `QTextStream` `<<` expression, and `L_FUNC` / `LS_FUNC` create an RAII `SimpleQtLoggerFunc` that logs function entry/exit (`\` and `/`) with per-thread stack-depth indentation. The destructor calls `logFuncEnd` only if the constructor's `logFuncBegin` incremented the depth, and it decides from the state at construction, not from the current run-time flags. This keeps the depth balanced when `ENABLE_LOG_LEVELS.logLevel_FUNCTION` or `ENABLE_FUNCTION_STACK_TRACE` change while a traced function is running. All macro paths (`L_*`, `LS_*`, and `SimpleQtLoggerFunc`) check `getInstance()` for NULL. Any variable declared inside a macro must start with `_sqtl_`, so it can't shadow a user variable used in the message expression (e.g. `LS_INFO("x=" << s)`).
- **File rolling:** `SinkFileLog` has one single-shot `QTimer` member (`_activityCheckTimer`) that is re-armed after every check, every `CHECK_LOG_FILE_ACTIVITY_INTERVAL` ms. Repeated `setLogFileName()` calls restart it rather than adding timers. If anything was written since the last check, it checks the on-disk size. There is no explicit `flush()`, but each message's `QTextStream` hands its text to the file as it goes out of scope, so lines reach the file right away. A log can therefore grow well past the rotation size before the next check. When the size exceeds the rotation size, it shifts `name.log` → `name_01.log` → `name_02.log` … up to the configured count. Log-file names must end in `.log`. If opening the file fails, either at first or after rolling, the sink retries on every activity check, warns once, and writes an internal "re-opened" message when it succeeds. Messages logged in between are dropped. Rolled names come from `rolledLogFileName()`, which inserts `_NN` only before the trailing `.log`; never use `QString::replace` on the path, since `.log` can appear in directory names.
- **Log format** is a template string with `<TS>`, `<TID>`, `<TID32>`, `<LL>`, `<TEXT>`, `<FUNC>`, `<FILE>` and `<LINE>` TAGs. Each sink has a normal format and an "internal" format used for the logger's own messages (level `-`).
