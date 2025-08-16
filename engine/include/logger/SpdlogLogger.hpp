#pragma once

#include "Logger.hpp"
#include "spdlog/spdlog.h"
#include <memory>

namespace PlatLogger {

    class SpdLogger : public Logger {
    public:
        SpdLogger(const std::string& name = "PlatEngine") {
            m_logger = spdlog::stdout_color_mt(name);
        }

        void log(LogLevel level, const std::string& message) override {
            switch (level) {
                case LogLevel::Trace:    m_logger->trace(message); break;
                case LogLevel::Debug:    m_logger->debug(message); break;
                case LogLevel::Info:     m_logger->info(message); break;
                case LogLevel::Warn:     m_logger->warn(message); break;
                case LogLevel::Error:    m_logger->error(message); break;
                case LogLevel::Critical: m_logger->critical(message); break;
            }
        }

        void trace(const std::string& message) override { m_logger->trace(message); }
        void debug(const std::string& message) override { m_logger->debug(message); }
        void info(const std::string& message) override { m_logger->info(message); }
        void warn(const std::string& message) override { m_logger->warn(message); }
        void error(const std::string& message) override { m_logger->error(message); }
        void critical(const std::string& message) override { m_logger->critical(message); }

    private:
        std::shared_ptr<spdlog::logger> m_logger;
    };

} // namespace PlatLogger
