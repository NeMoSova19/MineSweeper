#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>

class ResourceManager {
public:
	static sf::Texture& GetTexture(std::string const& path) {
		if (Textures.contains(path)) {
			return Textures[path];
		}
		Textures[path].loadFromFile(path);
		return Textures[path];
	}
	static void SetTexture(std::string const& from, std::string const& to) {
		Textures[to] = GetTexture(from);
	}
	static sf::Font& GetFont(std::string const& path) {
		if (Fonts.contains(path)) {
			return Fonts[path];
		}
		Fonts[path].loadFromFile(path);
		return Fonts[path];
	}

private:
	static inline std::unordered_map<std::string, sf::Texture> Textures;
	static inline std::unordered_map<std::string, sf::Font> Fonts;
};