#pragma once
#include <string>
#include <any>

struct Event {
    std::string type;
    std::any data;
    Event(const std::string& type, const std::any& data = {}) : type(type), data(data) {}
};
