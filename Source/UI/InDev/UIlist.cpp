#pragma once
#include "UIlist.hpp"


void UIlist::Update() {
	UIrectangle::Update();
	for (auto& u : regions) {
		u->Update();
	}
}

void UIlist::Draw(sf::RenderWindow& rw) {
	UIrectangle::Draw(rw);
	for (auto& u : regions) {
		u->Draw(rw);
	}
}

void UIlist::Add(UIregion* r) {
	regions.push_back(r);
	r->SetCallbackOnEditable([&]() {OnEditable(); });
}
void UIlist::Insert(UIregion* r, size_t where) {
	regions.insert(regions.begin() + where, r);
	r->SetCallbackOnEditable([&]() {OnEditable(); });
}
void UIlist::Delete(size_t where) {
	regions[where]->DelCallbackOnEditable();
	regions.erase(regions.begin() + where);
}
void UIlist::Clear() {
	for (auto& u : regions) {
		u->DelCallbackOnEditable();
	}
	regions.clear();
}

void UIlist::SetSizeForAll(bool b) {
	m_setSizeForAll = b;
}

void UIlist::SetAlignment(AlignmentHorizontal ah) {
	m_alig_H = ah;
}

void UIlist::SetAlignment(AlignmentVertical av) {
	m_alig_V = av;
}

size_t UIlist::GetListSize() {
	return regions.size();
}

UIregion* UIlist::operator[](size_t pos)
{
	return regions[pos];
}








void UIlistVertical::OnEditable() {
	Vector2 pos_lu{ GetGlobalPosition() };
	for (auto& u : regions) {
		u->SetGlobalPosition(pos_lu);
		if (m_setSizeForAll) u->SetWidth(GetSize().x);
		pos_lu.y += u->GetHeigth();
	}
}



void UIlistHorizontal::OnEditable() {
	Vector2 pos_lu{ GetGlobalPosition() };
	float total_height{ 0 };
	for (auto& u : regions) {
		u->SetGlobalPosition(pos_lu);
		pos_lu.x += u->GetWidth();
		total_height = std::max(total_height, u->GetHeigth());
	}
	SetHeight(total_height);
}
