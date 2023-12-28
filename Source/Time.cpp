#include "Time.hpp"

float Time::GetElapsedTime()
{
	return time.asSeconds();
}

size_t Time::GetFPS()
{
	return std::llround(total);
}

void Time::Init()
{
	clock.restart();
}

void Time::Update()
{
	time = clock.getElapsedTime();
	clock.restart();

	int f = std::lround(1.f / time.asSeconds());

	if (f < 0)f = 0;

	total = (total * deq.size() + f) / (deq.size() + 1.);
	deq.push_back(f);

	if (deq.size() > max_cnt) {
		int n = deq.front();

		total = (total * deq.size() - n) / (deq.size() - 1.);

		deq.pop_front();
	}
}