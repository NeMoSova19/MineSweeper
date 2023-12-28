#pragma once
#include <cstdint>
#include <SFML/Graphics/Color.hpp>

#pragma warning (disable: 4244)

struct Color {
	Color() = default;
	Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);

	Color operator* (Color const& col);
	operator sf::Color() const;

	uint8_t r{ 0 }, g{ 0 }, b{ 0 }, a{ 255 };

	static Color Red;
	static Color Green;
	static Color Blue;
	static Color White;
	static Color Black;
	static Color Yellow;
	static Color Magenta;
	static Color Transparent;
};