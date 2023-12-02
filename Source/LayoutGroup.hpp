#pragma once
#include "UI/UIregion.hpp"


struct LayoutGroup : public UIregion {
	enum Alignment {
		UL, UC, UR,
		ML, MC, MR,
		DL, DC, DR,
	} alignment{ MC };
	enum Connection {
		Neither,
		Width,
		Height,
		Both
	} connection{ Neither };
};

struct HorizontalLayoutGroup : public LayoutGroup {
	void OnEditable() override;
};
struct VerticalLayoutGroup : public LayoutGroup {
	void OnEditable() override;
};
struct ColumnGridLayoutGroup : public LayoutGroup {
	void OnEditable() override;

	void SetCount(size_t c);
	void SetPercent(size_t i, float percent);
	void SetCellHeight(float h);
	void SetControlChildrens(bool c);
	void SetSkipRows(size_t s);

private:
	std::vector<float> percents{ 0.5f, 0.5f };
	float cell_height{ 20.f };
	bool control_childrens{ false };
	size_t skip_rows{ 0 };
};