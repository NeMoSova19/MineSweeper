#pragma once

#include "UIregion.hpp"
#include "UIrectangle.hpp"
#include "../StandartTypes.hpp"
#include "UItext.hpp"

struct UIlogger : public UIrectangle {
	~UIlogger() = default;
	UIlogger(Vector2 pos, Vector2 size, Color color = Color(80, 40, 70));

	bool Contains(Vector2 const& p) override;
	void Update() override;
	void Draw(sf::RenderWindow& rw) override;
	void Print(std::wstring text);

private:
	//Color col{ 77,102,49 };
	int hue{ 0 };
	std::list <UItext*> list;
	float now_heigth{ 0 };
};