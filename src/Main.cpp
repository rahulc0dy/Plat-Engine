#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "imgui-SFML.h"
#include "imgui.h"
#include "spdlog/spdlog.h"

int main() {

    spdlog::set_level(spdlog::level::LOG_LEVEL);

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Plat Engine", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);

    if(ImGui::SFML::Init(window)) {
        spdlog::info("ImGui-SFML initialized");
    }



    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        ImGui::SFML::Update(window, sf::seconds(1.0f/60.0f));

        ImGui::Begin("Demo Window");
        ImGui::Text("This is a demo window.");
        ImGui::End();

        window.clear();

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
