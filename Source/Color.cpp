#include "Color.hpp"
#include <utility>

Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
	r = red;
	g = green;
	b = blue;
	a = alpha;
}

Color Color::operator* (Color const& col) {
	int R = col.r - r;
	int G = col.g - g;
	int B = col.b - b;
	float k = (float)col.a / (col.a + a);
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

Color::operator sf::Color() const {
	return sf::Color(r, g, b, a);
}

Color Color::Black{ 0,0,0 };
Color Color::Blue{ 0,0,255 };
Color Color::Green{ 0,255,0 };
Color Color::Magenta{ 255,0,255 };
Color Color::Red{ 255,0,0 };
Color Color::White{ 255,255,255 };
Color Color::Yellow{ 255,255,0 };
Color Color::Transparent{ 0,0,0,0 };