#include "ECS/Scene.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <algorithm>
#include <fstream>

Scene::Scene(const std::string& name) : name(name), activeCamera(INVALID_ENTITY) {}

void Scene::update(float dt) {
    ecs.update(dt);
    // CameraComponent update can be handled by a system if needed
}

void Scene::render(sf::RenderWindow& window) {
    if (activeCamera != INVALID_ENTITY && ecs.hasComponent<CameraComponent>(activeCamera)) {
        auto* cam = ecs.getComponent<CameraComponent>(activeCamera);
        if (cam) window.setView(cam->view);
    }
    else {
        window.setView(window.getDefaultView());
    }
    // Render entities/components here (extend as needed)
}

void Scene::addEntity(Entity entity) {
    entities.push_back(entity);
}

void Scene::removeEntity(Entity entity) {
    entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
    if (activeCamera == entity) {
        activeCamera = INVALID_ENTITY;
    }
}

void Scene::setActiveCamera(Entity entity) {
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
}

void Scene::unload() {
    // Cleanup resources/entities
}

void Scene::saveToFile(const std::string& path) const {
    // Stub for serialization (to be implemented)
    std::ofstream out(path);
    out << "Scene: " << name << "\n";
    // Serialize entities/components here
}

void Scene::loadFromFile(const std::string& path) {
    // Stub for deserialization (to be implemented)
    std::ifstream in(path);
    // Deserialize entities/components here
}

ECS& Scene::getECS() {
    return ecs;
}

const ECS& Scene::getECS() const {
    return ecs;
}
