#include "ECS/systems/RenderSystem.hpp"

void RenderSystem(ECS& ecs, sf::RenderWindow& window) {
    for (Entity e : ecs.getEntitiesWith<Transform, Sprite>()) {
        auto* transform = ecs.getComponent<Transform>(e);
        auto* spr = ecs.getComponent<Sprite>(e);
        if (transform && spr) {
            spr->sprite.setPosition(sf::Vector2f(transform->position.x, transform->position.y));
            window.draw(spr->sprite);
        }
    }
}
