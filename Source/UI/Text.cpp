#include "Text.hpp"
#include "../ResourceManager.hpp"
#include "../Windower.hpp"

#pragma warning (disable: 6295) // неверно определенный цикл for. Цикл выполняется бесконечно
#pragma warning (disable: 6001) // использование неинициальзированной памяти
#pragma warning (disable: 6385) // чтение недопустимых данных


UItext& UItext::SetText(std::wstring txt) {
	m_restructString = m_string = txt;
	OnEditable();
	return *this;
}

UItext& UItext::SetStyle(uint32_t style)
{
	m_text.setStyle(style);
	OnEditable();
	return *this;
}

UItext& UItext::SetTextFillColor(Color c)
{
	m_text.setFillColor({ c.r, c.g, c.b, c.a });
	return *this;
}

std::wstring UItext::GetText() {
	return m_string;
}

UItext::UItext()
{
	m_text.setFont(ResourceManager::GetFont(m_font));
	m_text.setFillColor({ 0,0,0 });
}

void UItext::Update() {
	UIregion::Update();
}

void UItext::OnEditable() {
	UIregion::OnEditable();
	switch (m_textRectType)
	{
	case TextRectType::InOneLine:
		RestructText_InOneLine();
		break;
	case TextRectType::InfiniteWrap:
		RestructText_InfiniteWrap();
		break;
	case TextRectType::Bounded:
		RestructText_Bounded();
		break;
	}

	Vector2 calc_pos;
	switch (m_alig_H)
	{
	case AlignmentHorizontal::Left:
		calc_pos.x = GetLeft();
		break;
	case AlignmentHorizontal::Center:
		calc_pos.x = GetCenter().x - aabb.width / 2;
		break;
	case AlignmentHorizontal::Right:
		calc_pos.x = GetRight() - aabb.width;
		break;
	}

	switch (m_alig_V)
	{
	case AlignmentVertical::Top:
		calc_pos.y = GetUp();
		break;
	case AlignmentVertical::Center:
		calc_pos.y = GetCenter().y - aabb.height / 2;
		break;
	case AlignmentVertical::Down:
		calc_pos.y = GetDown() - aabb.height;
		break;
	}

	m_text.setPosition(calc_pos - Vector2(aabb.left, aabb.top));

}

void UItext::Draw(sf::RenderWindow& rw) {
	UIregion::Draw(rw);
	rw.draw(m_text);
}

uint32_t UItext::GetStyle() {
	return m_text.getStyle();
}

UItext& UItext::SetTextOutlineColor(Color c) {
	m_text.setOutlineColor({ c.r, c.g, c.b, c.a });
	return *this;
}
Color UItext::GetTextFillColor() {
	auto c = m_text.getFillColor();
	Color col;
	col.r = c.r;
	col.g = c.g;
	col.b = c.b;
	col.a = c.a;
	return col;
}
Color UItext::GetTextOutlineColor() {
	auto c = m_text.getOutlineColor();
	Color col;
	col.r = c.r;
	col.g = c.g;
	col.b = c.b;
	col.a = c.a;
	return col;
}
UItext& UItext::SetOutlineThickness(float thickness) {
	m_text.setOutlineThickness(thickness);
	return *this;
}
UItext& UItext::SetFont(std::string font)
{
	m_font = font;
	m_text.setFont(ResourceManager::GetFont(font));
	OnEditable();
	return *this;
}
UItext& UItext::SetCharacterSize(uint32_t size)
{
	m_text.setCharacterSize(size);
	OnEditable();
	return *this;
}
UItext& UItext::SetAlignment(AlignmentHorizontal alig)
{
	m_alig_H = alig;
	OnEditable();
	return *this;
}
UItext& UItext::SetAlignment(AlignmentVertical alig)
{
	m_alig_V = alig;
	OnEditable();
	return *this;
}
UItext& UItext::SetTextRectType(TextRectType trt)
{
	m_textRectType = trt;
	OnEditable();
	return *this;
}
UItext& UItext::SetEndLastWrap(EndLastWrap elw)
{
	m_endLastWrap = elw;
	OnEditable();
	return *this;
}
float UItext::GetOutlineThickness() {
	return m_text.getOutlineThickness();
}

