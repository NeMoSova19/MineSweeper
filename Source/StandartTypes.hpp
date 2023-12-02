#pragma once
#include <cmath>
#include <string>
#include <iostream>
#include <algorithm>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

#pragma warning (disable: 4244) // преобразование : возможна потеря данных

struct Vector2;
//struct Vector2Int;//

//struct Vector3;
//struct Vector3Int;//
//
//struct Vector4;
//struct Vector4Int;//

struct Color;

//struct Matrix3;
//struct Matrix3Int;//
//
//struct Matrix4;
//struct Matrix4Int;//

struct Color {
	uint8_t r{ 0 }, g{ 0 }, b{ 0 }, a{ 255 }, s{ 0 }, v{ 0 };
	uint16_t h{ 0 };

	Color() = default;
	//Color(const Vector3& v);
	//Color(const Vector3Int& v);
	//Color(const Vector4& v);
	//Color(const Vector4Int& v);
	Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);
	~Color() = default;

	static Color HSV(uint16_t h, uint8_t s, uint8_t v) {
		Color col;
		col.h = h;
		col.s = s;
		col.v = v;
		return col;
	}
	static Color RGB(uint8_t r, uint8_t g, uint8_t b) {
		Color col;
		col.r = r;
		col.g = g;
		col.b = b;
		return col;
	}

	static float Mod(float a, float b) {
		return a - int(a / b) * b;
	}


	static Color RGBtoHSV(uint8_t r, uint8_t g, uint8_t b) {
		auto [min, max] = std::minmax({ r, g, b });

		float R, G, B, S, V; uint16_t H;
		R = r / 255.f;
		G = g / 255.f;
		B = b / 255.f;
		auto [MIN, MAX] = std::minmax({ R, G, B });

		if (max == 0) S = 0;
		else S = 1.f - MIN / MAX;

		V = MAX;

		S *= 100;
		V *= 100;

		if (max == min) {
			return Color::HSV( 0, (uint8_t)S, (uint8_t)V );
		}

		if (max == r && g>=b) {
			H = 60 * (G - B) / (MAX - MIN);
		}
		else if (max == r && g < b) {
			H = 60 * (G - B) / (MAX - MIN) + 360;
		}
		else if (max == g) {
			H = 60 * (B - R) / (MAX - MIN) + 120;
		}
		else {
			H = 60 * (R - G) / (MAX - MIN) + 240;
		}

		return Color::HSV(H, (uint8_t)S, (uint8_t)V);
	}

	static Color HSVtoRGB(uint16_t h, uint8_t s, uint8_t v) {
		uint8_t H = (h / 60) % 6;
		uint16_t V = (uint16_t)v;
		uint16_t V1 = (100 - s) * V / 100; // Vmin
		uint16_t a = (V - V1) * (h % 60) / 60;
		uint16_t V2 = V1 + a; // Vinc
		uint16_t V3 = V - a; // Vdec

		V = V * 255 / 100;
		V1 = V1 * 255 / 100;
		V2 = V2 * 255 / 100;
		V3 = V3 * 255 / 100;

		switch (H)
		{
		case 0:
			return Color::RGB((uint8_t)V, (uint8_t)V2, (uint8_t)V1);
			break;
		case 1:
			return Color::RGB((uint8_t)V3, (uint8_t)V, (uint8_t)V1);
			break;
		case 2:
			return Color::RGB((uint8_t)V1, (uint8_t)V, (uint8_t)V2);
			break;
		case 3:
			return Color::RGB((uint8_t)V1, (uint8_t)V3, (uint8_t)V);
			break;
		case 4:
			return Color::RGB((uint8_t)V2, (uint8_t)V1, (uint8_t)V);
			break;
		case 5:
			return Color::RGB((uint8_t)V, (uint8_t)V1, (uint8_t)V3);
			break;
		}
		return Color::RGB(0, 0, 0);
	}


	Color operator >>(size_t n) const {
		char c = n % 3;
		Color col{ r,g,b,a };

		switch (c)
		{
		case 0:
			break;
		case 1:
			col = {b, r, g, a};
			break;
		case 2:
			col = {g, b, r, a};
			break;
		}
		return col;
	}
	Color operator <<(size_t n) const {
		char c = n % 3;
		Color col{ r,g,b,a };

		switch (c)
		{
		case 0:
			break;
		case 1:
			col = { g, b, r, a };
			break;
		case 2:
			col = { b, r, g, a };
			break;
		}
		return col;
	}
	Color operator* (Color const& col) {
		int R = col.r - r;
		int G = col.g - g;
		int B = col.b - b;
		float k = (float)col.a / (col.a+a);
		R *= k;
		G *= k;
		B *= k;
		return Color(
			uint8_t(r + R),
			uint8_t(g + G),
			uint8_t(b + B),
			std::max(a, col.a)
		);
	}

	inline operator sf::Color() const {
		return sf::Color(r, g, b, a);
	}

	std::string ToString() {
		return '[' + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ']';
	}

	static Color Red;
	static Color Green;
	static Color Blue;
	static Color White;
	static Color Black;
	static Color Yellow;
	static Color Magenta;
	static Color Transparent;


	void Shift();
	void rgbPrint() {
		printf_s("{%d %d %d}", r, g, b);
	}
	void rgbPrintln() {
		printf_s("{%d %d %d}\n", r, g, b);
	}
};


