#pragma once
#include <box2d/box2d.h>

struct PhysicsBody {
    b2BodyId body; // Use b2BodyId for Box2D v3 opaque handles
    bool isDynamic = true;
};
