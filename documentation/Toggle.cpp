#include "Toggle.hpp"

void Toggle::OnMousePress(SuperMouse::Key key)
{
	if (isSelected) {
		if (group && group->GetAllowSwithOff() || !group) {
			SetSelect(false);
		}
	}
	else {
		if (group) {
			group->TurnOn(this);
			SetSelect(true);
		}
		else {
			SetSelect(true);
		}
	}
}

void Toggle::OnMouseRelease(SuperMouse::Key key)
{
	if (inRectNow)
		if (isSelected) 
			SetBGColor(SelectColor * HoverColor);
		else
			SetBGColor(NormalColor * HoverColor);
	else
		SetBGColor(NormalColor);
}

void Toggle::OnMouseEnter()
{
	if (isSelected) 
		SetBGColor(SelectColor * HoverColor);
	else
		SetBGColor(NormalColor * HoverColor);
}

void Toggle::OnMouseExit()
{
	if (isSelected)
		SetBGColor(SelectColor);
	else
		SetBGColor(NormalColor);
}

Toggle& Toggle::SetCallbackOnSelect(std::function<void(UIregion*)> f)
{
	FOnSelect.push_back(f);
	return *this;
}

Toggle& Toggle::SetCallbackOnDeSelect(std::function<void(UIregion*)> f)
{
	FOnDeSelect.push_back(f);
	return *this;
}

Toggle& Toggle::SetSelectColor(Color c)
{
	SelectColor = c;
	return *this;
}

Toggle& Toggle::SetSelect(bool b)
{
	if (isSelected == b) return *this;

	isSelected = b;
	if (b) {
		SetBGColor(SelectColor);
		OnSelect();
		for (auto i : FOnSelect) {
			i(this);
		}
	}
	else {
		SetBGColor(NormalColor);
		OnDeSelect();
		for (auto i : FOnDeSelect) {
			i(this);
		}
	}
	return *this;
}

Toggle& Toggle::SetGroup(ToggleGroup* tg)
{
	tg->Add(this);
	group = tg;
	return *this;
}

bool Toggle::GetSelect()
{
	return isSelected;
}

void Toggle::Update()
{
	Button::Update();
	//if (!inRectNow) {
	//	if (isSelected)
	//		SetBGColor(SelectColor);
	//	else
	//		SetBGColor(NormalColor);
	//}
}

void ToggleGroup::Add(Toggle* t)
{
	toggles.insert(t);
}

void ToggleGroup::TurnOn(Toggle* t)
{
	for (auto i : toggles) {
		if (i != t)
			i->SetSelect(false);
	}
}

void ToggleGroup::SetAllowSwithOff(bool b)
{
	allowSwithOff = b;
}

bool ToggleGroup::GetAllowSwithOff()
{
	return allowSwithOff;
}