std::string UItext::GetFont()
{
	return m_font;
}

uint32_t UItext::GetCharacterSize()
{
	return m_text.getCharacterSize();
}

AlignmentHorizontal UItext::getAlignmentH()
{
	return m_alig_H;
}

AlignmentVertical UItext::getAlignmentV()
{
	return m_alig_V;
}

TextRectType UItext::GetTextRectType()
{
	return m_textRectType;
}

EndLastWrap UItext::GetEndLastWrap()
{
	return m_endLastWrap;
}

std::string UItext::GetType()
{
	return "UItext";
}

json UItext::GetJson()
{
	json js = UIregion::GetJson();
	js["type"] = "UItext";
	js["string"] = m_string;

	js["style"] = GetStyle();
	Color c = GetTextFillColor();
	js["TextFillColor"][0] = c.r;
	js["TextFillColor"][1] = c.g;
	js["TextFillColor"][2] = c.b;
	js["TextFillColor"][3] = c.a;

	c = GetTextOutlineColor();
	js["TextOutlineColor"][0] = c.r;
	js["TextOutlineColor"][1] = c.g;
	js["TextOutlineColor"][2] = c.b;
	js["TextOutlineColor"][3] = c.a;

	js["OutlineThickness"] = GetOutlineThickness();
	js["Font"] = GetFont();
	js["CharacterSize"] = GetCharacterSize();
	js["AlignmentH"] = (int)getAlignmentH();
	js["AlignmentV"] = (int)getAlignmentV();
	js["TextRectType"] = (int)GetTextRectType();
	js["EndLastWrap"] = (int)GetEndLastWrap();
	
	return js;
}

void UItext::SetJson(json js)
{
	UIregion::SetJson(js);
	std::wstring ws;
	for (int i : js["string"]) {
		ws += (wchar_t)i;
	}
	SetText(ws);

	SetStyle(js["style"]);
	SetTextFillColor({ js["TextFillColor"][0],js["TextFillColor"][1],js["TextFillColor"][2],js["TextFillColor"][3] });
	SetTextOutlineColor({ js["TextOutlineColor"][0],js["TextOutlineColor"][1],js["TextOutlineColor"][2],js["TextOutlineColor"][3] });
	SetOutlineThickness(js["OutlineThickness"]);
	SetFont(js["Font"]);
	SetCharacterSize(js["CharacterSize"]);
	SetAlignment((AlignmentHorizontal)js["AlignmentH"]);
	SetAlignment((AlignmentVertical)js["AlignmentV"]);
	SetTextRectType(js["TextRectType"]);
	SetEndLastWrap(js["EndLastWrap"]);
}

void UItext::RestructText_InOneLine() {
	m_restructString = m_string;
	if (m_string.empty()) {
		m_text.setString("X");
		aabb = m_text.getLocalBounds();
		m_text.setString("");
	}
	else {
		m_text.setString(m_restructString);
		aabb = m_text.getLocalBounds();
	}
	float w = aabb.width;
	if (w >= m_normalWidth) {
		switch (m_alig_H)
		{
		case AlignmentHorizontal::Center:
			SetWidth(w + m_text.getCharacterSize() / 3.f);
			break;
		case AlignmentHorizontal::Left:
		case AlignmentHorizontal::Right:
			SetWidth(w + m_text.getCharacterSize() / 6.f);
			break;
		case AlignmentHorizontal::Width:
			SetWidth(w);
			break;
		}
		return;
	}

	SetWidth(m_normalWidth);
	return;
}

