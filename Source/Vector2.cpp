#include "Vector2.hpp"

Vector2::Vector2(const Vector2& v)
{
	x = v.x;
	y = v.y;
}
Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

bool Vector2::operator<(const Vector2& v)
{
	return (x < v.x) && (y < v.y);
}
bool Vector2::operator<=(const Vector2& v)
{
	return (x <= v.x) && (y <= v.y);
}
bool Vector2::operator>(const Vector2& v)
{
	return (x > v.x) && (y > v.y);
}
bool Vector2::operator>=(const Vector2& v)
{
	return (x >= v.x) && (y >= v.y);
}
bool Vector2::operator==(const Vector2& v)
{
	return (x == v.x) && (y == v.y);
}
bool Vector2::operator!=(const Vector2& v)
{
	return (x != v.x) || (y != v.y);
}
void Vector2::operator *= (float v)
{
	x *= v;
	y *= v;
}
void Vector2::operator /= (float v)
{
	x /= v;
	y /= v;
}
void Vector2::operator += (const Vector2& v)
{
	x += v.x;
	y += v.y;
}
void Vector2::operator -= (const Vector2& v)
{
	x -= v.x;
	y -= v.y;
}

Vector2& Vector2::operator = (const Vector2& v)
{
	x = v.x;
	y = v.y;
	return *this;
}
Vector2 Vector2::operator * (float v) const
{
	return { x * v, y * v };
}
Vector2 Vector2::operator / (float v) const
{
	return { x / v, y / v };
}
Vector2 Vector2::operator + (const Vector2& v) const
{
	return { x + v.x, y + v.y };
}
Vector2 Vector2::operator - (const Vector2& v) const
{
	return { x - v.x, y - v.y };
}
Vector2 Vector2::operator-() const
{
	return { -x, -y };
}

Vector2::operator sf::Vector2f() const
{
	return { x, y };
}
bool Vector2::is_zero() const {
	return x == 0 && y == 0;
}