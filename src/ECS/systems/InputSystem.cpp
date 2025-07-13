#include "ECS/systems/InputSystem.hpp"
#include <SFML/Window/Keyboard.hpp>

void InputSystem(ECS& ecs, const sf::Window& window) {
    // Example: update Input component for entities tagged as "player"
    for (Entity e : ecs.getEntitiesWithTag("player")) {
        auto* input = ecs.getComponent<Input>(e);
        if (input) {
            input->pressedKeys.clear();
            for (int k = 0; k < static_cast<int>(sf::Keyboard::KeyCount); ++k) {
                auto key = static_cast<sf::Keyboard::Key>(k);
                if (sf::Keyboard::isKeyPressed(key)) {
                    input->pressedKeys.insert(key);
                }
            }
        }
    }
}