struct Vector2
{
	float x{0}, y{0};

	Vector2() = default;
	Vector2(const Vector2& v);
	Vector2(const sf::Vector2f& v);
	//explicit Vector2(const Vector3& v);
	Vector2(float x, float y);
	~Vector2() = default;

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

	operator sf::Vector2f() const 
	{
		return {x, y};
	}
	bool is_zero() const {
		return x == 0 && y == 0;
	}

	//Vector3 cross_product(const Vector2& with) const;
	float dot_product(const Vector2& with) const;
	float length() const;
	float length_squared() const;
	Vector2 perpendicular() const;
	Vector2 inverse() const;
	Vector2& set_inverse();
	Vector2& normalize();
	void print() const;
	void println() const;
	std::string to_string() const;
};


//struct Vector3
//{
//	float x{0}, y{0}, z{0};
//
//	Vector3() = default;
//	Vector3(const Vector3& v);
//	explicit Vector3(const Vector2& v);
//	explicit Vector3(const Vector4& v);
//	Vector3(float x, float y, float z);
//	~Vector3() = default;
//
//	void operator *= (float v);
//	void operator /= (float v);
//	void operator += (const Vector3& v);
//	void operator -= (const Vector3& v);
//
//	Vector3& operator = (const Vector3& v);
//	Vector3 operator * (float v) const;
//	Vector3 operator / (float v) const;
//	Vector3 operator + (const Vector3& v) const;
//	Vector3 operator - (const Vector3& v) const;
//
//	[[nodiscard]] Vector3 cross_product(const Vector3& with) const;
//	[[nodiscard]] float dot_product(const Vector3& with) const;
//	[[nodiscard]] float length() const;
//	[[nodiscard]] float length_squared() const;
//	[[nodiscard]] Vector3 inverse() const;
//	Vector3& set_inverse();
//	Vector3& normalize();
//	void print() const;
//	void println() const;
//};
//
//struct Vector4
//{
//	float x{ 0 }, y{ 0 }, z{ 0 }, w{ 0 };
//
//	Vector4() = default;
//	Vector4(const Vector4& v);
//	Vector4(float x, float y, float z, float w = 1.f);
//	explicit Vector4(const Vector3& v);
//	~Vector4() = default;
//
//	void operator *= (float v);
//	void operator /= (float v);
//	void operator += (const Vector4& v);
//	void operator -= (const Vector4& v);
//
//	Vector4& operator = (const Vector4& v);
//	Vector4 operator * (float v) const;
//	Vector4 operator / (float v) const;
//	Vector4 operator + (const Vector4& v) const;
//	Vector4 operator - (const Vector4& v) const;
//	
//	[[nodiscard]] float dot_product(const Vector4& with) const;
//	[[nodiscard]] Vector4 inverse() const;
//	Vector4& set_inverse();
//	Vector4& normalize();
//	void print() const;
//	void println() const;
//};
//
//
//
//struct Matrix3
//{
//	float
//		x1{0}, y1{0}, z1{0},
//		x2{0}, y2{0}, z2{0},
//		x3{0}, y3{0}, z3{0};
//
//	//Matrix3(Matrix3&&) = delete;
//	Matrix3(Matrix3&& m);
//	Matrix3() = default;
//	~Matrix3() = default;
//	Matrix3(const Matrix3& m);
//	Matrix3(float x1, float y1, float z1,
//			float x2, float y2, float z2,
//			float x3, float y3, float z3);
//	Matrix3(const Vector3& a, 
//			const Vector3& b, 
//			const Vector3& c);
//
//	void operator /= (float n);
//	void operator *= (float n);
//	//void operator *= (const Matrix3& n);
//	void operator += (const Matrix3& m);
//	void operator -= (const Matrix3& m);
//
//	Matrix3& operator = (Matrix3 const& m);
//	Matrix3 operator / (float n) const;
//	Matrix3 operator * (float n) const;
//	Vector3 operator * (const Vector3& v) const;
//	//Matrix3& operator * (const Matrix3& n) const;
//	Matrix3 operator + (const Matrix3& m) const;
//	Matrix3 operator - (const Matrix3& m) const;
//
//	void inverse();
//	void transpose();
//	float get_determinant() const;
//	Matrix3 get_inverse() const;
//	Matrix3 get_transpose() const;
//	void print() const;
//	void println() const;
//};

