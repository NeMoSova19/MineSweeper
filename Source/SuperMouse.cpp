#include "SuperMouse.hpp"
#include <SFML/Window/Mouse.hpp>
#include "Windower.hpp"

Vector2 ToVector2(sf::Vector2f v) {
	return { v.x, v.y };
}
Vector2 ToVector2(sf::Vector2i v) {
	return { (float)v.x, (float)v.y};
}


void SuperMouse::Init() {
	win_pos = map_pos = ToVector2(sf::Mouse::getPosition());
	Windower::Win.AddEventCallback(sf::Event::EventType::MouseMoved, [&](sf::Event e) {MouseMoved(e); });
}

void SuperMouse::MouseMoved(sf::Event e)
{
	win_pos = { (float)e.mouseMove.x, (float)e.mouseMove.y };
	map_pos = ToVector2(Windower::Win.rw.mapPixelToCoords({ (int)win_pos.x, (int)win_pos.y }));
}

void SuperMouse::Update() {
	for (int i = 0; i < Count; i++)
	{
		mButtonPrev[i] = mButtonNow[i];
		mButtonNow[i] = sf::Mouse::isButtonPressed((sf::Mouse::Button)i);
		mButtonState[i] = static_cast<ButtonState>((mButtonPrev[i] << 1) + mButtonNow[i]);
	}
}