#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <string>

struct Animation {
    std::string name;
    int currentFrame = 0;
    int frameCount = 1;
    float frameTime = 0.1f; // Seconds per frame
    float timer = 0.f;
    bool loop = true;
    sf::IntRect frameRect; // For sprite sheet

    Animation(const std::string& name = "", int frames = 1, float time = 0.1f, bool loop = true)
        : name(name), frameCount(frames), frameTime(time), loop(loop) {}
};
