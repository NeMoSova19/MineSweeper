#pragma once
#include <SFML/Graphics.hpp>
#include "StandartTypes.hpp"

/*
Полная обработанная информация о мыши
\param win_pose позиция относительно окна
\param pose		позиция мыши
\param dir		смещение за кадр
\param mButtonNow		состояние нажатия кнопок (bool)
\param mButtonState		1 из 4 состояний в ButtonState
*/
class SuperMouse {
public:
	static void initialize(sf::RenderWindow* _wwer);

	static void update();

	enum ButtonState{
		Not_press,
		Press,
		Release,
		Hold
	};

	enum Key {
		Left, Right, Middle, Side1, Side2
	};

	static inline const int8_t NumKeys{ 5 };
	static inline Vector2 win_pose, pose, map_pose, dir;
	static inline ButtonState mButtonState[NumKeys];


private:
	static inline Vector2 prev_pose;
	static inline sf::RenderWindow* wwer{nullptr};
	static inline bool mButtonNow[NumKeys];
	static inline bool mButtonPrev[NumKeys];

};