void UItext::RestructText_InfiniteWrap() {
	sf::Text T_text;
	T_text.setCharacterSize(m_text.getCharacterSize());
	T_text.setStyle(GetStyle());
	T_text.setFont(*m_text.getFont());
	sf::FloatRect _aabb;

	std::vector<std::wstring> split_text(1); std::vector<Vector2> sizes;
	for (auto const& u : m_string) {
		if (u == ' ' || u == '\n' || u == '\t') {
			if (!split_text.back().empty()) {
				split_text.emplace_back();
				split_text.back() += u;
				split_text.emplace_back();
				continue;
			}
		}
		split_text.back() += u;
	}

	if (!split_text.empty()) {

		for (auto u : split_text) { // вычисление всех размеров
			T_text.setString(u);
			_aabb = T_text.getLocalBounds();
			sizes.emplace_back(_aabb.width, _aabb.height);
		}

		bool* wraps = new bool[split_text.size()]; // какое слово переносим
		float counter = 0;
		float total_height = 0, now_height = 0;

		for (size_t i = 0; i < split_text.size(); i++) // вычисление переносов
		{
			counter += sizes[i].x;
			now_height = std::max(now_height, sizes[i].y);

			if (counter > GetSize().x) {
				wraps[i] = true;
				counter = sizes[i].x;
				continue;
			}

			wraps[i] = false;
		}

		std::vector<std::wstring> lines{ split_text.front() };

		for (size_t i = 1; i < split_text.size(); i++)
		{
			if (wraps[i]) {
				size_t ofs = 0;
				for (size_t j = 0; j < lines.back().size(); j++)
				{
					char c = lines.back()[j];
					if (c == ' ' || c == '\n' || c == '\t') {
						lines.back().erase(lines.back().begin() + j - ofs);
						ofs++;
						continue;
					}
					break;
				}

				if (!lines.back().empty())
					for (size_t j = lines.back().size() - 1; j >= 0; j--)
					{
						char c = lines.back()[j];
						if (c == ' ' || c == '\n' || c == '\t') {
							lines.back().erase(lines.back().begin() + j);
							continue;
						}
						break;
					}
				auto s = lines.back();
				if (!s.empty())
					lines.emplace_back();
			}

			lines.back() += split_text[i];
		}

		delete[] wraps;

		std::wstring final_string{ lines.front() };

		for (size_t i = 1; i < lines.size(); i++)
		{
			final_string += L'\n' + lines[i];
		}

		m_restructString = final_string;
		if (m_restructString.empty()) {
			m_text.setString("|");
			aabb = m_text.getLocalBounds();
			aabb.width = 0.f;
			m_text.setString("");
		}
		else {
			m_text.setString(final_string);
			aabb = m_text.getLocalBounds();
		}

		switch (m_alig_V)
		{
		case AlignmentVertical::Center:
			SetHeight(aabb.height + m_text.getCharacterSize() / 3.f);
			break;
		case AlignmentVertical::Top:
		case AlignmentVertical::Down:
			SetHeight(aabb.height + m_text.getCharacterSize() / 6.f);
			break;
		case AlignmentVertical::Height:
			SetHeight(aabb.height);
			break;
		}
		return;
	}
}

