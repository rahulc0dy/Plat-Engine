#pragma once
#include <string>

namespace PlatLogger {

    enum class LogLevel {
        Trace,
        Debug,
        Info,
        Warn,
        Error,
        Critical,
        Off
    };

    class Logger {
    public:
        virtual ~Logger() = default;

        virtual void log(LogLevel level, const std::string& msg) = 0;

        void trace(const std::string& msg) { log(LogLevel::Trace, msg); }
        void debug(const std::string& msg) { log(LogLevel::Debug, msg); }
        void info(const std::string& msg)  { log(LogLevel::Info, msg); }
        void warn(const std::string& msg)  { log(LogLevel::Warn, msg); }
        void error(const std::string& msg) { log(LogLevel::Error, msg); }
        void critical(const std::string& msg) { log(LogLevel::Critical, msg); }
    };

}
