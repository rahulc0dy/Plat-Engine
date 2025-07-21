#include <imgui.h>

#include "Editor.hpp"
#include "ECS/Scene.hpp"
#include "ECS/Transform.hpp"
#include "ECS/Animation.hpp"
#include "ECS/AssetManager.hpp"
#include "ECS/Audio.hpp"
#include "ECS/Camera.hpp"
#include "ECS/Collider.hpp"
#include "ECS/Event.hpp"
#include "ECS/Input.hpp"
#include "ECS/Sprite.hpp"
#include "ECS/PhysicsBody.hpp"
#include "ECS/Script.hpp"
#include "ECS/Velocity.hpp"
#include "ECS/Name.hpp"

Editor::Editor()
    : m_window(sf::VideoMode::getDesktopMode(), "Plat Engine Editor", sf::Style::Default)
{
    if (PRODUCTION_BUILD) {
        try {
            if (!std::filesystem::exists("logs")) {
                std::filesystem::create_directory("logs");
            }
            auto file_logger = spdlog::basic_logger_mt("file_logger", "logs/plat_engine_editor.log");
            spdlog::set_default_logger(file_logger);
            spdlog::set_level(spdlog::level::err);
        } catch (const std::exception& e) {
            spdlog::error("Failed to create file logger: {}", e.what());
            spdlog::set_level(spdlog::level::warn);
        }
    } else {
        spdlog::set_level(spdlog::level::debug);
    }
    if (ImGui::SFML::Init(m_window)) {
        spdlog::info("ImGui-SFML initialized in Editor"); 
    }
    else {
        spdlog::error("Failed to initialize ImGui-SFML");
        throw std::runtime_error("ImGui-SFML initialization failed");
    }

}

Editor::~Editor() {
    ImGui::SFML::Shutdown();
    spdlog::info("ImGui-SFML shutdown in Editor");
}

void Editor::run() {
    while (m_window.isOpen()) {
        sf::Clock deltaClock;
        float dt = deltaClock.getElapsedTime().asSeconds();

        while (const std::optional event = m_window.pollEvent()) {
            ImGui::SFML::ProcessEvent(m_window, *event);

            if (event->is<sf::Event::Closed>()) {
                spdlog::info("SFML window closed in Editor");
                m_window.close();
            }
        }

        ImGui::SFML::Update(m_window, deltaClock.restart());
        m_scene.update(dt);

        drawMenuBar();
        drawEntityList();
        drawInspector();
        drawToolbar();
        drawGridSettings();
        drawScenesWidget();

        m_window.clear();
        m_scene.render(m_window);
        ImGui::SFML::Render(m_window);
        m_window.display();
    }
}

void Editor::drawMenuBar() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New Scene")) {
                m_scene = Scene("New Scene");
                spdlog::info("New scene created in Editor");
            }
            if (ImGui::MenuItem("Open Scene")) {
                // Implement scene loading logic
                spdlog::info("Open Scene clicked in Editor");
            }
            if (ImGui::MenuItem("Save Scene")) {
                // Implement scene saving logic
                spdlog::info("Save Scene clicked in Editor");
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo")) {
                // Implement undo logic
                spdlog::info("Undo clicked in Editor");
            }
            if (ImGui::MenuItem("Redo")) {
                // Implement redo logic
                spdlog::info("Redo clicked in Editor");
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void Editor::drawEntityList() {
    ImGui::Begin("Entities");
    auto& ecs = m_scene.getECS();

    // Use only the member variable for selection
    for (Entity e : ecs.getEntitiesWith<>()) {
        std::string label = "Entity " + std::to_string(e);
        if(ecs.getComponent<Name>(e)) {
            label = ecs.getComponent<Name>(e)->value;
        }
        if (ImGui::Selectable(label.c_str(), selectedEntity == e)) {
            selectedEntity = e;
        }
    }

    if(ImGui::Button("Create Entity")) {
        Entity newEntity = ecs.createEntity();
        ecs.addComponent<Transform>(newEntity, sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f), 0.f);
        ecs.addComponent<Name>(newEntity, "Entity " + std::to_string(newEntity));
        m_scene.addEntity(newEntity);
        selectedEntity = newEntity;
        spdlog::info("Created new entity: {}", newEntity);
    }

    ImGui::End();
}

