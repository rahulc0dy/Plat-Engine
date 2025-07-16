#include "ECS/AssetManager.hpp"

std::shared_ptr<sf::Texture> AssetManager::loadTexture(const std::string& name, const std::string& filepath) {
    auto it = textures.find(name);
    if (it != textures.end()) {
        spdlog::info("Texture '{}' already loaded, returning existing instance.", name);
        return it->second;
    }
    auto texture = std::make_shared<sf::Texture>();
    if(!texture->loadFromFile(filepath)) {
        spdlog::error("Failed to load texture from '{}'", filepath);
        return nullptr;
    }
    textures[name] = texture;
    spdlog::info("Loaded texture '{}' from '{}'", name, filepath);
    return texture;
}

std::shared_ptr<sf::Texture> AssetManager::getTexture(const std::string& name) const {
    auto it = textures.find(name);
    if(it != textures.end()) {
        return it->second;
    }

    spdlog::warn("Texture '{}' not found", name);
    return nullptr;
}

void AssetManager::unloadTexture(const std::string& name) {
    auto it = textures.find(name);
    if(it != textures.end()) {
        textures.erase(it);
        spdlog::info("Unloaded texture '{}'", name);
    } else {
        spdlog::warn("Attempted to unload non-existent texture '{}'", name);
    }
}

std::shared_ptr<sf::SoundBuffer> AssetManager::loadSound(const std::string& name, const std::string& filepath) {
    if (sounds.count(name)) {
        spdlog::info("Sound '{}' already loaded, returning existing instance.", name);
        return sounds[name];
    }
    auto sound = std::make_shared<sf::SoundBuffer>();
    if(!sound->loadFromFile(filepath)) {
        spdlog::error("Failed to load sound from '{}'", filepath);
        return nullptr;
    }
    sounds[name] = sound;
    spdlog::info("Loaded sound '{}' from '{}'", name, filepath);
    return sound;
}

std::shared_ptr<sf::SoundBuffer> AssetManager::getSound(const std::string& name) const {
    auto it = sounds.find(name);
    if(it != sounds.end()) {
        return it->second;
    }
    spdlog::warn("Sound '{}' not found", name);
    return nullptr;
}

void AssetManager::unloadSound(const std::string& name) {
    auto it = sounds.find(name);
    if(it != sounds.end()) {
        sounds.erase(it);
        spdlog::info("Unloaded sound '{}'", name);
    } else {
        spdlog::warn("Attempted to unload non-existent sound '{}'", name);
    }
}

void AssetManager::unloadAll() {
    textures.clear();
    sounds.clear();
    spdlog::info("Unloaded all assets");
}

