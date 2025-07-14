#pragma once
#include "ECS/ECS.hpp"
#include <SFML/Window/Event.hpp>
#include "ECS/Input.hpp"

void InputSystem(ECS& ecs, const sf::Event& event);
