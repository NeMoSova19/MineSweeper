#pragma once
#include <unordered_map>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class ResourceManager {
public:
	static sf::Shader& GetShader(std::string const& path, sf::Shader::Type type = sf::Shader::Fragment) {
		if (Shaders.contains(path)) {
			return Shaders[path];
		}
		Shaders[path].loadFromFile(path, type);
		return Shaders[path];
	}
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
	static sf::Music& GetMusic(std::string const& path) {
		if (Musics.contains(path)) {
			return Musics[path];
		}
		Musics[path].openFromFile(path);
		return Musics[path];
	}

private:
	static inline std::unordered_map<std::string, sf::Texture> Textures;
	static inline std::unordered_map<std::string, sf::Shader> Shaders;
	static inline std::unordered_map<std::string, sf::Font> Fonts;
	static inline std::unordered_map<std::string, sf::Music> Musics;
};