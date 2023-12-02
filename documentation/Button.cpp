#pragma once
#include "Button.hpp"

Button::Button() {
	text = new UItext;
	text->SetBGColor({ 0,0,0,0 });
	text->SetParent(this);

	Clicable(true);
	SetTexture("Textures/ButtonStandart.png");
}
Button::~Button() {
	delete text;
}

void Button::OnEditable() {
	UIregion::OnEditable();
	//if (m_editState != EditState::Move) {
	//	text->SetSizeAcrossPos(GetSize());
	//}
}

void Button::OnMousePress(SuperMouse::Key key) {
	SetBGColor(TouchColor);
}

void Button::OnMouseRelease(SuperMouse::Key key)
{
	if (inRectNow) 
		SetBGColor(NormalColor*HoverColor);
	else 
		SetBGColor(NormalColor);
}

void Button::OnMouseEnter()
{
	SetBGColor(NormalColor*HoverColor);
}

void Button::OnMouseExit()
{
	SetBGColor(NormalColor);
}

float GetZnak(float f) {
	if (f > 0) return 1;
	return -1;
}

void Button::Draw(sf::RenderWindow& rw) {
	Drawable::Draw(rw);
	text->Draw(rw);
}

void Button::Update()
{
	UIregion::Update();
	text->Update();	
}

json Button::GetJson()
{
	json js = UIregion::GetJson();
	js["type"] = "UIButton";
	js["text"] = text->GetName();
	js["connected"] = json::array();
	return js;
}

void Button::SetJson(json js)
{
	UIregion::SetJson(js);
}

void Button::PostSetJson(json js)
{
	UIregion::PostSetJson(js);
	std::string s = js["text"];

	text = UIregion::FindByName<UItext>(s);
}

Button& Button::SetNormalColor(Color c)
{
	NormalColor = c;
	return *this;
}

Button& Button::SetHoverColor(Color c)
{
	HoverColor = c;
	return *this;
}

Button& Button::SetTouchColor(Color c)
{
	TouchColor = c;
	return *this;
}

Color Button::GetNormalColor()
{
	return NormalColor;
}

Color Button::GetHoverColor()
{
	return HoverColor;
}

Color Button::GetTouchColor()
{
	return TouchColor;
}