void Editor::drawInspector() {
    ImGui::Begin("Inspector");
    auto& ecs = m_scene.getECS();

    if (selectedEntity != Scene::INVALID_ENTITY) {
        ImGui::Text("Entity ID: %u", selectedEntity);

        // Name editing
        if (auto* name = ecs.getComponent<Name>(selectedEntity)) {
            char buffer[128];
            std::strncpy(buffer, name->value.c_str(), sizeof(buffer));
            buffer[sizeof(buffer) - 1] = 0;
            if (ImGui::InputText("Name", buffer, sizeof(buffer), ImGuiInputTextFlags_EnterReturnsTrue)) {
                name->value = buffer[0] ? buffer : "Un-named Entity";
            }
        }
        else {
            ImGui::Text("Name: (none)");
        }

        if (auto* transform = ecs.getComponent<Transform>(selectedEntity)) {
            float pos[2] = { transform->position.x, transform->position.y };
            if (ImGui::InputFloat2("Position", pos)) {
                transform->position = sf::Vector2f(pos[0], pos[1]);
            }

            float scale[2] = { transform->scale.x, transform->scale.y };
            if (ImGui::InputFloat2("Scale", scale)) {
                transform->scale = sf::Vector2f(scale[0], scale[1]);
            }

            float rotation = transform->rotation;
            if (ImGui::InputFloat("Rotation", &rotation)) {
                transform->rotation = rotation;
            }
        }

        if (auto* spr = ecs.getComponent<Sprite>(selectedEntity)) {
            ImGui::Text("Sprite loaded");
            // TODO: Add sprite editing controls as needed
        }

        // TODO: Add more component editors as needed

        if (ImGui::Button("Delete Entity")) {
            ecs.destroyEntity(selectedEntity);
            spdlog::info("Deleted entity: {}", selectedEntity);
            selectedEntity = Scene::INVALID_ENTITY;
        }
    }
    else {
        ImGui::Text("No entity selected.");
    }

    ImGui::End();
}

void Editor::drawToolbar() {
    ImGui::Begin("Toolbar", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    if (ImGui::Button("Play")) {
        // TODO: Implement play mode
        spdlog::info("Play button clicked");
    }
    ImGui::SameLine();
    if (ImGui::Button("Pause")) {
        // TODO: Implement pause mode
        spdlog::info("Pause button clicked");
    }
    ImGui::SameLine();
    if (ImGui::Button("Stop")) {
        // TODO: Implement stop mode
        spdlog::info("Stop button clicked");
    }

    ImGui::End();
}

void Editor::drawGridSettings() {
    ImGui::Begin("Grid Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Checkbox("Enable Grid", &m_gridEnabled);
    ImGui::InputFloat("Grid Size", &m_gridSize);

    ImGui::End();
}

void Editor::drawScenesWidget() {
    ImGui::Begin("Scenes", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    // Display current scene name
    ImGui::Text("Current Scene: %s", m_scene.getName().c_str());

    // New scene button
    if (ImGui::Button("New Scene")) {
        m_scene = Scene("New Scene");
        selectedEntity = Scene::INVALID_ENTITY;
        spdlog::info("New scene created from Scenes widget");
    }

    ImGui::SameLine();

    // Open scene button (stub)
    if (ImGui::Button("Open Scene")) {
        // TODO: Implement scene loading dialog
        spdlog::info("Open Scene clicked in Scenes widget");
    }

    ImGui::SameLine();

    // Save scene button (stub)
    if (ImGui::Button("Save Scene")) {
        // TODO: Implement scene saving dialog
        spdlog::info("Save Scene clicked in Scenes widget");
    }

    ImGui::End();
}
