#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "imgui-SFML.h"
#include "imgui.h"
#include "spdlog/spdlog.h"

int main() {
    // Set log level with cmake variable at compile time
    spdlog::set_level(spdlog::level::LOG_LEVEL);

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Plat Engine", sf::Style::Default);

    if(ImGui::SFML::Init(window)) {
        spdlog::info("ImGui-SFML initialized");
    }

    float sliderValue = 0.5f;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>())
            {
                spdlog::info("Window close event received");
                window.close();
            }
        }

        ImGui::SFML::Update(window, sf::seconds(1.0f/60.0f));

        ImGui::Begin("Demo Window", nullptr,  ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("This is a demo window.");
        ImGui::Button("Click Me");
        ImGui::SliderFloat("Slider", &sliderValue, 0.0f, 1.0f);
        ImGui::Text("Slider Value: %.2f", sliderValue);
        ImGui::End();

        window.clear();

        ImGui::SFML::Render(window);
        window.display();
    }
    
    ImGui::SFML::Shutdown();
    return 0;
}
