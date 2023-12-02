#pragma once
#include "../StandartTypes.hpp"
#include <functional>
#include "UIrectangle.hpp"
#include <SFML/Graphics/RenderTexture.hpp>
#include "UIregion.hpp"


struct UIslider : public UIrectangle {
	~UIslider() = default;
	UIslider();
	UIslider(Vector2 pos, Vector2 size);

	void Grab();
	float GetValue();
	void SetValue(float v);
	void OnEditable();
	void SetCallbackOnSlide(std::function<void(float)> f);
	void Update() override;
	void Draw(sf::RenderWindow& rw) override;

private:
	float value{ 0.f };
	UIrectangle slider;
	std::function<void(float)> FOnSlide{ [](float) {} };
};
