#include "ECS/systems/PhysicsSystem.hpp"
#include <box2d/box2d.h>
#include "ECS/PhysicsBody.hpp"
#include "ECS/Transform.hpp"

void PhysicsSystem(ECS& ecs, b2WorldId world, float dt) {
    // Step Box2D world
    b2World_Step(world, dt, 8); // 8 substeps as example
    // Sync ECS Transform with Box2D bodies
    for (Entity e : ecs.getEntitiesWith<PhysicsBody, Transform>()) {
        auto* phys = ecs.getComponent<PhysicsBody>(e);
        auto* transform = ecs.getComponent<Transform>(e);
        if (phys && transform) {
            b2Vec2 p = b2Body_GetPosition(phys->body);
            transform->position.x = p.x;
            transform->position.y = p.y;
        }
    }
}
