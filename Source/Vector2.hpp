#pragma once
#include <SFML/System/Vector2.hpp>

struct Vector2
{
	float x{ 0 }, y{ 0 };

	Vector2() = default;
	Vector2(const Vector2& v);
	Vector2(float x, float y);

	bool operator < (const Vector2& v);
	bool operator <= (const Vector2& v);
	bool operator > (const Vector2& v);
	bool operator >= (const Vector2& v);
	bool operator == (const Vector2& v);
	bool operator != (const Vector2& v);

	void operator *= (float v);
	void operator /= (float v);
	void operator += (const Vector2& v);
	void operator -= (const Vector2& v);

	Vector2& operator = (const Vector2& v);
	Vector2 operator * (float v) const;
	Vector2 operator / (float v) const;
	Vector2 operator + (const Vector2& v) const;
	Vector2 operator - (const Vector2& v) const;
	Vector2 operator - () const;

	operator sf::Vector2f() const;
	bool is_zero() const;
};