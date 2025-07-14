#include "ECS/EntityManager.hpp"
#include "spdlog/spdlog.h"

Entity EntityManager::createEntity() {
    // Deprecated: ECS manages entity lifecycle.
    return nextEntity++;
}

bool EntityManager::isAlive(Entity entity) const {
    // Deprecated: ECS manages entity lifecycle.
    spdlog::warn("EntityManager::isAlive is deprecated and always returns false.");
    return false;
}
