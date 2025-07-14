#pragma once
#include <cstdint>

using Entity = std::uint32_t;

class EntityManager {
public:
    Entity createEntity();
    bool isAlive(Entity entity) const;
    // Entity destruction is managed by ECS. This class is deprecated for entity lifecycle.
private:
    Entity nextEntity = 1;
    // livingEntities removed; ECS manages entity lifecycle.
};