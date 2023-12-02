#include "UIlogger.hpp"

UIlogger::UIlogger(Vector2 pos, Vector2 size, Color color) {
	SetGlobalPosition(pos);
	SetSizeAcrossPos(size);
	SetBGColor(color);
}

bool UIlogger::Contains(Vector2 const& p) {
	return false;
}

void UIlogger::Update() {
	UIregion::Update();
	for (auto& u : list) {
		u->Update();
	}
}

void UIlogger::Draw(sf::RenderWindow& rw) {
	UIrectangle::Draw(rw);
	for (auto& u : list) {
		u->Draw(rw);
	}
}

void UIlogger::Print(std::wstring text) {
	std::wstring s = L" >> " + text;
	auto* t = new UItext;
	t->SetCharacterSize(16);
	t->SetAlignment(AlignmentHorizontal::Left);
	t->SetAlignment(AlignmentVertical::Center);
	t->SetTextRectType(TextRectType::Bounded);
	t->SetWidth(GetWidth());
	t->SetBGColor(Color::HSVtoRGB(hue,100,75), {70,70,70}, 0.5);
	
	hue+=1;
	if (hue > 360) hue = hue%360;


	while (now_heigth + t->GetHeigth() > GetHeigth()) {
		float del_heigth = list.back()->GetHeigth();
		delete list.back(); 
		list.pop_back();
		for (auto& u : list) {
			u->Move({ 0, -del_heigth });
		}
		now_heigth -= del_heigth;
	}

	now_heigth += t->GetHeigth();

	if (list.empty()) {
		t->SetGlobalPosition(GetGlobalPosition());
	}
	else {
		t->SetGlobalPosition({ GetLeft(), list.front()->GetDown() });
	}

	list.push_front(t);

}
