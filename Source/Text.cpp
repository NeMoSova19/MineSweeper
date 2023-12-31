#include "Text.hpp"
#include "ResourceManager.hpp"
#include "Windower.hpp"
#include "Time.hpp"

#pragma warning (disable: 6295) // ������� ������������ ���� for. ���� ����������� ����������
#pragma warning (disable: 6001) // ������������� �������������������� ������
#pragma warning (disable: 6385) // ������ ������������ ������

UItext::UItext()
{
	m_text.setFont(ResourceManager::GetFont(m_font));
	m_text.setFillColor({ 0,0,0 });
	
}

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

void UItext::Draw() {
	UIregion::Draw();
	Windower::Win.rw.draw(m_text);
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

		for (auto u : split_text) { // ���������� ���� ��������
			T_text.setString(u);
			_aabb = T_text.getLocalBounds();
			sizes.emplace_back(_aabb.width, _aabb.height);
		}

		bool* wraps = new bool[split_text.size()]; // ����� ����� ���������
		float counter = 0;
		float total_height = 0, now_height = 0;

		for (size_t i = 0; i < split_text.size(); i++) // ���������� ���������
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

		for (auto u : split_text) { // ���������� ���� ��������
			T_text.setString(u);
			_aabb = T_text.getLocalBounds();
			sizes.emplace_back(_aabb.width, _aabb.height);
		}

		bool* wraps = new bool[split_text.size()]; 
		float counter = 0;
		float total_height = 0, now_height = 0;

		for (size_t i = 0; i < split_text.size(); i++) // ���������� ���������
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
	
TextInput::TextInput(std::wstring text)
{
	SetText(text);
	UIregion::Clicable(true);
	Windower::Win.AddEventCallback(sf::Event::KeyPressed, (std::bind(&TextInput::func1, this, std::placeholders::_1)));
	Windower::Win.AddEventCallback(sf::Event::TextEntered, (std::bind(&TextInput::func, this, std::placeholders::_1)));
}

void TextInput::func1(sf::Event e) { // KeyPressed ���������� �� TextEntered
	if (m_selected) {
		if (e.key.code == sf::Keyboard::Enter) {
			m_selected = false;
			CallbackOnTextEnter();
			CallbackOnTextOffFocus();
			return;
		}
		if (e.key.code == sf::Keyboard::Escape) {
			m_selected = false;
			CallbackOnTextEnter();
			CallbackOnTextOffFocus();
			return;
		}
		if (e.key.code == sf::Keyboard::BackSpace) {
			d_time = 0;
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
			d_time = 0;
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
		d_time = 0;
		m_blink = true;

		if (e.key.code == sf::Keyboard::Left) {
			if (cursor > 0) {
				cursor--;
				d_time = 0;
				m_blink = true;
			}
			return;
		}
		if (e.key.code == sf::Keyboard::Right) {
			if (cursor < m_restructString.size()) {
				cursor++;
				d_time = 0;
				m_blink = true;
			}
			return;
		}

		auto is_digit = [](sf::Keyboard::Key k)->bool { return k >= 26 && k <= 35; };

		switch (text_content)
		{
		case TextContent::digits:
			m_canInput = is_digit(e.key.code);
			break;
		case TextContent::letters:
			m_canInput = !is_digit(e.key.code);
			break;
		case TextContent::all:
			return;
		}
	}

}

void TextInput::func(sf::Event e) {
	if (m_selected && m_canInput) {
		m_string.insert(m_string.begin() + cursor, static_cast<wchar_t>(e.key.code));
		SetText(m_string);
		cursor++;
		d_time = 0;
		CallbackOnTextUpdated();
	}
}

void TextInput::Update() {
	UItext::Update();

	d_time += Time::GetElapsedTime();
	if (d_time >= 0.5f) {
		d_time -= 0.5f;
		m_blink ^= 1;
	}

	if (m_selected) {
		if (m_blink && cursor <= m_restructString.size()) m_text.setString(m_restructString.substr(0, cursor) + L'|' + m_restructString.substr(cursor));
		else m_text.setString(m_restructString);
	}
	else {
		m_text.setString(m_restructString);
	}
}

void TextInput::Draw() {
	UItext::Draw();
}

TextInput& TextInput::SetTextContent(TextContent tc)
{
	text_content = tc;
	return *this;
}

void TextInput::OnMousePress(SuperMouse::Key key) {
	if (!m_selected) {
		m_selected = true;
		CallbackOnTextOnFocus();
	}
	int new_pos = static_cast<int>((SuperMouse::map_pos.x - GetLeft()) / (m_text.getLocalBounds().width/m_string.size()));
	if (new_pos < 0) new_pos = 0;
	else if (new_pos > m_string.size()) new_pos = (int)m_string.size();
	cursor = new_pos;
	d_time = 0;
	m_blink = true;
}

void TextInput::OnMousePressOut(SuperMouse::Key) {
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