//struct Matrix4
//{
//	float
//		x1{ 0 }, y1{ 0 }, z1{ 0 }, w1{ 0 },
//		x2{ 0 }, y2{ 0 }, z2{ 0 }, w2{ 0 },
//		x3{ 0 }, y3{ 0 }, z3{ 0 }, w3{ 0 },
//		x4{ 0 }, y4{ 0 }, z4{ 0 }, w4{ 0 };
//
//	Matrix4(Matrix4&&) = delete;
//	Matrix4() = default;
//	~Matrix4() = default;
//	Matrix4(float x1, float y1, float z1, float w1,
//			float x2, float y2, float z2, float w2,
//			float x3, float y3, float z3, float w3,
//			float x4, float y4, float z4, float w4);
//	Matrix4(const Vector4& a,
//			const Vector4& b,
//			const Vector4& c,
//			const Vector4& d);
//
//	void operator /= (float n);
//	void operator *= (float n);
//	//void operator *= (const Matrix4& n);
//	void operator += (const Matrix4& m);
//	void operator -= (const Matrix4& m);
//
//	Matrix4& operator = (const Matrix4& m);
//	Matrix4& operator / (float n) const;
//	Matrix4& operator * (float n) const;
//	Vector4& operator * (const Vector4& v) const;
//	//Matrix4& operator * (const Matrix4& n) const;
//	Matrix4& operator + (const Matrix4& m) const;
//	Matrix4& operator - (const Matrix4& m) const;
//
//	//void inverse();
//	//void transpose();
//	//[[nodiscard]] float get_determinant() const;
//	//[[nodiscard]] Matrix3& get_inverse() const;
//	//[[nodiscard]] Matrix3& get_transpose() const;
//	void print() const;
//	void println() const;
//};


//
//enum class PointType
//{
//	LU,
//	RU,
//	RD,
//	LD,
//	Center
//};
//struct AABB2d
//{
//	Vector2 center{0, 0};
//	float L{0}, R{0}, U{0}, D{0};
//
//	AABB2d() = default;
//	AABB2d(float left, float right, float up, float down);
//	AABB2d(float width, float heigth);
//	AABB2d(const Vector2& size);
//	AABB2d(const Vector2& left_up, const Vector2& size);
//
//	Vector2 get_size() const;
//	Vector2 get_center();
//	Vector2 get_left_up();
//	Vector2 get_right_up();
//	Vector2 get_left_down();
//	Vector2 get_right_down();
//	Vector2 get_centered_up();
//	Vector2 get_centered_down();
//	Vector2 get_centered_left();
//	Vector2 get_centered_right();
//
//	void move(const Vector2& m);
//	void set_pos_about(PointType point, Vector2 p);
//	void set_size_about(PointType point, Vector2 s);
//
//	bool contains(const Vector2& p) const;
//	static bool intersect(AABB2d& r);
//};