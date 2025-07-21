#pragma once 
#include <string>

struct Name {
	std::string value;
	Name(const std::string& v = "New Entity") : value(v) {}
};