//// This is a personal academic project. Dear PVS-Studio, please check it.
//// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
//#include "StandartTypes.hpp"
//
//Matrix4::Matrix4(float x1, float y1, float z1, float w1, float x2, float y2, float z2, float w2, float x3, float y3, float z3, float w3, float x4, float y4, float z4, float w4)
//{
//	this->x1 = x1; this->y1 = y1; this->z1 = z1; this->w1 = w1;
//	this->x2 = x2; this->y2 = y2; this->z2 = z2; this->w2 = w2;
//	this->x3 = x3; this->y3 = y3; this->z3 = z3; this->w3 = w3;
//	this->x4 = x4; this->y4 = y4; this->z4 = z4; this->w4 = w4;
//}
//Matrix4::Matrix4(const Vector4& a, const Vector4& b, const Vector4& c, const Vector4& d)
//{
//	this->x1 = a.x; this->y1 = a.y; this->z1 = a.z; this->w1 = a.w;
//	this->x2 = b.x; this->y2 = b.y; this->z2 = b.z; this->w2 = b.w;
//	this->x3 = c.x; this->y3 = c.y; this->z3 = c.z; this->w3 = c.w;
//	this->x4 = d.x; this->y4 = d.y; this->z4 = d.z; this->w4 = d.w;
//}
//
//void Matrix4::operator/=(float n)
//{
//	x1 /= n; y1 /= n; z1 /= n; w1 /= n;
//	x2 /= n; y2 /= n; z2 /= n; w2 /= n;
//	x3 /= n; y3 /= n; z3 /= n; w3 /= n;
//	x4 /= n; y4 /= n; z4 /= n; w4 /= n;
//}
//void Matrix4::operator*=(float n)
//{
//	x1 *= n; y1 *= n; z1 *= n; w1 *= n;
//	x2 *= n; y2 *= n; z2 *= n; w2 *= n;
//	x3 *= n; y3 *= n; z3 *= n; w3 *= n;
//	x4 *= n; y4 *= n; z4 *= n; w4 *= n;
//}
//void Matrix4::operator+=(const Matrix4& m)
//{
//	x1 += m.x1; y1 += m.y1; z1 += m.z1; w1 += m.w1;
//	x2 += m.x2; y2 += m.y2; z2 += m.z2; w2 += m.w2;
//	x3 += m.x3; y3 += m.y3; z3 += m.z3; w3 += m.w3;
//	x4 += m.x4; y4 += m.y4; z4 += m.z4; w4 += m.w4;
//}
//void Matrix4::operator-=(const Matrix4& m)
//{
//	x1 -= m.x1; y1 -= m.y1; z1 -= m.z1; w1 -= m.w1;
//	x2 -= m.x2; y2 -= m.y2; z2 -= m.z2; w2 -= m.w2;
//	x3 -= m.x3; y3 -= m.y3; z3 -= m.z3; w3 -= m.w3;
//	x4 -= m.x4; y4 -= m.y4; z4 -= m.z4; w4 -= m.w4;
//}
//
//Matrix4& Matrix4::operator=(const Matrix4& m)
//{
//	x1 = m.x1; y1 = m.y1; z1 = m.z1; w1 = m.w1;
//	x2 = m.x2; y2 = m.y2; z2 = m.z2; w2 = m.w2;
//	x3 = m.x3; y3 = m.y3; z3 = m.z3; w3 = m.w3;
//	x4 = m.x4; y4 = m.y4; z4 = m.z4; w4 = m.w4;
//	return *this;
//}
//
//Matrix4& Matrix4::operator/(float n) const
//{
//	Matrix4 m;
//	m = *this;
//	m /= n;
//	return m;
//}
//Matrix4& Matrix4::operator*(float n) const
//{
//	Matrix4 m;
//	m = *this;
//	m *= n;
//	return m;
//}
//Vector4& Matrix4::operator*(const Vector4& v) const
//{
//	Vector4 result;
//	result.x = x1 * v.x + y1 * v.y + z1 * v.z + w1 * v.w;
//	result.y = x2 * v.x + y2 * v.y + z2 * v.z + w2 * v.w;
//	result.z = x3 * v.x + y3 * v.y + z3 * v.z + w3 * v.w;
//	result.w = x4 * v.x + y4 * v.y + z4 * v.z + w4 * v.w;
//	return result;
//}
//Matrix4& Matrix4::operator+(const Matrix4& m) const
//{
//	Matrix4 n;
//	n = *this;
//	n += m;
//	return n;
//}
//Matrix4& Matrix4::operator-(const Matrix4& m) const
//{
//	Matrix4 n;
//	n = *this;
//	n -= m;
//	return n;
//}
//
//void Matrix4::print() const
//{
//	printf_s("{ %.1f, %.1f, %.1f, %.1f,\n  %.1f, %.1f, %.1f, %.1f,\n  %.1f, %.1f, %.1f, %.1f,\n  %.1f, %.1f, %.1f, %.1f  }", x1, y1, z1, w1, x2, y2, z2, w2, x3, y3, z3, w3, x4, y4, z4, w4);
//
//}
//void Matrix4::println() const
//{
//	print();
//	std::cout << '\n';
//}
