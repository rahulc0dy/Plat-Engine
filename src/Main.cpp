#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "imgui-SFML.h"
#include "imgui.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

#ifdef _WIN32
#include <Windows.h>
extern int main();
int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    try {
        return main();
    } catch (const std::exception& e) {
        spdlog::critical("Exception: {}", e.what());
        return EXIT_FAILURE;
    }
}
#endif

int main() {
    if (PRODUCTION_BUILD) {
        auto file_logger = spdlog::basic_logger_mt("file_logger", "logs/plat_engine.log");
        spdlog::set_default_logger(file_logger);
        spdlog::set_level(spdlog::level::warn);
    }
    else { 
        spdlog::set_level(spdlog::level::debug);
    }

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Plat Engine", sf::Style::Default);

    if (ImGui::SFML::Init(window)) {
        spdlog::info("ImGui-SFML initialized");
    }

    float sliderValue = 0.5f;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>()) {
                spdlog::info("SFML window closed");
                window.close();
            }
        }

        ImGui::SFML::Update(window, sf::seconds(1.0f / 60.0f));

        ImGui::Begin("Demo Window", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
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
