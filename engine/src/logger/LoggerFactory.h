#pragma once
#include <memory>

#include "Logger.h"

namespace PlatLogger {

    class LoggerFactory {
    public:
        static std::shared_ptr<Logger> createConsoleLogger(const std::string& name);
        static std::shared_ptr<Logger> createFileLogger(const std::string& name, const std::string& filename);
    };

}
