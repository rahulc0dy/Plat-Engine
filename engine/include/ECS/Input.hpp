#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <set>

struct Input {
    std::set<sf::Keyboard::Key> pressedKeys;
};
