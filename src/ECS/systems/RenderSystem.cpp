#include "ECS/systems/RenderSystem.hpp"

void RenderSystem(ECS& ecs, sf::RenderWindow& window) {
    for (Entity e : ecs.getEntitiesWith<Position, Sprite>()) {
        auto* pos = ecs.getComponent<Position>(e);
        auto* spr = ecs.getComponent<Sprite>(e);
        if (pos && spr) {
            spr->sprite.setPosition(sf::Vector2f(pos->x, pos->y));
            window.draw(spr->sprite);
        }
    }
}
