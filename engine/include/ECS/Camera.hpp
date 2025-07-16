#pragma once
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include "spdlog/spdlog.h"

struct CameraComponent {
    sf::View view;
    float zoomLevel = 1.0f;
    std::string name; // For editor identification
    CameraComponent(const std::string& name = "") : name(name) {
        view.setCenter({ 0.f, 0.f });
        view.setSize({ 1280.f, 720.f });
    }
    void setPosition(const sf::Vector2f& position) {
        view.setCenter(position);
    }
    void setZoom(float zoom) {
        if(zoom <= 0.f) {
			spdlog::error("Zoom level must be greater than 0. Current value: {}", zoom);
		}
        zoomLevel = zoom;
        view.setSize({ 1280.f * zoomLevel, 720.f * zoomLevel });
    }
    void setRotation(float angle) {
        view.setRotation(sf::degrees(angle));
    }
    void update() {
        // Implement smooth movement or effects if needed
    }
};
