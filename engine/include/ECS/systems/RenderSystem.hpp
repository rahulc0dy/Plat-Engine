#pragma once 
#include <SFML/Graphics.hpp>
#include "ECS/ECS.hpp"
#include "ECS/Sprite.hpp"
#include "ECS/Transform.hpp"
#include "ECS/PhysicsBody.hpp"

void RenderSystem(ECS& ecs, sf::RenderWindow& window);
