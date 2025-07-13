#include "ECS/ECS.hpp"
#include "spdlog/spdlog.h"

Entity ECS::createEntity() {
    spdlog::debug("Creating entity with ID: {}", nextEntity);
    livingEntities.insert(nextEntity);
    return nextEntity++;
}

void ECS::destroyEntity(Entity entity) {
    spdlog::debug("Destroying entity ID: {}", entity);
    livingEntities.erase(entity);
    for (auto& [type, compMap] : components) {
        compMap.erase(entity);
    }
    tags.erase(entity);
}

void ECS::registerSystem(const std::function<void(ECS&, float)>& system) {
    systems.push_back(system);
}

void ECS::update(float dt) {
    for (auto& system : systems) {
        system(*this, dt);
    }
}
