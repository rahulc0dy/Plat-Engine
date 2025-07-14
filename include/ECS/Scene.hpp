#pragma once
#include <vector>
#include "ECS.hpp"
#include "Camera.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class Scene {
public:
    Scene();
    void update(float dt);
    void render(sf::RenderWindow& window);
    void addEntity(Entity entity);
    void removeEntity(Entity entity);
    // Camera is now managed via ECS as a component
    void setActiveCamera(Entity entity);
    Entity getActiveCamera() const;
    void load();
    void unload();
private:
    ECS ecs;
    std::vector<Entity> entities;
    Entity activeCamera = 0;
};
