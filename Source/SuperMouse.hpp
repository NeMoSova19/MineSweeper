#pragma once
#include "Vector2.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class SuperMouse {
public:
	static void Init();

	static void Update();

	enum ButtonState: uint8_t{
		Not_press,
		Press,
		Release,
		Hold
	};

	enum Key: uint8_t {
		Left, Right, Middle, Side1, Side2, Count
	};

	static inline Vector2 win_pos, map_pos;
	static inline ButtonState mButtonState[Count];


private:
	static void MouseMoved(sf::Event);

	static inline bool mButtonNow[Count];
	static inline bool mButtonPrev[Count];

};