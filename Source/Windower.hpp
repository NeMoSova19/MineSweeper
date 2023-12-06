#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "StandartTypes.hpp"
#include <map>
#include <vector>
#include <functional>
#include "UIregion.hpp"

struct Windower;

struct Windower : public UIregion {
	Windower() = default;
	void Create(Vector2 size, std::string name, uint8_t style = sf::Style::Default, sf::ContextSettings settings = sf::ContextSettings());
	void SetTitlebarColor(Color c);

	void SetSize(Vector2 s);
	void SetPosition(Vector2 p);
	void SetCenter(Vector2 c);

	void Centering();

	Vector2 GetSize();
	Vector2 GetPosition();
	Vector2 GetCenter();

	void CheckEvents();
	void AddEventCallback(sf::Event::EventType type, std::function<void(sf::Event)> function);

	sf::RenderWindow rw{};
	static inline sf::View view{};
	std::map<sf::Event::EventType, std::vector<std::function<void(sf::Event)>>> EventBinds;

	static Windower Win;
};