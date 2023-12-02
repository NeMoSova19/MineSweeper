// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "StandartTypes.hpp"

Vector3::Vector3(const Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}
Vector3::Vector3(const Vector2& v)
{
	x = v.x;
	y = v.y;
	z = 1.f;
}
Vector3::Vector3(const Vector4& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}
Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Vector3::operator *= (float v)
{
	x *= v;
	y *= v;
	z *= v;
}
void Vector3::operator /= (float v)
{
	x /= v;
	y /= v;
	z /= v;
}
void Vector3::operator+=(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}
void Vector3::operator-=(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

Vector3& Vector3::operator = (const Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}
Vector3 Vector3::operator * (float v) const
{
	return { x * v, y * v, z * v };
}
Vector3 Vector3::operator / (float v) const
{
	return { x / v, y / v, z / v };
}
Vector3 Vector3::operator + (const Vector3& v) const
{
	return { x + v.x, y + v.y, z + v.z };
}
Vector3 Vector3::operator - (const Vector3& v) const
{
	return { x - v.x, y - v.y, z - v.z };
}

Vector3 Vector3::cross_product(const Vector3& with) const
{
	return { y * with.z - with.y * z,with.x * z - x * with.z, x * with.y - y * with.x };
}
float Vector3::dot_product(const Vector3& with) const
{
	return x * with.x + y * with.y + z * with.z;
}
float Vector3::length() const
{
	return sqrtf(length_squared());
}
float Vector3::length_squared() const
{
	return x * x + y * y + z * z;
}
Vector3 Vector3::inverse() const
{
	return { -x,-y,-z };
}
Vector3& Vector3::set_inverse()
{
	x = -x;
	y = -y;
	z = -z;
	return *this;
}
Vector3& Vector3::normalize()
{
	*this /= length();
	return *this;
}

void Vector3::print() const
{
	printf_s("{ %.2f  %.2f  %.2f }", x, y, z);
}
void Vector3::println() const
{
	print();
	std::cout << '\n';
}
