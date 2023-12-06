#pragma once
#include "Button.hpp"
#include <set>

class ToggleGroup;

class Toggle : public Button
{
public:
	Toggle(Toggle&&) = delete;
	Toggle() = default;

	void OnMousePress(SuperMouse::Key key) override;
	void OnMouseRelease(SuperMouse::Key key) override;
	void OnMouseEnter() override;
	void OnMouseExit() override;


	Toggle& SetCallbackOnSelect(std::function<void(UIregion*)> f);
	Toggle& SetCallbackOnDeSelect(std::function<void(UIregion*)> f);
	

	Toggle& SetSelectColor(Color);
	Toggle& SetSelect(bool);
	Toggle& SetGroup(ToggleGroup* tg);

	bool GetSelect();

	void Update() override;

protected:
	bool isSelected{ false };
	Color SelectColor{ 0,0,255 };

	virtual void OnSelect() {};
	virtual void OnDeSelect() {};

	std::vector<std::function<void(UIregion*)>> FOnSelect;
	std::vector<std::function<void(UIregion*)>> FOnDeSelect;

	ToggleGroup* group{ nullptr };
};

class ToggleGroup
{
	friend Toggle;
public:
	void SetAllowSwithOff(bool b);
	bool GetAllowSwithOff();

private:
	std::set<Toggle*> toggles;
	bool allowSwithOff{ false };

	void TurnOn(Toggle* t);
	void Add(Toggle* t);
};

