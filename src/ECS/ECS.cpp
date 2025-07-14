#include "ECS/ECS.hpp"
#include "spdlog/spdlog.h"
#include <limits>
#include <stdexcept>

Entity ECS::createEntity() {
    if (nextEntity >= ECS::MAX_ENTITIES) {
        spdlog::error("Maximum number of entities reached ({}).", MAX_ENTITIES);
        throw std::overflow_error("Maximum number of entities reached");
    }
    if (livingEntities.find(nextEntity) != livingEntities.end()) {
        spdlog::error("Entity ID {} already exists.", nextEntity);
        throw std::runtime_error("Entity ID already exists: " + std::to_string(nextEntity));
    }
    spdlog::debug("Creating entity with ID: {}", nextEntity);
    livingEntities.insert(nextEntity);
    return nextEntity++;
}

void ECS::destroyEntity(Entity entity) {
    if (livingEntities.find(entity) == livingEntities.end()) {
        spdlog::warn("Attempted to destroy non-existent entity: {}", entity);
        return;
    }
    spdlog::debug("Destroying entity ID: {}", entity);
    livingEntities.erase(entity);
    for (auto& [type, compMap] : components) {
        compMap.erase(entity);
    }
    tags.erase(entity);
}

void ECS::registerSystem(const std::function<void(ECS&, float)>& system) {
    if (!system) {
        spdlog::error("Attempted to register an invalid (nullptr) system.");
        throw std::invalid_argument("Cannot register nullptr system");
    }
    systems.push_back(system);
}

void ECS::update(float dt) {
    if (systems.empty()) {
        spdlog::warn("No systems registered for update.");
    }
    for (auto& system : systems) {
        if (!system) {
            spdlog::error("Encountered nullptr system during update.");
            continue;
        }
        system(*this, dt);
    }
}
