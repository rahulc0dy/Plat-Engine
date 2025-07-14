#pragma once 
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <typeindex>
#include <any>
#include <memory>
#include <functional>
#include <cstdint>
#include <string>
#include <set>
#include <limits>
#include "spdlog/spdlog.h"
#include <stdexcept>

using Entity = std::uint32_t;

class ECS {
public:
    static constexpr Entity MAX_ENTITIES = std::numeric_limits<Entity>::max();
    // ECS is the sole authority for entity creation and destruction.
    Entity createEntity(); // Declaration only
    void destroyEntity(Entity entity); // Declaration only

    template<typename Component, typename... Args>
    void addComponent(Entity entity, Args&&... args) {
        if (livingEntities.find(entity) == livingEntities.end()) {
            spdlog::error("Attempted to add component to non-existent or destroyed entity: {}", entity);
            throw std::runtime_error("Cannot add component to non-existent entity: " + std::to_string(entity));
        }
        auto& compMap = components[typeid(Component)];
        if (compMap.find(entity) != compMap.end()) {
            spdlog::warn("Entity {} already has component {}.", entity, typeid(Component).name());
        }
        compMap[entity] = Component(std::forward<Args>(args)...);
    }

    template<typename Component>
    void removeComponent(Entity entity) {
        auto it = components.find(typeid(Component));
        if (it != components.end()) {
            if (it->second.erase(entity) == 0) {
                spdlog::warn("Attempted to remove non-existent component {} from entity {}.", typeid(Component).name(), entity);
            }
        } else {
            spdlog::warn("Attempted to remove component {} from entity {} but component type not found.", typeid(Component).name(), entity);
        }
    }

    template<typename Component>
    Component* getComponent(Entity entity) {
        auto it = components.find(typeid(Component));
        if (it != components.end()) {
            auto& compMap = it->second;
            auto compIt = compMap.find(entity);
            if (compIt != compMap.end()) {
                return std::any_cast<Component>(&compIt->second);
            } else {
                spdlog::warn("Entity {} does not have component {}.", entity, typeid(Component).name());
            }
        } else {
            spdlog::warn("Component type {} not found for entity {}.", typeid(Component).name(), entity);
        }
        return nullptr;
    }

    template<typename Component>
    bool hasComponent(Entity entity) const {
        auto it = components.find(typeid(Component));
        if (it != components.end()) {
            return it->second.find(entity) != it->second.end();
        }
        return false;
    }

    // Tag system
    void addTag(Entity entity, const std::string& tag) {
        if (livingEntities.find(entity) == livingEntities.end()) {
            spdlog::warn("Attempted to add tag '{}' to non-existent entity {}.", tag, entity);
            return;
        }
        tags[entity].insert(tag);
    }
    void removeTag(Entity entity, const std::string& tag) {
        if (tags.find(entity) == tags.end()) {
            spdlog::warn("Attempted to remove tag '{}' from non-existent entity {}.", tag, entity);
            return;
        }
        tags[entity].erase(tag);
    }
    bool hasTag(Entity entity, const std::string& tag) const {
        auto it = tags.find(entity);
        if (it != tags.end()) {
            return it->second.count(tag) > 0;
        }
        return false;
    }
    std::vector<Entity> getEntitiesWithTag(const std::string& tag) const {
        std::vector<Entity> result;
        for (const auto& [entity, tagSet] : tags) {
            if (tagSet.count(tag)) result.push_back(entity);
        }
        return result;
    }

    // System registration: function takes ECS&, dt
    void registerSystem(const std::function<void(ECS&, float)>& system);
    void update(float dt);

    // Helper: get all entities with a set of components
    template<typename... Components>
    std::vector<Entity> getEntitiesWith() const {
        std::vector<Entity> result;
        for (Entity entity : livingEntities) {
            if ((hasComponent<Components>(entity) && ...)) {
                result.push_back(entity);
            }
        }
        return result;
    }

private:
    Entity nextEntity = 1;
    std::unordered_set<Entity> livingEntities;
    std::unordered_map<std::type_index, std::unordered_map<Entity, std::any>> components;
    std::unordered_map<Entity, std::set<std::string>> tags;
    std::vector<std::function<void(ECS&, float)>> systems;
};