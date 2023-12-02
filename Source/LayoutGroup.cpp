#include "LayoutGroup.hpp"

void VerticalLayoutGroup::OnEditable() {
	switch (connection)
	{
	case LayoutGroup::Neither:
		break;
	case LayoutGroup::Width:
		SetLocalX(0);
		SetWidth(dynamic_cast<Rect*>(GetParent())->GetWidth());
		break;
	case LayoutGroup::Height:
		SetLocalY(0);
		SetHeight(dynamic_cast<Rect*>(GetParent())->GetHeigth());
		break;
	case LayoutGroup::Both:
		SetLocalX(0);
		SetLocalY(0);
		SetWidth(dynamic_cast<Rect*>(GetParent())->GetWidth());
		SetHeight(dynamic_cast<Rect*>(GetParent())->GetHeigth());
		break;
	}

	size_t s = GetChildrens().size();
	float sss{ 0 };
	for (auto& u : GetChildrens()) {
		sss += dynamic_cast<Rect*>(u)->GetHeigth();
	}
	float ss = GetHeigth() - sss;
	ss /= s + 1;
	float start{ 0 };
	for (size_t i = 0; i < s; i++)
	{
		if (alignment % 3 == 0) { // left
			GetChildrens()[i]->SetLocalX(0);
		}
		else if (alignment % 3 == 1) { // center
			GetChildrens()[i]->SetLocalX(GetWidth() / 2 - dynamic_cast<Rect*>(GetChildrens()[i])->GetWidth() / 2);
		}
		else if (alignment % 3 == 2) { // right
			GetChildrens()[i]->SetLocalX(GetWidth() - dynamic_cast<Rect*>(GetChildrens()[i])->GetWidth());

		}

		if (alignment / 3 == 0) { // up
			GetChildrens()[i]->SetLocalY(ss * i + start);

		}
		else if (alignment / 3 == 1) { // middle
			GetChildrens()[i]->SetLocalY(ss * (i + 1) + start);

		}
		else if (alignment / 3 == 2) { // down
			GetChildrens()[i]->SetLocalY(ss * (i + 2) + start);

		}

		start += dynamic_cast<Rect*>(GetChildrens()[i])->GetHeigth();
	}
}

void HorizontalLayoutGroup::OnEditable() {
	switch (connection)
	{
	case LayoutGroup::Neither:
		break;
	case LayoutGroup::Width:
		SetLocalX(0);
		SetWidth(dynamic_cast<Rect*>(GetParent())->GetWidth());
		break;
	case LayoutGroup::Height:
		SetLocalY(0);
		SetHeight(dynamic_cast<Rect*>(GetParent())->GetHeigth());
		break;
	case LayoutGroup::Both:
		SetLocalX(0);
		SetLocalY(0);
		SetWidth(dynamic_cast<Rect*>(GetParent())->GetWidth());
		SetHeight(dynamic_cast<Rect*>(GetParent())->GetHeigth());
		break;
	}

	size_t s = GetChildrens().size();
	float sss{ 0 };
	for (auto& u : GetChildrens()) {
		sss += dynamic_cast<Rect*>(u)->GetWidth();
	}
	float ss = GetWidth() - sss;
	ss /= s + 1;
	float start{ 0 };
	for (size_t i = 0; i < s; i++)
	{
		if (alignment % 3 == 0) { // left
			GetChildrens()[i]->SetLocalX(ss * i + start);
		}
		else if (alignment % 3 == 1) { // center
			GetChildrens()[i]->SetLocalX(ss * (i + 1) + start);
		}
		else if (alignment % 3 == 2) { // right
			GetChildrens()[i]->SetLocalX(ss * (i + 2) + start);

		}

		if (alignment / 3 == 0) { // up
			GetChildrens()[i]->SetLocalY(0);
		}
		else if (alignment / 3 == 1) { // middle
			GetChildrens()[i]->SetLocalY(GetHeigth() / 2 - dynamic_cast<Rect*>(GetChildrens()[i])->GetHeigth() / 2);

		}
		else if (alignment / 3 == 2) { // down
			GetChildrens()[i]->SetLocalY(GetHeigth() - dynamic_cast<Rect*>(GetChildrens()[i])->GetHeigth());

		}

		start += dynamic_cast<Rect*>(GetChildrens()[i])->GetWidth();
	}
}

