#pragma once
#include "UIregion.hpp"

struct UIeditorRegionRect : public UIregion {
	UIeditorRegionRect();
	void Set(UIregion* r);
	void Update() override;
	void Draw(sf::RenderWindow& rw) override;

	std::string GetType() { return "UIeditorRegionRect"; }

	UIregion* m_region{ nullptr };
private:
	void UpdatePosition();
	void LU_grab();
	void LD_grab();
	void RU_grab();
	void RD_grab();
	void Center_grab();

	UIregion points[5];
};
