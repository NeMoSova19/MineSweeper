#pragma once
#include "UIenum.hpp"
#include "UIrectangle.hpp"


struct UIlist abstract : public UIrectangle {
	UIlist(UIlist&&) = delete;
	UIlist() = default;
	~UIlist() = default;

	void Update() override;
	void Draw(sf::RenderWindow& rw) override;
	void Add(UIregion* r);
	void Insert(UIregion* r, size_t where);
	void Delete(size_t where);
	void Clear();
	void SetSizeForAll(bool b);
	void SetAlignment(AlignmentHorizontal ah);
	void SetAlignment(AlignmentVertical av);
	size_t GetListSize();
	UIregion* operator[](size_t pos);

protected:
	std::vector<UIregion*> regions;

	// настройки
	bool m_setSizeForAll{ true };
	AlignmentHorizontal m_alig_H{ AlignmentHorizontal::Left };	// выравнивание
	AlignmentVertical m_alig_V{ AlignmentVertical::Top };		// выравнивание
	float indent_one{ 0 }, indent_two{ 0 }; // отступы до и после
	// или сетка, тоесть начала прямоугольников по углам сетки
};





struct UIlistVertical : public UIlist {
	UIlistVertical(UIlistVertical&&) = delete;
	UIlistVertical() = default;
	~UIlistVertical() = default;

	void OnEditable() override;
};




struct UIlistHorizontal : public UIlist {
	UIlistHorizontal(UIlistHorizontal&&) = delete;
	UIlistHorizontal() = default;
	~UIlistHorizontal() = default;

	void OnEditable() override;
};