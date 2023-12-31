#pragma once
#include "Vector2.hpp"
#include "Color.hpp"
#include "UIregion.hpp"
#include "Text.hpp"

struct Button : public UIregion {
	Button(Button&&) = delete;
	virtual ~Button();
	Button();

	// Setter
	Button& SetNormalColor(Color);
	Button& SetHoverColor(Color);
	Button& SetTouchColor(Color);
	
	// Getter
	Color GetNormalColor();
	Color GetHoverColor();
	Color GetTouchColor();

	// Events
	void OnEditable() override;
	void OnMouseExit() override;
	void OnMouseEnter() override;
	void OnMousePress(SuperMouse::Key key) override;
	void OnMouseRelease(SuperMouse::Key key) override;

	// Drawing
	void Draw() override;
	void Update() override;

	UItext* text;
protected:
	Color HoverColor{230,230,230};
	Color TouchColor{255,255,255};
	Color NormalColor{255,255,255};
};