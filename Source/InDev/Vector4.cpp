// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "StandartTypes.hpp"

Vector4::Vector4(const Vector4& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
}
Vector4::Vector4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
Vector4::Vector4(const Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = 1.f;
}

void Vector4::operator*=(float v)
{
	x *= v;
	y *= v;
	z *= v;
	w *= v;
}
void Vector4::operator/=(float v)
{
	x /= v;
	y /= v;
	z /= v;
	w /= v;
}
void Vector4::operator+=(const Vector4& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
}
void Vector4::operator-=(const Vector4& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
}

Vector4& Vector4::operator=(const Vector4& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	return *this;
}
Vector4 Vector4::operator*(float v) const
{
	return { x * v, y * v, z * v, w * v };
}
Vector4 Vector4::operator/(float v) const
{
	return { x / v, y / v, z / v, w / v };
}
Vector4 Vector4::operator+(const Vector4& v) const
{
	Vector4 n(x + v.x, y + v.y, z + v.z, w + v.w);
	return n;
}
Vector4 Vector4::operator-(const Vector4& v) const
{
	return { x - v.x, y - v.y, z - v.z, w - v.w };
}

float Vector4::dot_product(const Vector4& with) const
{
	return x * with.x + y * with.y + z * with.z + w*with.w;
}
Vector4 Vector4::inverse() const
{
	return { -x,-y,-z,-w };
}
Vector4& Vector4::set_inverse()
{
	x = -x;
	y = -y;
	z = -z;
	w = -w;
	return *this;
}
Vector4& Vector4::normalize()
{
	*this /= w;
	w = 1.f;
	return *this;
}

void Vector4::print() const
{
	printf_s("{ %.2f  %.2f  %.2f  %.2f }", x, y, z, w);
}
void Vector4::println() const
{
	print();
	std::cout << '\n';
}
