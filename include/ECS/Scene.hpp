#pragma once
#include <vector>
#include <string>
#include "ECS.hpp"
#include "Camera.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class Scene {
public:
    static constexpr Entity INVALID_ENTITY = ECS::MAX_ENTITIES;
    Scene(const std::string& name = "");
    void update(float dt);
    void render(sf::RenderWindow& window);
    void addEntity(Entity entity);
    void removeEntity(Entity entity);
    void setActiveCamera(Entity entity);
    Entity getActiveCamera() const;
    const std::string& getName() const;
    void load();
    void unload();
    void saveToFile(const std::string& path) const;
    void loadFromFile(const std::string& path);
    ECS& getECS();
    const ECS& getECS() const;
private:
    std::string name;
    ECS ecs;
    std::vector<Entity> entities;
    Entity activeCamera = INVALID_ENTITY;
};
