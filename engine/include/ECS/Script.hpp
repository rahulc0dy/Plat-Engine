#pragma once
#include <string>

struct Script {
    std::string name;
    // You can extend this with script data, function pointers, etc.
    Script(const std::string& name = "") : name(name) {}
};
