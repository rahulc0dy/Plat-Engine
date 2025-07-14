#include "ECS/EntityManager.hpp"

Entity EntityManager::createEntity() {
    // Deprecated: ECS manages entity lifecycle.
    return nextEntity++;
}

bool EntityManager::isAlive(Entity entity) const {
    // Deprecated: ECS manages entity lifecycle.
    return false;
}
