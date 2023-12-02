#include "SuperMouse.hpp"

void SuperMouse::initialize(sf::RenderWindow* _wwer) {
	wwer = _wwer;
}

Vector2 ToVector2(sf::Vector2f v) {
	return { v.x, v.y };
}
Vector2 ToVector2(sf::Vector2i v) {
	return { (float)v.x, (float)v.y};
}

void SuperMouse::update() {
	prev_pose = pose;

	pose = ToVector2(sf::Mouse::getPosition());
	win_pose = ToVector2(sf::Mouse::getPosition(*wwer));
	map_pose = ToVector2(wwer->mapPixelToCoords({(int)win_pose.x, (int)win_pose.y}));

	dir = pose - prev_pose;

	for (int i = 0; i < NumKeys; i++)
	{
		mButtonPrev[i] = mButtonNow[i];
		mButtonNow[i] = sf::Mouse::isButtonPressed((sf::Mouse::Button)i);
		mButtonState[i] = static_cast<ButtonState>((mButtonPrev[i] << 1) + mButtonNow[i]);
	}
}