#include "StandartTypes.hpp"


//Color::Color(const Vector3& v) { // 0...1
//	r = static_cast<uint8_t>(v.x);
//	g = static_cast<uint8_t>(v.y);
//	b = static_cast<uint8_t>(v.z);
//}
//Color::Color(const Vector3Int& v) { // 0...255
//
//}
//Color::Color(const Vector4& v) { // 0...1
//	r = static_cast<uint8_t>(v.x);
//	g = static_cast<uint8_t>(v.y);
//	b = static_cast<uint8_t>(v.z);
//	a = static_cast<uint8_t>(v.w);
//}
//Color::Color(const Vector4Int& v) { // 0...255
//
//}
Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
	r = red;
	g = green;
	b = blue;
	a = alpha;
}

void Color::Shift()
{
	uint8_t _r = r;
	r = g; g = b; b = _r;
}

Color Color::Black{ 0,0,0 };
Color Color::Blue{ 0,0,255 };
Color Color::Green{ 0,255,0 };
Color Color::Magenta{ 255,0,255 };
Color Color::Red{ 255,0,0 };
Color Color::White{ 255,255,255 };
Color Color::Yellow{ 255,255,0 };
Color Color::Transparent{ 0,0,0,0 };
