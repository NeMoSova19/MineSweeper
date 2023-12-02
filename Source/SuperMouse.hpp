#pragma once
#include <SFML/Graphics.hpp>
#include "StandartTypes.hpp"

/*
������ ������������ ���������� � ����
\param win_pose ������� ������������ ����
\param pose		������� ����
\param dir		�������� �� ����
\param mButtonNow		��������� ������� ������ (bool)
\param mButtonState		1 �� 4 ��������� � ButtonState
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