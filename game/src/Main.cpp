#include "spdlog/spdlog.h"

int main() {
    spdlog::set_level(spdlog::level::trace);
    spdlog::warn("This is ultimate {}", "Logging");
    spdlog::error("This is ultimate {}", "Logging");
    spdlog::info("This is ultimate {}", "Logging");
    spdlog::debug("This is ultimate {}", "Logging");
    spdlog::critical("This is ultimate {}", "Logging");
    return 0;
}
