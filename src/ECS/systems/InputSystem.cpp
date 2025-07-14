#include "ECS/systems/InputSystem.hpp"
#include "ECS/Input.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

void InputSystem(ECS& ecs, const sf::Event& event) {
    // Example: update Input component for entities tagged as "player"
    if (event.is<sf::Event::KeyPressed>()) {
        if (const auto* keyEvent = event.getIf<sf::Event::KeyPressed>()) {
            for (Entity e : ecs.getEntitiesWithTag("player")) {
                auto* input = ecs.getComponent<Input>(e);
                if (input) {
                    input->pressedKeys.insert(keyEvent->code);
                }
            }
        }
    } else if (event.is<sf::Event::KeyReleased>()) {
        if (const auto* keyEvent = event.getIf<sf::Event::KeyReleased>()) {
            for (Entity e : ecs.getEntitiesWithTag("player")) {
                auto* input = ecs.getComponent<Input>(e);
                if (input) {
                    input->pressedKeys.erase(keyEvent->code);
                }
            }
        }
    }
}
