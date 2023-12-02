#pragma once
#include "UIslider.hpp"
#include "../SuperMouse.hpp"


UIslider::UIslider() {
	SetBGColor(Color::White);

	slider.SetCallbackOnMouseGrab([&](SuperMouse::Key, UIregion*) {Grab(); });
	slider.SetBGColor(Color::Blue);
	slider.Clicable(true);
}

UIslider::UIslider(Vector2 pos, Vector2 size) {
	SetGlobalPosition(pos);
	SetSizeAcrossPos(size);
	SetBGColor(Color::White);

	slider.SetGlobalPosition(pos);
	slider.SetSizeAcrossPos({ size.x / 10.f, size.y });

	slider.SetCallbackOnMouseGrab([&](SuperMouse::Key, UIregion*) {Grab(); });
	slider.SetBGColor(Color::Blue);
	slider.Clicable(true);
}

void UIslider::Grab() {
	//float p = (SuperMouse::win_pose - SuperMouse::grab_from).x;
	//if (slider.GetLeft() + p < GetGlobalPosition().x) {
	//	slider.SetGlobalPosition(GetGlobalPosition());
	//	FOnSlide(GetValue());
	//	return;
	//}
	//
	//if (slider.GetRight() + p > GetRight()) {
	//	slider.SetGlobalPosition({ GetRight() - slider.GetWidth(), GetUp() });
	//	FOnSlide(GetValue());
	//	return;
	//}
	//
	//SuperMouse::grab_from.x = SuperMouse::win_pose.x;
	//FOnSlide(GetValue());
	//slider.Move({ p, 0 });
	//value = (slider.GetLeft() - GetLeft()) / (GetWidth() - slider.GetWidth());
}

float UIslider::GetValue() {
	return value;
}

void UIslider::SetValue(float v) {
	value = v;
	slider.SetGlobalPosition({ v * (GetWidth() - slider.GetWidth()) + GetLeft(), GetUp() });
}

void UIslider::OnEditable() {
	switch (m_editState)
	{
	case UIregion::EditState::Resize:
		slider.SetSizeAcrossPos({ GetWidth() / 10.f, GetHeigth() });
		break;
	case UIregion::EditState::Move:
		slider.SetGlobalPosition(GetGlobalPosition());
		break;
	case UIregion::EditState::Edit:
		slider.SetGlobalPosition(GetGlobalPosition());
		slider.SetSizeAcrossPos({ GetWidth() / 10.f, GetHeigth() });
		break;
	}
	SetValue(value);
}

void UIslider::SetCallbackOnSlide(std::function<void(float)> f) {
	FOnSlide = f;
}

void UIslider::Update() {
	UIrectangle::Update();
	slider.Update();
}

void UIslider::Draw(sf::RenderWindow& rw) {
	UIrectangle::Draw(rw);
	slider.Draw(rw);
}