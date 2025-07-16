#include "ECS/systems/PhysicsSystem.hpp"
#include <box2d/box2d.h>
#include "ECS/PhysicsBody.hpp"
#include "ECS/Position.hpp"

void PhysicsSystem(ECS& ecs, b2WorldId world, float dt) {
    // Step Box2D world
    b2World_Step(world, dt, 8); // 8 substeps as example
    // Sync ECS Position with Box2D bodies
    for (Entity e : ecs.getEntitiesWith<PhysicsBody, Position>()) {
        auto* phys = ecs.getComponent<PhysicsBody>(e);
        auto* pos = ecs.getComponent<Position>(e);
        if (phys && pos) {
            b2Vec2 p = b2Body_GetPosition(phys->body);
            pos->x = p.x;
            pos->y = p.y;
        }
    }
}
