// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "StandartTypes.hpp"

Matrix3::Matrix3(const Matrix3& m)
{
	x1 = m.x1; y1 = m.y1; z1 = m.z1;
	x2 = m.x2; y2 = m.y2; z2 = m.z2;
	x3 = m.x3; y3 = m.y3; z3 = m.z3;
}
Matrix3::Matrix3(Matrix3&& m)
{
	x1 = m.x1; y1 = m.y1; z1 = m.z1;
	x2 = m.x2; y2 = m.y2; z2 = m.z2;
	x3 = m.x3; y3 = m.y3; z3 = m.z3;
}
Matrix3::Matrix3(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
{
	this->x1 = x1; this->y1 = y1; this->z1 = z1;
	this->x2 = x2; this->y2 = y2; this->z2 = z2;
	this->x3 = x3; this->y3 = y3; this->z3 = z3;
}
Matrix3::Matrix3(const Vector3& a, const Vector3& b, const Vector3& c)
{
	x1 = a.x; y1 = a.y; z1 = a.z;
	x2 = b.x; y2 = b.y; z2 = b.z;
	x3 = c.x; y3 = c.y; z3 = c.z;
}

void Matrix3::operator/=(float n)
{
	x1 /= n; y1 /= n; z1 /= n;
	x2 /= n; y2 /= n; z2 /= n;
	x3 /= n; y3 /= n; z3 /= n;
}
void Matrix3::operator*=(float n)
{
	x1 *= n; y1 *= n; z1 *= n;
	x2 *= n; y2 *= n; z2 *= n;
	x3 *= n; y3 *= n; z3 *= n;
}
//void Matrix3::operator*=(const Matrix3& n)
//{
//	*this = {
//		x1 * n.x1 + y1 * n.x2 + z1 * n.x3,
//		x1 * n.y1 + y1 * n.y2 + z1 * n.y3,
//		x1 * n.z1 + y1 * n.z2 + z1 * n.z3,
//		x2 * n.x1 + y2 * n.x2 + z2 * n.x3,
//		x2 * n.y1 + y2 * n.y2 + z2 * n.y3,
//		x2 * n.z1 + y2 * n.z2 + z2 * n.z3,
//		x3 * n.x1 + y3 * n.x2 + z3 * n.x3,
//		x3 * n.y1 + y3 * n.y2 + z3 * n.y3,
//		x3 * n.z1 + y3 * n.z2 + z3 * n.z3
//	};
//}
void Matrix3::operator+=(const Matrix3& m)
{
	x1 += m.x1; y1 += m.y1; z1 += m.z1;
	x2 += m.x2; y2 += m.y2; z2 += m.z2;
	x3 += m.x3; y3 += m.y3; z3 += m.z3;
}
void Matrix3::operator-=(const Matrix3& m)
{
	x1 += m.x1; y1 += m.y1; z1 += m.z1;
	x2 += m.x2; y2 += m.y2; z2 += m.z2;
	x3 += m.x3; y3 += m.y3; z3 += m.z3;
}

Matrix3& Matrix3::operator=(Matrix3 const& m)
{
	this->x1 = m.x1;
	this->x2 = m.x2;
	this->x3 = m.x3;
	this->y1 = m.y1;
	this->y2 = m.y2;
	this->y3 = m.y3;
	this->z1 = m.z1;
	this->z2 = m.z2;
	this->z3 = m.z3;
	return *this;
}

Matrix3 Matrix3::operator/(float n) const
{
	Matrix3 m = *this;
	m /= n;
	return m;
}
Matrix3 Matrix3::operator*(float n) const
{
	Matrix3 m = *this;
	m *= n;
	return m;
}
Vector3 Matrix3::operator*(const Vector3& v) const
{
	Vector3 result(
		x1 * v.x + y1 * v.y + z1 * v.z,
		x2 * v.x + y2 * v.y + z2 * v.z,
		x3 * v.x + y3 * v.y + z3 * v.z
	);
	return result;
}
//Matrix3& Matrix3::operator*(const Matrix3& n) const
//{
//	Matrix3 result(
//		x1 * n.x1 + y1 * n.x2 + z1 * n.x3,
//		x1 * n.y1 + y1 * n.y2 + z1 * n.y3,
//		x1 * n.z1 + y1 * n.z2 + z1 * n.z3,
//		x2 * n.x1 + y2 * n.x2 + z2 * n.x3,
//		x2 * n.y1 + y2 * n.y2 + z2 * n.y3,
//		x2 * n.z1 + y2 * n.z2 + z2 * n.z3,
//		x3 * n.x1 + y3 * n.x2 + z3 * n.x3,
//		x3 * n.y1 + y3 * n.y2 + z3 * n.y3,
//		x3 * n.z1 + y3 * n.z2 + z3 * n.z3
//	);
//	return result;
//}
Matrix3 Matrix3::operator+(const Matrix3& m) const
{
	Matrix3 result(
		x1 + m.x1, y1 + m.y1, z1 + m.z1,
		x2 + m.x2, y2 + m.y2, z2 + m.z2,
		x3 + m.x3, y3 + m.y3, z3 + m.z3
	);
	return result;
}
Matrix3 Matrix3::operator-(const Matrix3& m) const
{
	Matrix3 result(
		x1 - m.x1, y1 - m.y1, z1 - m.z1,
		x2 - m.x2, y2 - m.y2, z2 - m.z2,
		x3 - m.x3, y3 - m.y3, z3 - m.z3
	);
	return result;
}

void Matrix3::inverse()
{
	*this = get_inverse();
}
void Matrix3::transpose()
{
	*this = get_transpose();
}
float Matrix3::get_determinant() const
{
	return x1 * y2 * z3 + x2 * y3 * z1 + x3 * y1 * z2 - x1 * y3 * z2 - x2 * y1 * z3 - x3 * y2 * z1;
}
Matrix3 Matrix3::get_inverse() const
{
	Matrix3 result;
	float det = get_determinant();
	if (det == 0.f) {
		// Обратной матрицы не существует
		// Возвращаем пустую матрицу
		return result;
	}
	float invDet = 1.f / det;
	// Вычисляем алгебраическое дополнение для каждого элемента матрицы
	Matrix3 adj;
	adj.x1 = y2 * z3 - y3 * z2;
	adj.y1 = x3 * z2 - x2 * z3;
	adj.z1 = x2 * y3 - x3 * y2;
	adj.x2 = y3 * z1 - y1 * z3;
	adj.y2 = x1 * z3 - x3 * z1;
	adj.z2 = x3 * y1 - x1 * y3;
	adj.x3 = y1 * z2 - y2 * z1;
	adj.y3 = x2 * z1 - x1 * z2;
	adj.z3 = x1 * y2 - x2 * y1;
	// Транспонируем матрицу алгебраических дополнений
	adj = adj.get_transpose();
	// Умножаем каждый элемент на обратный определитель
	result.x1 = adj.x1 * invDet;
	result.y1 = adj.y1 * invDet;
	result.z1 = adj.z1 * invDet;
	result.x2 = adj.x2 * invDet;
	result.y2 = adj.y2 * invDet;
	result.z2 = adj.z2 * invDet;
	result.x3 = adj.x3 * invDet;
	result.y3 = adj.y3 * invDet;
	result.z3 = adj.z3 * invDet;
	return result;
}
Matrix3 Matrix3::get_transpose() const
{
	Matrix3 result(x1,y1,z1, x2, y2, z2, x3, y3, z3);
	return result;
}

void Matrix3::print() const
{
	printf_s("{ %.1f, %.1f, %.1f,\n  %.1f, %.1f, %.1f,\n  %.1f, %.1f, %.1f }", x1, y1, z1, x2, y2, z2, x3, y3, z3);
}
void Matrix3::println() const
{
	print();
	std::cout << '\n';
}