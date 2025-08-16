#include <memory>

#include "logger/SpdlogLogger.hpp"

int main() {
    using namespace PlatLogger;

    // Game/engine only knows about Logger interface
    std::unique_ptr<Logger> logger = std::make_unique<SpdLogger>("Game");

    logger->info("Game started!");
    logger->debug("Loading assets...");
    logger->warn("Low memory warning");
    logger->error("Failed to load texture");
    logger->critical("Fatal error, shutting down!");

    return 0;
}
