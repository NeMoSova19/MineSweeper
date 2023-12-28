#pragma once
#include "Button.hpp"
#include "Color.hpp"

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

void Button::Draw() {
	Drawable::Draw();
	text->Draw();
}

void Button::Update()
{
	UIregion::Update();
	text->Update();	
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