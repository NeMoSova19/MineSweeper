#pragma once
#include <SFML/System.hpp>
#include <deque>

class Time
{
public:
	static float GetElapsedTime();
	static size_t GetFPS();

	static void Init();
	static void Update();
private:
	static inline sf::Clock clock;
	static inline sf::Time time;

	static inline double total{ 0 };
	static inline int max_cnt{ 100 };
	static inline std::deque<int> deq;
};