void UItext::RestructText_Bounded() {
	sf::Text T_text;
	T_text.setCharacterSize(m_text.getCharacterSize());
	T_text.setStyle(GetStyle());
	T_text.setFont(*m_text.getFont());
	sf::FloatRect _aabb;

	std::vector<std::wstring> split_text(1); std::vector<Vector2> sizes;
	for (auto const& u : m_string) {
		if (u == ' ' || u == '\n' || u == '\t') {
			if (!split_text.back().empty()) {
				split_text.emplace_back();
				split_text.back() += u;
				split_text.emplace_back();
				continue;
			}
		}
		split_text.back() += u;
	}

	if (!split_text.empty()) {

		for (auto u : split_text) { // вычисление всех размеров
			T_text.setString(u);
			_aabb = T_text.getLocalBounds();
			sizes.emplace_back(_aabb.width, _aabb.height);
		}

		bool* wraps = new bool[split_text.size()]; // какое слово переносим
		// определять не только какое слово переносить, но и сколько строк влезет в rect
		// центровка по верх/середина/низ только для первой строки
		// первая строка точно есть
		// если слова не влязиют по строкам, то в конце строки троеточие
		// выравнивать по центру строки которые влазиют в rect!
		float counter = 0;
		float total_height = 0, now_height = 0;

		for (size_t i = 0; i < split_text.size(); i++) // вычисление переносов
		{
			counter += sizes[i].x;
			now_height = std::max(now_height, sizes[i].y);

			if (counter > GetSize().x) {
				wraps[i] = true;
				counter = sizes[i].x;
				continue;
			}

			wraps[i] = false;
		}

		std::vector<std::wstring> lines{ split_text.front() };

		for (size_t i = 1; i < split_text.size(); i++)
		{
			if (wraps[i]) {
				size_t ofs = 0;
				for (size_t j = 0; j < lines.back().size(); j++)
				{
					char c = lines.back()[j];
					if (c == ' ' || c == '\n' || c == '\t') {
						lines.back().erase(lines.back().begin() + j - ofs);
						ofs++;
						continue;
					}
					break;
				}
				if(!lines.back().empty())
				for (size_t j = lines.back().size() - 1; j >= 0; j--)
				{
					char c = lines.back()[j];
					if (c == ' ' || c == '\n' || c == '\t') {
						lines.back().erase(lines.back().begin() + j);
						continue;
					}
					break;
				}
				auto s = lines.back();
				if (!s.empty())
					lines.emplace_back();
			}

			lines.back() += split_text[i];
		}

		delete[] wraps;

		std::wstring final_string{ lines.front() };

		for (size_t i = 1; i < lines.size(); i++)
		{
			T_text.setString(final_string + L'\n' + lines[i]);
			_aabb = T_text.getLocalBounds();
			if (_aabb.height > GetSize().y) {
				break;
			}
			final_string += L'\n' + lines[i];
		}

		m_restructString = final_string;
		if (m_restructString.empty()) {
			m_text.setString("|");
			aabb = m_text.getLocalBounds();
			m_text.setString("");
		}
		else {
			m_text.setString(final_string);
			aabb = m_text.getLocalBounds();
		}
	}
}


//void UItext::Update_letters() {
//	auto texture = m_text.getFont();
//	for (char c = 0; c < 127; c++)
//	{
//		auto t = texture->getGlyph(c, m_text.getCharacterSize(), m_text.getStyle() & sf::Text::Style::Bold, m_text.getOutlineThickness());
//		m_lettersSize[c] = { t.bounds.width + t.bounds.left, t.bounds.height + t.bounds.top };
//	}
//}
//Vector2 UItext::GetLineSize(std::string l) { // линия - без переносов
//	sf::Text _T = m_text;
//	_T.setString(l);
//	auto _aabb = _T.getLocalBounds();
//	return { _aabb.width, _aabb.height };
//
//	Vector2 total;
//	for (auto u : l) {
//		total.x += m_lettersSize[u].x;
//		total.y = std::max(total.y, m_lettersSize[u].y);
//	}
//	return total;
//}
//Vector2 UItext::GetStringSize(std::string s) { // любая строка
//	sf::Text _T = m_text;
//	_T.setString(s);
//	auto _aabb = _T.getLocalBounds();
//	return { _aabb.width, _aabb.height };
//
//	Vector2 total; std::string line;
//	for (auto u : s) {
//		if (u == '\n') {
//			auto gls = GetLineSize(line);
//			line = "";
//			total.x = std::max(total.x, gls.x);
//			total.y += gls.y;
//			continue;
//		}
//
//		line += u;
//	}
//	return total;
//}

	
TextInput::TextInput(std::wstring text)
{
	SetText(text);
	UIregion::Clicable(true);
	Windower::Win.AddEventCallback(sf::Event::KeyPressed, (std::bind(&TextInput::func1, this, std::placeholders::_1)));
	Windower::Win.AddEventCallback(sf::Event::TextEntered, (std::bind(&TextInput::func, this, std::placeholders::_1)));
}

