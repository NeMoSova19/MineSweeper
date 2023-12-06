#pragma once
#include "StandartTypes.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "UIregion.hpp"
#include "SuperMouse.hpp"
#include "UIenum.hpp"

enum class UItextStyle : uint8_t
{
	Regular = 0,            //< обычный
	Bold = 1 << 0,          //< жирный
	Italic = 1 << 1,        //< курсив
	Underlined = 1 << 2,    //< нижнее подчеркивание
	StrikeThrough = 1 << 3  //< зачеркивание	
};

struct UItext : public UIregion {
	UItext(UItext&&) = delete;
	UItext();
	~UItext() = default;

	void Update() override;
	void OnEditable() override;
	void Draw(sf::RenderWindow& rw) override;

	// Set
	UItext& SetText(std::wstring txt);
	UItext& SetStyle(uint32_t style);
	UItext& SetTextFillColor(Color c);
	UItext& SetTextOutlineColor(Color c);
	UItext& SetOutlineThickness(float thickness = 0);
	UItext& SetFont(std::string font);
	UItext& SetCharacterSize(uint32_t);
	UItext& SetAlignment(AlignmentHorizontal);
	UItext& SetAlignment(AlignmentVertical);
	UItext& SetTextRectType(TextRectType);
	UItext& SetEndLastWrap(EndLastWrap);

	// Get
	std::wstring		GetText();
	uint32_t			GetStyle();
	Color				GetTextFillColor();
	Color				GetTextOutlineColor();
	float				GetOutlineThickness();
	std::string			GetFont();
	uint32_t		    GetCharacterSize();
	AlignmentHorizontal getAlignmentH();
	AlignmentVertical   getAlignmentV();
	TextRectType		GetTextRectType();
	EndLastWrap			GetEndLastWrap();

protected:
	// «начимые пол€
	sf::Text m_text;
	std::string m_font{ "Fonts/times.ttf" };
	AlignmentHorizontal m_alig_H{ AlignmentHorizontal::Center };
	AlignmentVertical m_alig_V{ AlignmentVertical::Center };
	TextRectType m_textRectType{ TextRectType::Bounded };
	EndLastWrap m_endLastWrap{ EndLastWrap::DeleteLastWord };

	// ƒополнительные пол€
	//std::map<char, Vector2> m_lettersSize;

	sf::FloatRect aabb;
	float m_normalWidth{ 100.f };
	std::wstring m_string; // входна€ строка
	std::wstring m_restructString; // выходна€ строка

	// перенос всегда по словам
	// обрезка не влезающего текста только в режиме Bounded 
	// если единственное слово не влезает в Bounded то выводить влезающую часть + "..."
	// иначе по инструкции EndLastWrap


private:
	void RestructText_InOneLine();
	void RestructText_InfiniteWrap();
	void RestructText_Bounded();
};

enum class TextContent {
	digits,
	letters,
	all
};

struct TextInput : public UItext
{
	TextInput(TextInput&&) = delete;
	TextInput(std::wstring text = L"");
	~TextInput() = default;

	void func1(sf::Event e);

	void func(sf::Event e);

	void Update() override;

	void Draw(sf::RenderWindow& rw) override;

	TextInput& SetTextContent(TextContent tc);

	void OnMousePress(SuperMouse::Key key) override;
	void OnMousePressOut(SuperMouse::Key) override;

	void SetCallbackOnTextUpdated(std::function<void()> f);
	void SetCallbackOnTextEnter(std::function<void()> f);
	void SetCallbackOnTextOnFocus(std::function<void()> f);
	void SetCallbackOnTextOffFocus(std::function<void()> f);

private:
	bool m_selected{ false }, m_blink{ true }, m_canInput{ true };
	int counter{ 0 }, cursor{ 0 };
	TextContent text_content{ TextContent::all };
	std::function<void()> CallbackOnTextUpdated{ []() {} };
	std::function<void()> CallbackOnTextEnter{ []() {} };
	std::function<void()> CallbackOnTextOnFocus{ []() {} };
	std::function<void()> CallbackOnTextOffFocus{ []() {} };
};