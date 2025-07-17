#pragma once
#include <box2d/box2d.h>
#include "ECS/ECS.hpp"
#include "ECS/PhysicsBody.hpp"
#include "ECS/Position.hpp"
#include "ECS/Velocity.hpp"

void PhysicsSystem(ECS& ecs, b2WorldId world, float dt);
