// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "StandartTypes.hpp"

AABB2d::AABB2d(float left, float right, float up, float down)
{
	L = left;
	R = right;
	U = up;
	D = down;
}

AABB2d::AABB2d(float width, float heigth)
{
	R = width;
	D = heigth;
}

AABB2d::AABB2d(const Vector2& size)
{
	R = size.x;
	D = size.y;
}

AABB2d::AABB2d(const Vector2& left_up, const Vector2& size)
{
	L = left_up.x;
	R = L + size.x;
	U = left_up.y;
	D = U + size.y;
}

bool AABB2d::contains(const Vector2& p) const
{
	return (p.x < R && p.y < D && p.x > L && p.y > U);
}

bool AABB2d::intersect(AABB2d& r)
{
	return true;
}

Vector2 AABB2d::get_size() const
{
	return { R - L, D - U };
}

Vector2 AABB2d::get_center()
{
	return center;
}
Vector2 AABB2d::get_left_up() {
	return { L, U };
}
Vector2 AABB2d::get_right_up() {
	return { R, U };
}
Vector2 AABB2d::get_left_down() {
	return { L, D };
}
Vector2 AABB2d::get_right_down() {
	return { R, D };
}

Vector2 AABB2d::get_centered_up() {
	return { center.x, U };
}
Vector2 AABB2d::get_centered_down() {
	return { center.x, D };
}
Vector2 AABB2d::get_centered_left() {
	return { L, center.y };
}
Vector2 AABB2d::get_centered_right() {
	return { R, center.y };
}

void AABB2d::move(const Vector2& m) {
	L += m.x; R += m.x;
	U += m.y; D += m.y;
}
void AABB2d::set_pos_about(PointType point, Vector2 p) {
	switch (point)
	{
	case PointType::LU:
		move(p - get_left_up());
		break;
	case PointType::RU:
		move(p - get_right_up());
		break;
	case PointType::RD:
		move(p - get_right_down());
		break;
	case PointType::LD:
		move(p - get_left_down());
		break;
	case PointType::Center:
		move(p - center);
		break;
	}
}
void AABB2d::set_size_about(PointType point, Vector2 s) {
	switch (point)
	{
	case PointType::LU:
		R = L + s.x;
		D = U + s.y;
		break;
	case PointType::RU:
		L = R - s.x;
		D = U + s.y;
		break;
	case PointType::RD:
		L = R - s.x;
		U = D - s.y;
		break;
	case PointType::LD:
		R = L + s.x;
		U = D - s.y;
		break;
	case PointType::Center:
		Vector2 c = center / 2.f;
		L = c.x - s.x;
		R = c.x + s.x;
		U = c.y - s.y;
		D = c.y + s.y;
		break;
	}
}