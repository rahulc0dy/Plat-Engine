#pragma once
#include <unordered_set>
#include <cstdint>

using Entity = std::uint32_t;

class EntityManager {
public:
    Entity createEntity();
    void destroyEntity(Entity entity);
    bool isAlive(Entity entity) const;

private:
    Entity nextEntity = 1;
    std::unordered_set<Entity> livingEntities;
};