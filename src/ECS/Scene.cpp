#include "ECS/Scene.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <algorithm>
#include <fstream>
#include "spdlog/spdlog.h"

Scene::Scene(const std::string& name) : name(name), activeCamera(INVALID_ENTITY) {}

void Scene::update(float dt) {
    ecs.update(dt);
    // CameraComponent update can be handled by a system if needed
}

void Scene::render(sf::RenderWindow& window) {
    if (activeCamera != INVALID_ENTITY) {
        if (!ecs.hasComponent<CameraComponent>(activeCamera)) {
            spdlog::warn("Active camera entity {} does not have a CameraComponent.", activeCamera);
            window.setView(window.getDefaultView());
            return;
        }
        auto* cam = ecs.getComponent<CameraComponent>(activeCamera);
        if (cam) {
            window.setView(cam->view);
        } else {
            spdlog::error("Failed to get CameraComponent for entity {}.", activeCamera);
            window.setView(window.getDefaultView());
        }
    } else {
        window.setView(window.getDefaultView());
    }
    // Render entities/components here (extend as needed)
}

void Scene::addEntity(Entity entity) {
    if (std::find(entities.begin(), entities.end(), entity) != entities.end()) {
        spdlog::warn("Entity {} already exists in the scene.", entity);
        return;
    }
    entities.push_back(entity);
}

void Scene::removeEntity(Entity entity) {
    auto it = std::remove(entities.begin(), entities.end(), entity);
    if (it == entities.end()) {
        spdlog::warn("Attempted to remove non-existent entity {} from scene.", entity);
        return;
    }
    entities.erase(it, entities.end());
    if (activeCamera == entity) {
        spdlog::info("Active camera entity {} removed. Resetting active camera.", entity);
        activeCamera = INVALID_ENTITY;
    }
}

void Scene::setActiveCamera(Entity entity) {
    if (entity != INVALID_ENTITY && !ecs.hasComponent<CameraComponent>(entity)) {
        spdlog::error("Entity {} does not have a CameraComponent. Cannot set as active camera.", entity);
        throw std::runtime_error("Entity does not have a CameraComponent: " + std::to_string(entity));
    }
    activeCamera = entity;
}

Entity Scene::getActiveCamera() const {
    return activeCamera;
}

const std::string& Scene::getName() const {
    return name;
}

void Scene::load() {
    // Load resources/entities
    // Add error handling as needed when implemented
}

void Scene::unload() {
    // Cleanup resources/entities
    // Add error handling as needed when implemented
}

void Scene::saveToFile(const std::string& path) const {
    std::ofstream out(path);
    if (!out) {
        spdlog::error("Failed to open file for saving scene: {}", path);
        throw std::runtime_error("Failed to open file for saving scene: " + path);
    }
    out << "Scene: " << name << "\n";
    // Serialize entities/components here
}

void Scene::loadFromFile(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        spdlog::error("Failed to open file for loading scene: {}", path);
        throw std::runtime_error("Failed to open file for loading scene: " + path);
    }
    // Deserialize entities/components here
}

ECS& Scene::getECS() {
    return ecs;
}

const ECS& Scene::getECS() const {
    return ecs;
}
