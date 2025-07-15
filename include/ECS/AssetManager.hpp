#pragma once 
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <unordered_map>
#include <string>
#include <memory>
#include "spdlog/spdlog.h"

class AssetManager {
public:
	std::shared_ptr<sf::Texture> loadTexture(const std::string& name, const std::string& filepath);
	std::shared_ptr<sf::Texture> getTexture(const std::string& name) const;
	void unloadTexture(const std::string& name);

	std::shared_ptr<sf::SoundBuffer> loadSound(const std::string& name, const std::string& filepath);
	std::shared_ptr<sf::SoundBuffer> getSound(const std::string& name) const;
	void unloadSound(const std::string& name);

	void unloadAll();

private:
	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;
	std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> sounds;
};