void TextInput::func1(sf::Event e) { // KeyPressed вызывается до TextEntered
	if (m_selected) {
		if (e.key.code == sf::Keyboard::Enter) {
			m_selected = false;
			CallbackOnTextEnter();
			CallbackOnTextOffFocus();
			return;
		}
		if (e.key.code == sf::Keyboard::BackSpace) {
			if (!m_string.empty()) {
				if (cursor > 0 && cursor <= m_string.size()) {
					m_string.erase(m_string.begin() + cursor - 1);
					SetText(m_string);
					cursor--;
				}
			}
			m_canInput = false;
			CallbackOnTextUpdated();
			return;
		}
		if (e.key.code == sf::Keyboard::Delete) {
			if (!m_string.empty()) {
				if (cursor >= 0 && cursor < m_string.size()) {
					m_string.erase(m_string.begin() + cursor);
					SetText(m_string);
				}
			}
			m_canInput = false;
			CallbackOnTextUpdated();
			return;
		}
		if (e.key.control) {
			m_canInput = false;
			return;
		}

		m_canInput = true;

		if (e.key.code == sf::Keyboard::Left) {
			if (cursor > 0) {
				cursor--;
				counter = 60;
				m_blink = true;
			}
			return;
		}
		if (e.key.code == sf::Keyboard::Right) {
			if (cursor < m_restructString.size()) {
				cursor++;
				counter = 60;
				m_blink = true;
			}
			return;
		}
	}

}

void TextInput::func(sf::Event e) {
	if (m_selected && m_canInput) {
		//std::wcout << e.key.code << '\n';
		m_string.insert(m_string.begin() + cursor, static_cast<wchar_t>(e.key.code));
		SetText(m_string);
		cursor++;
		CallbackOnTextUpdated();
	}
}

void TextInput::Update() {
	UItext::Update();

	if (m_selected) {
		if (counter >= 120) {
			counter = 0;
			m_blink = !m_blink;
		}
		if (m_blink && cursor <= m_restructString.size()) m_text.setString(m_restructString.substr(0, cursor) + L'|' + m_restructString.substr(cursor));
		else m_text.setString(m_restructString);
		counter += 1;
	}
	else {
		if (counter != 0) {
			counter = 0;
			m_blink = true;
			m_text.setString(m_restructString);
		}
	}
}

void TextInput::Draw(sf::RenderWindow& rw) {
	UItext::Draw(rw);
	//PrimitiveDrawer::DrawText(&rw, GetPosition() - zero, m_text);
	//rw.draw(m_text);
}


void TextInput::OnMousePress(SuperMouse::Key key) {
	if (!m_selected) {
		m_selected = true;
		CallbackOnTextOnFocus();
	}
	int new_pos = static_cast<int>((SuperMouse::map_pose.x - GetLeft()) / 13);
	if (new_pos < 0) new_pos = 0;
	else if (new_pos > m_string.size()) new_pos = (int)m_string.size();
	cursor = new_pos;
	counter = 60;
	m_blink = true;
}

void TextInput::OnMousePressOut() {
	if (m_selected) {
		m_selected = false;
	}
	CallbackOnTextOffFocus();
}

void TextInput::SetCallbackOnTextUpdated(std::function<void()> f)
{
	CallbackOnTextUpdated = f;
}

void TextInput::SetCallbackOnTextEnter(std::function<void()> f)
{
	CallbackOnTextEnter = f;
}

void TextInput::SetCallbackOnTextOnFocus(std::function<void()> f)
{
	CallbackOnTextOnFocus = f;
}

void TextInput::SetCallbackOnTextOffFocus(std::function<void()> f)
{
	CallbackOnTextOffFocus = f;
}
