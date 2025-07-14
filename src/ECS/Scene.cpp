#include "ECS/Scene.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <algorithm>

Scene::Scene() {}

void Scene::update(float dt) {
    ecs.update(dt);
    // CameraComponent update can be handled by a system if needed
}

void Scene::render(sf::RenderWindow& window) {
    if (activeCamera != 0) {
        auto* cam = ecs.getComponent<CameraComponent>(activeCamera);
        if (cam) window.setView(cam->view);
    }
    // Render entities/components here (extend as needed)
}

void Scene::addEntity(Entity entity) {
    entities.push_back(entity);
}

void Scene::removeEntity(Entity entity) {
    entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
}

void Scene::setActiveCamera(Entity entity) {
    activeCamera = entity;
}

Entity Scene::getActiveCamera() const {
    return activeCamera;
}

void Scene::load() {
    // Load resources/entities
}

void Scene::unload() {
    // Cleanup resources/entities
}
