#pragma once
#include "../SuperMouse.hpp"
#include "UIeditorRegion.hpp"


UIeditorRegionRect::UIeditorRegionRect()
{
	for (auto& u : points) {
		u.SetRectType(RectType::Circle);
		u.Clicable(true).SetRadius(8);
	}
}

void UIeditorRegionRect::Set(UIregion* r) {
	m_region = r;

	if (!m_region) return;
	
	points[0].SetBGColor(Color::Blue).SetCenter(m_region->GetGlobalPosition());
	points[0].SetCallbackOnMouseGrab([&](SuperMouse::Key, UIregion*) {LU_grab(); });

	points[1].SetBGColor(Color::Blue).SetCenter({ m_region->GetLeft(), m_region->GetDown() });
	points[1].SetCallbackOnMouseGrab([&](SuperMouse::Key, UIregion*) {LD_grab(); });

	points[2].SetBGColor(Color::Blue).SetCenter({ m_region->GetRight(),m_region->GetUp() });
	points[2].SetCallbackOnMouseGrab([&](SuperMouse::Key, UIregion*) {RU_grab(); });

	points[3].SetBGColor(Color::Blue).SetCenter({ m_region->GetRight(),m_region->GetDown() });
	points[3].SetCallbackOnMouseGrab([&](SuperMouse::Key, UIregion*) {RD_grab(); });

	points[4].SetBGColor(Color::Blue).SetCenter(m_region->GetCenter());
	points[4].SetCallbackOnMouseGrab([&](SuperMouse::Key, UIregion*) {Center_grab(); });
}
void UIeditorRegionRect::Update() {
	if (!m_region) return;
	for (auto& u : points) {
		u.ClickUpdate();
		u.Update();
	}
	if (m_region) UpdatePosition();
}
void UIeditorRegionRect::Draw(sf::RenderWindow& rw)  {
	if (!m_region) return;
	for (auto& u : points) {
		u.Draw(rw);
	}
}


void UIeditorRegionRect::UpdatePosition() {
	points[0].SetCenter(m_region->GetGlobalPosition());
	points[1].SetCenter({ m_region->GetLeft(), m_region->GetDown() });
	points[2].SetCenter({ m_region->GetRight(),m_region->GetUp() });
	points[3].SetCenter({ m_region->GetRight(),m_region->GetDown() });
	points[4].SetCenter(m_region->GetCenter());
}
void UIeditorRegionRect::LU_grab() {
	m_region->SetLeftUp(SuperMouse::map_pose);
	//UpdatePosition();
}
void UIeditorRegionRect::LD_grab() {
	m_region->SetLeftDown(SuperMouse::map_pose);
	//UpdatePosition();
}
void UIeditorRegionRect::RU_grab() {
	m_region->SetRightUp(SuperMouse::map_pose);
	//UpdatePosition();
}
void UIeditorRegionRect::RD_grab() {
	m_region->SetRightDown(SuperMouse::map_pose);
}
void UIeditorRegionRect::Center_grab() {
	m_region->SetCenter(SuperMouse::map_pose);
	//UpdatePosition();
}