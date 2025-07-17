#include "Editor.hpp"

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
            spdlog::set_level(spdlog::level::warn);
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
        while (const std::optional event = m_window.pollEvent()) {
            ImGui::SFML::ProcessEvent(m_window, *event);

            if (event->is<sf::Event::Closed>()) {
                spdlog::info("SFML window closed in Editor");
                m_window.close();
            }
        }

        ImGui::SFML::Update(m_window, sf::seconds(1.0f / 60.0f));
        ImGui::Begin("Editor Window", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("This is the Plat Engine Editor.");
        ImGui::Button("Click Me");
        ImGui::End();

        m_window.clear();
        ImGui::SFML::Render(m_window);
        m_window.display();
    }
}
