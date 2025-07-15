#pragma once
#include <string>

struct Audio {
    std::string soundName;
    bool playOnStart = false;
    float volume = 100.f;
    Audio(const std::string& name = "", bool play = false, float vol = 100.f)
        : soundName(name), playOnStart(play), volume(vol) {}
};
