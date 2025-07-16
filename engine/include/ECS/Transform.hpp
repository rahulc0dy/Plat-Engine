#pragma once
#include <SFML/System/Vector2.hpp>

struct Transform {
    sf::Vector2f position{0.f, 0.f};
    sf::Vector2f scale{1.f, 1.f};
    float rotation{0.f}; // Degrees

    Transform() = default;
    Transform(const sf::Vector2f& pos, const sf::Vector2f& scl = {1.f, 1.f}, float rot = 0.f)
        : position(pos), scale(scl), rotation(rot) {}
};