void ColumnGridLayoutGroup::OnEditable()
{
	switch (connection)
	{
	case LayoutGroup::Neither:
		break;
	case LayoutGroup::Width:
		SetLocalX(0);
		SetWidth(dynamic_cast<Rect*>(GetParent())->GetWidth());
		break;
	case LayoutGroup::Height:
		SetLocalY(0);
		SetHeight(dynamic_cast<Rect*>(GetParent())->GetHeigth());
		break;
	case LayoutGroup::Both:
		SetLocalX(0);
		SetLocalY(0);
		SetWidth(dynamic_cast<Rect*>(GetParent())->GetWidth());
		SetHeight(dynamic_cast<Rect*>(GetParent())->GetHeigth());
		break;
	}

	std::vector<float> lefts(percents.size(), 0.f);
	for (size_t i = 1; i < percents.size(); i++)
	{
		lefts[i] = lefts[i - 1] + GetWidth() * percents[i - 1];
	}
	Vector2 cell_size{ 0, cell_height };
	Vector2 top_left{ 0,0 };
	for (size_t i = 0; i < GetChildrens().size(); i++)
	{
		cell_size.x = GetWidth() * percents[i % percents.size()];
		top_left.x = lefts[i % percents.size()];
		top_left.y = cell_size.y * (i / percents.size() + skip_rows);

		if (!control_childrens) {
			if (alignment % 3 == 0) { // left
				GetChildrens()[i]->SetLocalX(top_left.x);
			}
			else if (alignment % 3 == 1) { // center
				GetChildrens()[i]->SetLocalX(top_left.x + cell_size.x / 2 - dynamic_cast<Rect*>(GetChildrens()[i])->GetWidth() / 2);
			}
			else if (alignment % 3 == 2) { // right
				GetChildrens()[i]->SetLocalX(top_left.x + cell_size.x - dynamic_cast<Rect*>(GetChildrens()[i])->GetWidth());
			}

			if (alignment / 3 == 0) { // up
				GetChildrens()[i]->SetLocalY(top_left.y);
			}
			else if (alignment / 3 == 1) { // middle
				GetChildrens()[i]->SetLocalY(top_left.y + cell_size.y / 2 - dynamic_cast<Rect*>(GetChildrens()[i])->GetHeigth() / 2);
			}
			else if (alignment / 3 == 2) { // down
				GetChildrens()[i]->SetLocalY(top_left.y + cell_size.y - dynamic_cast<Rect*>(GetChildrens()[i])->GetHeigth());
			}
			continue;
		}
		GetChildrens()[i]->SetLocalPosition(top_left);
		dynamic_cast<Rect*>(GetChildrens()[i])->SetSizeAcrossPos({ cell_size });
	}
}

void ColumnGridLayoutGroup::SetCount(size_t c)
{
	if (c == 0) return;

	percents.resize(c,	1.f/c);
}

void ColumnGridLayoutGroup::SetPercent(size_t i, float percent)
{
	if (i >= percents.size()) return;
	if (percent > 1.f || percent < 0.f) return;

	percents[i] = percent;
}

void ColumnGridLayoutGroup::SetCellHeight(float h)
{
	cell_height = h;
	SetHeight(cell_height * (GetChildrens().size() / 2 + GetChildrens().size() % 2));
}

void ColumnGridLayoutGroup::SetControlChildrens(bool c)
{
	control_childrens = c;
}

void ColumnGridLayoutGroup::SetSkipRows(size_t s)
{
	skip_rows = s;
}
