// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "StandartTypes.hpp"

Vector2::Vector2(const Vector2& v)
{
	x = v.x;
	y = v.y;
}
Vector2::Vector2(const sf::Vector2f& v)
{
	x = v.x;
	y = v.y;
}
//Vector2::Vector2(const Vector3& v)
//{
//	x = v.x;
//	y = v.y;
//}
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

//Vector3 Vector2::cross_product(const Vector2& with) const
//{
//	return { 0.f, 0.f, x * with.y - y * with.x };
//}
float Vector2::dot_product(const Vector2& with) const
{
	return x * with.x + y * with.y;
}
float Vector2::length() const
{
	return sqrtf(length_squared());
}
float Vector2::length_squared() const
{
	return x * x + y * y;
}
Vector2 Vector2::perpendicular() const
{
	return { y, -x };
}
Vector2 Vector2::inverse() const
{
	return { -x, -y };
}
Vector2& Vector2::set_inverse()
{
	x = -x;
	y = -y;
	return *this;
}
Vector2& Vector2::normalize()
{
	*this /= length();
	return *this;
}

void Vector2::print() const
{
	printf_s("{ %.2f  %.2f }", x, y);
}
void Vector2::println() const
{
	print();
	std::cout << '\n';
}

std::string Vector2::to_string() const
{
	return "{ " + std::to_string(x) + ' ' + std::to_string(y) + " }";
}
