#include "ECS/EntityManager.hpp"

Entity EntityManager::createEntity() {
    livingEntities.insert(nextEntity);
    return nextEntity++;
}

void EntityManager::destroyEntity(Entity entity) {
    livingEntities.erase(entity);
}

bool EntityManager::isAlive(Entity entity) const {
    return livingEntities.count(entity) > 0;
}
