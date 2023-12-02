#include "Windower.hpp"
#include "SuperMouse.hpp"
#include <string>
#include "UI/UIregion.hpp"
#include "UI/Text.hpp"
#include "UI/Button.hpp"
#include "UI/Toggle.hpp"
#include "LayoutGroup.hpp"
#include "Canvas.hpp"
#include "Dll_reader.hpp"
#include "Minesweeper.hpp"
#include "Settings.hpp"
#include "UI/UIeditorRegion.hpp"



void __CloseWindow(sf::Event const e) {
	if (e.type == sf::Event::Closed || (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Key::Escape)) {
		switch (Settings::Where)
		{
		case WHERE::MainMenu:
			Windower::Win.rw.close();
			return;

		case WHERE::Game:
			//Canvas::DisableAll();
			Canvas::SceneSettings("Game", true, false);
			Canvas::SceneSettings("Exit", true, true);
			Settings::Where = WHERE::Exit;
			//Game::Pause();
			return;

		case WHERE::Exit:
			Canvas::SceneSettings("Exit");
			Canvas::SceneSettings("Game", true, true);
			//Game::UnPause();
			Settings::Where = WHERE::Game;
			return;

		case WHERE::Settings:
			Canvas::SceneSettings("Settings");
			Canvas::SceneSettings("MainMenu", true, true);
			Settings::Where = WHERE::MainMenu;
			return;
		}
	}
}

struct FPS {
	static void Add(int f) {
		if (f < 0)f = 0;

		total = (total * deq.size() + f) / (deq.size() + 1.);
		deq.push_back(f);

		if (deq.size() > max_cnt) {
			int n = deq.front();

			total = (total * deq.size() - n) / (deq.size() - 1.);

			deq.pop_front();
		}
	}
	static inline double total{ 0 };
	static inline int max_cnt{ 100 };
	static inline std::deque<int> deq;
};

typedef size_t(*SizeTFunc)();

void Init() {
	// Layer0
	Canvas::CreateScene("Layer0");
	Canvas::SceneSettings("Layer0", true, true, true);
	auto& BG_r  = Canvas::AddOnScene("Layer0", new UIregion);

	BG_r
		// UIregion
		.SetName("L_r")
		.SetTexture("Textures/BG.png")
		.SetTextureRect({ 0,0,0,0 })
		.SetSpriteDrawType(SpriteDrawType::TextureRect)
		.SetBGColor(Color(255, 255, 255, 255))
		// Rect
		.SetSizeAcrossPos({ 800,800 })
		.SetGlobalPosition({ 0,0 });


	// MainMenu
	Canvas::CreateScene("MainMenu");
	Canvas::SceneSettings("MainMenu", true, true);
	auto& MM_bg = Canvas::AddOnScene("MainMenu", new UIregion); // bg
	auto& MM_t  = Canvas::AddOnScene("MainMenu", new UItext); // text
	auto& MM_t1 = Canvas::AddOnScene("MainMenu", new Button); // gm
	auto& MM_t2 = Canvas::AddOnScene("MainMenu", new Button); // gm
	auto& MM_t3 = Canvas::AddOnScene("MainMenu", new Button); // gm
	auto& MM_b1 = Canvas::AddOnScene("MainMenu", new Button); // stats
	auto& MM_b2 = Canvas::AddOnScene("MainMenu", new Button); // settings
	auto& MM_b3 = Canvas::AddOnScene("MainMenu", new Button); // exit

	auto& MM_vlg1 = Canvas::AddOnScene("MainMenu", new VerticalLayoutGroup);
	auto& MM_hlg1 = Canvas::AddOnScene("MainMenu", new HorizontalLayoutGroup);
	auto& MM_vlg2 = Canvas::AddOnScene("MainMenu", new VerticalLayoutGroup);

	MM_vlg1.SetParent(&Windower::Win);
	MM_bg.SetParent(&MM_vlg1);
	MM_vlg2.SetParent(&MM_bg);
	MM_t.SetParent(&MM_vlg2);
	MM_hlg1.SetParent(&MM_vlg2);
	MM_t1.SetParent(&MM_hlg1);
	MM_t2.SetParent(&MM_hlg1);
	MM_t3.SetParent(&MM_hlg1);
	MM_b1.SetParent(&MM_vlg2);
	MM_b2.SetParent(&MM_vlg2);
	MM_b3.SetParent(&MM_vlg2);

	MM_vlg1.connection = LayoutGroup::Connection::Both;
	MM_vlg1.alignment = LayoutGroup::Alignment::MC;

	MM_vlg2.connection = LayoutGroup::Connection::Both;
	MM_vlg2.alignment = LayoutGroup::Alignment::MC;

	MM_hlg1.connection = LayoutGroup::Connection::Width;
	MM_hlg1.alignment = LayoutGroup::Alignment::MC;
	MM_hlg1.SetHeight(140);

	// MM_bg
	MM_bg
		// UIregion
		.SetName("MM_bg")
		.SetBGColor(Color(125, 125, 125, 210))
		// Rect
		.SetSizeAcrossPos({ 600,700 });

	// MM_t
	MM_t
		// UItext
		.SetText(L"Сапер")
		.SetStyle(sf::Text::Style::Bold | sf::Text::Style::Italic)
		.SetTextFillColor(Color(0, 0, 0))
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(3.f)
		.SetFont("Fonts/times.ttf")
		.SetCharacterSize(120)
		.SetAlignment(AlignmentHorizontal::Center)
		.SetAlignment(AlignmentVertical::Center)
		.SetTextRectType(TextRectType::Bounded)
		.SetEndLastWrap(EndLastWrap::DeleteLastWord)
		// UIregion
		.SetName("MM_T_Saper")
		.SetBGColor(Color(0, 0, 0, 0))
		// Rect
		.SetSizeAcrossPos({ 320,120 })
		.SetCenter({ 400,180 });

	MM_t1
		// Button
		.SetNormalColor(Color::White)
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetTouchColor(Color::White)
		// UIregion
		.SetName("MM_B_t1")
		.SetBGColor(Color::White)
		.SetTexture("Button1k1")
		.SetTextureRect(Rect(0, 0, 128, 128))
		.SetRectType(RectType::Rect)	
		// Rect
		.SetSizeAcrossPos({ 140,140 })
		.SetCenter({ 250,350 });
	MM_t1.text
		// UItext
		->SetText(L"9 на 9")
		.SetStyle(sf::Text::Style::Regular)
		.SetTextFillColor(Color(0, 0, 0))
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetFont("Fonts/times.ttf")
		.SetCharacterSize(28)
		.SetAlignment(AlignmentHorizontal::Center)
		.SetAlignment(AlignmentVertical::Center)
		.SetTextRectType(TextRectType::Bounded)
		.SetEndLastWrap(EndLastWrap::DeleteLastWord)
		// UIregion
		.SetName("MM_B_T_8x8")
		.SetBGColor(Color(0, 0, 0, 0))
		// Rect
		.SetSizeAcrossPos({ 140,140 });

	MM_t2
		// Button
		.SetNormalColor(Color::White)
		.SetHoverColor(Color(0,0,0,25))
		.SetTouchColor(Color::White)
		// UIregion
		.SetName("MM_B_t2")
		.SetBGColor(Color::White)
		.SetTexture("Button1k1")
		.SetTextureRect(Rect(0, 0, 128, 128))
		.SetRectType(RectType::Rect)
		// Rect
		.SetSizeAcrossPos({ 140,140 })
		.SetCenter({ 400,350 });
	MM_t2.text
		// UItext
		->SetText(L"16 на 16")
		.SetStyle(sf::Text::Style::Regular)
		.SetTextFillColor(Color(0, 0, 0))
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetFont("Fonts/times.ttf")
		.SetCharacterSize(28)
		.SetAlignment(AlignmentHorizontal::Center)
		.SetAlignment(AlignmentVertical::Center)
		.SetTextRectType(TextRectType::Bounded)
		.SetEndLastWrap(EndLastWrap::DeleteLastWord)
		// UIregion
		.SetName("MM_B_T_16x16")
		.SetBGColor(Color(0, 0, 0, 0))
		// Rect
		.SetSizeAcrossPos({ 140,140 });

	MM_t3
		// Button
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetTouchColor(Color::White)
		.SetNormalColor(Color::White)
		// UIregion
		.SetName("MM_B_t3")
		.SetBGColor(Color::White)
		.SetTexture("Button1k1")
		.SetTextureRect(Rect(0, 0, 128, 128))
		.SetRectType(RectType::Rect)
		
		
		// Rect
		.SetSizeAcrossPos({ 140,140 })
		.SetCenter({ 550,350 });
	MM_t3.text
		// UItext
		->SetText(L"30 на 16")
		.SetStyle(sf::Text::Style::Regular)
		.SetTextFillColor(Color(0, 0, 0))
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetFont("Fonts/times.ttf")
		.SetCharacterSize(28)
		.SetAlignment(AlignmentHorizontal::Center)
		.SetAlignment(AlignmentVertical::Center)
		.SetTextRectType(TextRectType::Bounded)
		.SetEndLastWrap(EndLastWrap::DeleteLastWord)
		// UIregion
		.SetName("MM_B_T_32x32")
		.SetBGColor(Color(0, 0, 0, 0))
		// Rect
		.SetSizeAcrossPos({ 140,140 });

	MM_b1
		// Button
		.SetNormalColor(Color::White)
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetTouchColor(Color::White)
		// UIregion
		.SetName("MM_B_b1")
		.SetBGColor(Color::White)
		.SetTexture("Button3k1")
		.SetTextureRect(Rect(0, 0, 128 * 3, 128))
		.SetRectType(RectType::Rect)
		// Rect
		.SetSizeAcrossPos({ 300,100 })
		.SetCenter({ 400,500 });
	MM_b1.text
		// UItext
		->SetText(L"Статистика")
		.SetStyle(sf::Text::Style::Italic)
		.SetTextFillColor(Color(0, 0, 0))
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetFont("Fonts/times.ttf")
		.SetCharacterSize(50)
		.SetAlignment(AlignmentHorizontal::Center)
		.SetAlignment(AlignmentVertical::Center)
		.SetTextRectType(TextRectType::Bounded)
		.SetEndLastWrap(EndLastWrap::DeleteLastWord)
		// UIregion
		.SetName("MM_B_T_stat")
		.SetBGColor(Color(0, 0, 0, 0))
		// Rect
		.SetSizeAcrossPos({ 300,100 });

	MM_b2
		// Button
		.SetNormalColor(Color::White)
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetTouchColor(Color::White)
		// UIregion
		.SetName("MM_B_b2")
		.SetBGColor(Color::White)
		.SetTexture("Button3k1")
		.SetTextureRect(Rect(0, 0, 128 * 3, 128))
		.SetRectType(RectType::Rect)
		// Rect
		.SetSizeAcrossPos({ 300,100 })
		.SetCenter({ 400,500 });
	MM_b2.text
		// UItext
		->SetText(L"Настройки")
		.SetStyle(sf::Text::Style::Italic)
		.SetTextFillColor(Color(0, 0, 0))
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetFont("Fonts/times.ttf")
		.SetCharacterSize(50)
		.SetAlignment(AlignmentHorizontal::Center)
		.SetAlignment(AlignmentVertical::Center)
		.SetTextRectType(TextRectType::Bounded)
		.SetEndLastWrap(EndLastWrap::DeleteLastWord)
		// UIregion
		.SetName("MM_B_T_settings")
		.SetBGColor(Color(0, 0, 0, 0))
		// Rect
		.SetSizeAcrossPos({ 300,100 });

	MM_b3
		// Button
		.SetNormalColor(Color::White)
		.SetHoverColor(Color(0,0,0,25))
		.SetTouchColor(Color::White)
		// UIregion
		.SetName("MM_B_b3")
		.SetBGColor(Color::White)
		.SetTexture("Button3k1")
		.SetTextureRect(Rect(0, 0, 128 * 3, 128))
		.SetRectType(RectType::Rect)
		// Rect
		.SetSizeAcrossPos({ 300,100 })
		.SetCenter({ 400,620 });
	MM_b3.text
		// UItext
		->SetText(L"Выйти")
		.SetStyle(sf::Text::Style::Italic)
		.SetTextFillColor(Color(0, 0, 0))
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetFont("Fonts/times.ttf")
		.SetCharacterSize(50)
		.SetAlignment(AlignmentHorizontal::Center)
		.SetAlignment(AlignmentVertical::Center)
		.SetTextRectType(TextRectType::Bounded)
		.SetEndLastWrap(EndLastWrap::DeleteLastWord)
		// UIregion
		.SetName("MM_B_T_exit")
		.SetBGColor(Color(0, 0, 0, 0))
		// Rect
		.SetSizeAcrossPos({ 300,100 });

	// Game
	Canvas::CreateScene("Game");
	Canvas::SceneSettings("Game", false, false);



	// WinGame
	Canvas::CreateScene("WinGame");
	Canvas::SceneSettings("WinGame", false, false);
	auto& W_bg = Canvas::AddOnScene("WinGame", new UIregion);
	auto& W_t =  Canvas::AddOnScene("WinGame", new UItext);
	auto& W_b1 = Canvas::AddOnScene("WinGame", new Button);
	auto& W_b2 = Canvas::AddOnScene("WinGame", new Button);
	auto& W_hlg = Canvas::AddOnScene("WinGame", new VerticalLayoutGroup);
	auto& W_vlg = Canvas::AddOnScene("WinGame", new VerticalLayoutGroup);

	W_t.SetParent(&W_vlg);
	W_b2.SetParent(&W_vlg);
	W_b1.SetParent(&W_vlg);
	W_vlg.SetParent(&W_bg);
	W_bg.SetParent(&W_hlg);
	W_hlg.SetParent(&Windower::Win);

	W_hlg.connection = LayoutGroup::Connection::Both;
	W_hlg.alignment = LayoutGroup::Alignment::MC;

	W_vlg.connection = LayoutGroup::Connection::Both;
	W_vlg.alignment = LayoutGroup::Alignment::MC;

	W_bg
		// UIregion
		.SetName("E_bg")
		.SetBGColor(Color(125, 125, 125, 230))
		// Rect
		.SetSizeAcrossPos({ 300,350 })
		.SetCenter({ 400,400 });


	W_t
		// UItext
		.SetText(L"Вы выиграли")
		.SetStyle(sf::Text::Style::Bold | sf::Text::Style::Italic)
		.SetTextFillColor(Color(0, 0, 0))
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(3.f)
		.SetFont("Fonts/times.ttf")
		.SetCharacterSize(30)
		.SetAlignment(AlignmentHorizontal::Center)
		.SetAlignment(AlignmentVertical::Center)
		.SetTextRectType(TextRectType::Bounded)
		.SetEndLastWrap(EndLastWrap::DeleteLastWord)
		// UIregion
		.SetName("E_T_Exit")
		.SetBGColor(Color(0, 0, 0, 0))
		// Rect
		.SetSizeAcrossPos({ 200,30 });


	W_b1
		// Button
		.SetNormalColor(Color::Green)
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetTouchColor(Color::Red)
		// UIregion
		.SetName("E_B_b1")
		.SetBGColor(Color::Green)
		.SetRectType(RectType::Rect)
		// Rect
		.SetSizeAcrossPos({ 200,70 });
	W_b1.text
		// UItext
		->SetText(L"Выйти")
		.SetStyle(sf::Text::Style::Regular)
		.SetTextFillColor(Color(0, 0, 0))
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetFont("Fonts/times.ttf")
		.SetCharacterSize(28)
		.SetAlignment(AlignmentHorizontal::Center)
		.SetAlignment(AlignmentVertical::Center)
		.SetTextRectType(TextRectType::Bounded)
		.SetEndLastWrap(EndLastWrap::DeleteLastWord)
		// UIregion
		.SetName("MM_B_T_yes")
		.SetBGColor(Color(0, 0, 0, 0))
		// Rect
		.SetSizeAcrossPos({ 200,70 });


	W_b2
		// Button
		.SetNormalColor(Color::Green)
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetTouchColor(Color::Red)
		// UIregion
		.SetName("E_B_b2")
		.SetBGColor(Color::Green)
		.SetRectType(RectType::Rect)
		// Rect
		.SetSizeAcrossPos({ 200,70 });
	W_b2.text
		// UItext
		->SetText(L"Ещё раз")
		.SetStyle(sf::Text::Style::Regular)
		.SetTextFillColor(Color(0, 0, 0))
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetFont("Fonts/times.ttf")
		.SetCharacterSize(28)
		.SetAlignment(AlignmentHorizontal::Center)
		.SetAlignment(AlignmentVertical::Center)
		.SetTextRectType(TextRectType::Bounded)
		.SetEndLastWrap(EndLastWrap::DeleteLastWord)
		// UIregion
		.SetName("MM_B_T_no")
		.SetBGColor(Color(0, 0, 0, 0))
		// Rect
		.SetSizeAcrossPos({ 200,70 });


	// LoseGame
	Canvas::CreateScene("LoseGame");
	Canvas::SceneSettings("LoseGame", false, false);
	auto& L_bg = Canvas::AddOnScene("LoseGame", new UIregion);
	auto& L_t  = Canvas::AddOnScene("LoseGame", new UItext);
	auto& L_b1 = Canvas::AddOnScene("LoseGame", new Button);
	auto& L_b2 = Canvas::AddOnScene("LoseGame", new Button);
	auto& L_hlg = Canvas::AddOnScene("LoseGame", new VerticalLayoutGroup);
	auto& L_vlg = Canvas::AddOnScene("LoseGame", new VerticalLayoutGroup);

	L_t.SetParent(&L_vlg);
	L_b2.SetParent(&L_vlg);
	L_b1.SetParent(&L_vlg);
	L_vlg.SetParent(&L_bg);
	L_bg.SetParent(&L_hlg);
	L_hlg.SetParent(&Windower::Win);

	L_hlg.connection = LayoutGroup::Connection::Both;
	L_hlg.alignment = LayoutGroup::Alignment::MC;
	
	L_vlg.connection = LayoutGroup::Connection::Both;
	L_vlg.alignment = LayoutGroup::Alignment::MC;

	L_bg
		// UIregion
		.SetName("E_bg")
		.SetBGColor(Color(125, 125, 125, 230))
		// Rect
		.SetSizeAcrossPos({ 300,350 });

	L_t
		// UItext
		.SetText(L"Вы проиграли")
		.SetStyle(sf::Text::Style::Bold | sf::Text::Style::Italic)
		.SetTextFillColor(Color(0, 0, 0))
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(3.f)
		.SetFont("Fonts/times.ttf")
		.SetCharacterSize(30)
		.SetAlignment(AlignmentHorizontal::Center)
		.SetAlignment(AlignmentVertical::Center)
		.SetTextRectType(TextRectType::Bounded)
		.SetEndLastWrap(EndLastWrap::DeleteLastWord)
		// UIregion
		.SetName("E_T_Exit")
		.SetBGColor(Color(0, 0, 0, 0))
		// Rect
		.SetSizeAcrossPos({ 300,30 });

	L_b1
		// Button
		.SetNormalColor(Color::Green)
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetTouchColor(Color::Red)
		// UIregion
		.SetName("E_B_b1")
		.SetBGColor(Color::Green)
		.SetRectType(RectType::Rect)
		// Rect
		.SetSizeAcrossPos({ 200,70 });
	L_b1.text
		// UItext
		->SetText(L"Выйти")
		.SetStyle(sf::Text::Style::Regular)
		.SetTextFillColor(Color(0, 0, 0))
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetFont("Fonts/times.ttf")
		.SetCharacterSize(28)
		.SetAlignment(AlignmentHorizontal::Center)
		.SetAlignment(AlignmentVertical::Center)
		.SetTextRectType(TextRectType::Bounded)
		.SetEndLastWrap(EndLastWrap::DeleteLastWord)
		// UIregion
		.SetName("MM_B_T_yes")
		.SetBGColor(Color(0, 0, 0, 0))
		// Rect
		.SetSizeAcrossPos({ 200,70 });


	L_b2
		// Button
		.SetNormalColor(Color::Green)
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetTouchColor(Color::Red)
		// UIregion
		.SetName("E_B_b2")
		.SetBGColor(Color::Green)
		.SetRectType(RectType::Rect)
		// Rect
		.SetSizeAcrossPos({ 200,70 });
	L_b2.text
		// UItext
		->SetText(L"Ещё раз")
		.SetStyle(sf::Text::Style::Regular)
		.SetTextFillColor(Color(0, 0, 0))
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetFont("Fonts/times.ttf")
		.SetCharacterSize(28)
		.SetAlignment(AlignmentHorizontal::Center)
		.SetAlignment(AlignmentVertical::Center)
		.SetTextRectType(TextRectType::Bounded)
		.SetEndLastWrap(EndLastWrap::DeleteLastWord)
		// UIregion
		.SetName("MM_B_T_no")
		.SetBGColor(Color(0, 0, 0, 0))
		// Rect
		.SetSizeAcrossPos({ 200,70 });


	// Exit
	Canvas::CreateScene("Exit");
	Canvas::SceneSettings("Exit", false, false);
	auto& E_bg = Canvas::AddOnScene("Exit", new UIregion);
	auto& E_t  = Canvas::AddOnScene("Exit", new UItext);
	auto& E_b1 = Canvas::AddOnScene("Exit", new Button);
	auto& E_b2 = Canvas::AddOnScene("Exit", new Button);
	auto& E_b3 = Canvas::AddOnScene("Exit", new Button);
	auto& E_vlg= Canvas::AddOnScene("Exit", new VerticalLayoutGroup);
	auto& E_vlg1= Canvas::AddOnScene("Exit", new VerticalLayoutGroup);

	//ed.Set(&E_hlg);

	E_t.SetParent(&E_vlg1);
	E_b2.SetParent(&E_vlg1);
	E_b3.SetParent(&E_vlg1);
	E_b1.SetParent(&E_vlg1);
	E_vlg1.SetParent(&E_bg);
	E_bg.SetParent(&E_vlg);
	E_vlg.SetParent(&Windower::Win);

	E_vlg.connection = LayoutGroup::Connection::Both;
	E_vlg.alignment = LayoutGroup::Alignment::MC;
	
	E_vlg1.connection = LayoutGroup::Connection::Both;
	E_vlg1.alignment = LayoutGroup::Alignment::MC;

	E_bg
		// UIregion
		.SetName("E_bg")
		.SetBGColor(Color(125, 125, 125, 230))
		// Rect
		.SetSizeAcrossPos({ 300,350 });


	E_t
		// UItext
		.SetText(L"Пауза")
		.SetStyle(sf::Text::Style::Bold | sf::Text::Style::Italic)
		.SetTextFillColor(Color(0, 0, 0))
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(3.f)
		.SetFont("Fonts/times.ttf")
		.SetCharacterSize(30)
		.SetAlignment(AlignmentHorizontal::Center)
		.SetAlignment(AlignmentVertical::Center)
		.SetTextRectType(TextRectType::Bounded)
		.SetEndLastWrap(EndLastWrap::DeleteLastWord)
		// UIregion
		.SetName("E_T_Exit")
		.SetBGColor(Color(0, 0, 0, 0))
		// Rect
		.SetSizeAcrossPos({ 300,30 });
		


	E_b1
		// Button
		.SetNormalColor(Color::White)
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetTouchColor(Color::White)
		// UIregion
		.SetName("E_B_b1")
		.SetBGColor(Color::White)
		.SetTexture("Button3k1")
		.SetTextureRect({ 0,0,0,0 })
		.SetRectType(RectType::Rect)
		// Rect
		.SetSizeAcrossPos({ 200,70 });

	E_b1.text
		// UItext
		->SetText(L"Выйти")
		.SetStyle(sf::Text::Style::Regular)
		.SetTextFillColor(Color(0, 0, 0))
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetFont("Fonts/times.ttf")
		.SetCharacterSize(28)
		.SetAlignment(AlignmentHorizontal::Center)
		.SetAlignment(AlignmentVertical::Center)
		.SetTextRectType(TextRectType::Bounded)
		.SetEndLastWrap(EndLastWrap::DeleteLastWord)
		// UIregion
		.SetName("MM_B_T_yes")
		.SetBGColor(Color(0, 0, 0, 0))
		// Rect
		.SetSizeAcrossPos({ 200,70 });


	E_b2
		// Button
		.SetNormalColor(Color::White)
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetTouchColor(Color::White)
		// UIregion
		.SetName("E_B_b2")
		.SetBGColor(Color::White)
		.SetTexture("Button3k1")
		.SetTextureRect({ 0,0,0,0 })
		.SetRectType(RectType::Rect)
		// Rect
		.SetSizeAcrossPos({ 200,70 });
	E_b2.text
		// UItext
		->SetText(L"Продолжить")
		.SetStyle(sf::Text::Style::Regular)
		.SetTextFillColor(Color(0, 0, 0))
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetFont("Fonts/times.ttf")
		.SetCharacterSize(28)
		.SetAlignment(AlignmentHorizontal::Center)
		.SetAlignment(AlignmentVertical::Center)
		.SetTextRectType(TextRectType::Bounded)
		.SetEndLastWrap(EndLastWrap::DeleteLastWord)
		// UIregion
		.SetName("MM_B_T_no")
		.SetBGColor(Color(0, 0, 0, 0))
		// Rect
		.SetSizeAcrossPos({ 200,70 });

	E_b3
		// Button
		.SetNormalColor(Color::White)
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetTouchColor(Color::White)
		// UIregion
		.SetName("E_B_b2")
		.SetBGColor(Color::White)
		.SetTexture("Button3k1")
		.SetTextureRect({ 0,0,0,0 })
		.SetRectType(RectType::Rect)
		// Rect
		.SetSizeAcrossPos({ 200,70 });
	E_b3.text
		// UItext
		->SetText(L"Заново")
		.SetStyle(sf::Text::Style::Regular)
		.SetTextFillColor(Color(0, 0, 0))
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetFont("Fonts/times.ttf")
		.SetCharacterSize(28)
		.SetAlignment(AlignmentHorizontal::Center)
		.SetAlignment(AlignmentVertical::Center)
		.SetTextRectType(TextRectType::Bounded)
		.SetEndLastWrap(EndLastWrap::DeleteLastWord)
		// UIregion
		.SetName("MM_B_T_no")
		.SetBGColor(Color(0, 0, 0, 0))
		// Rect
		.SetSizeAcrossPos({ 200,70 });


	// Settings
	Canvas::CreateScene("Settings");
	Canvas::SceneSettings("Settings", false, false);
	auto& S_bg = Canvas::AddOnScene("Settings", new UIregion);

	auto& S_t  = Canvas::AddOnScene("Settings", new UItext);
	auto& S_t1 = Canvas::AddOnScene("Settings", new UItext);
	auto& S_t2 = Canvas::AddOnScene("Settings", new UItext);
	auto& S_t3 = Canvas::AddOnScene("Settings", new UItext);
	auto& S_t4 = Canvas::AddOnScene("Settings", new UItext);
	auto& S_t5 = Canvas::AddOnScene("Settings", new UItext);
	auto& S_t6 = Canvas::AddOnScene("Settings", new UItext);

	auto& S_ti1 = Canvas::AddOnScene("Settings", new TextInput);
	auto& S_b1  = Canvas::AddOnScene("Settings", new Toggle);
	auto& S_b2  = Canvas::AddOnScene("Settings", new Toggle);
	auto& S_b3  = Canvas::AddOnScene("Settings", new Toggle);
	auto& S_b4  = Canvas::AddOnScene("Settings", new Toggle);
	auto& S_b5  = Canvas::AddOnScene("Settings", new Toggle);

	auto& S_cntr = Canvas::AddOnScene("Settings", new VerticalLayoutGroup);
	auto& S_grid = Canvas::AddOnScene("Settings", new ColumnGridLayoutGroup);

	S_grid.SetCount(2);
	S_grid.SetPercent(0, 0.85f);
	S_grid.SetPercent(1, 0.15f);
	S_grid.SetCellHeight(60.f);
	S_grid.SetSkipRows(2);

	S_cntr.SetParent(&Windower::Win);
	S_bg.SetParent(&S_cntr);
	S_grid.SetParent(&S_bg);

	S_cntr.alignment = LayoutGroup::MC;
	S_cntr.connection = LayoutGroup::Connection::Both;
	S_grid.alignment = LayoutGroup::ML;
	S_grid.connection = LayoutGroup::Connection::Both;

	S_t1.SetParent(&S_grid);
	S_ti1.SetParent(&S_grid);

	S_t2.SetParent(&S_grid);
	S_b1. SetParent(&S_grid);
	
	S_t3.SetParent(&S_grid);
	S_b2. SetParent(&S_grid);
	
	S_t4.SetParent(&S_grid);
	S_b3. SetParent(&S_grid);
	
	S_t5.SetParent(&S_grid);
	S_b4. SetParent(&S_grid);
	
	S_t6.SetParent(&S_grid);
	S_b5. SetParent(&S_grid);

	S_t.SetParent(&S_bg);
	

	S_ti1
		// UItext
		.SetText(std::to_wstring(Settings::GetFPS_limit()))
		.SetStyle(sf::Text::Style::Bold | sf::Text::Style::Italic)
		.SetTextFillColor(Color(0, 0, 0))
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(3.f)
		.SetFont("Fonts/times.ttf")
		.SetCharacterSize(30)
		.SetAlignment(AlignmentHorizontal::Center)
		.SetAlignment(AlignmentVertical::Center)
		.SetTextRectType(TextRectType::Bounded)
		.SetEndLastWrap(EndLastWrap::DeleteLastWord)
		// UIregion
		.SetName("S_TI1")
		.SetBGColor(Color::White)
		.SetTexture("ToggleOff")
		.SetTextureRect({ 0,0,0,0 })
		.SetRectType(RectType::Rect)
		// Rect
		.SetSizeAcrossPos({ 60,40 });

	S_bg
		// UIregion
		.SetName("S_bg")
		.SetBGColor(Color(125, 125, 125, 230))
		// Rect
		.SetSizeAcrossPos({ 600,700 });

	S_t
		// UItext
		.SetText(L"Настройки")
		.SetStyle(sf::Text::Style::Italic | sf::Text::Style::Bold)
		.SetTextFillColor(Color(0, 0, 0))
		.SetTextOutlineColor(Color(0, 0, 0))
		.SetOutlineThickness(0)
		.SetFont("Fonts/consola.ttf")
		.SetCharacterSize(60)
		.SetAlignment(AlignmentHorizontal::Center)
		.SetAlignment(AlignmentVertical::Center)
		.SetTextRectType(TextRectType::Bounded)
		.SetEndLastWrap(EndLastWrap::DeleteLastWord)
		// UIregion
		.SetName("S_t")
		.SetBGColor(Color(0, 0, 0, 0))
		// Rect
		.SetSizeAcrossPos({ 320,120 })
		.SetLocalPosition({140,0});
	S_t1
		// UItext
		.SetText(L" Ограничение FPS")
		.SetStyle(sf::Text::Style::Italic)
		.SetTextFillColor(Color(0, 0, 0))
		.SetTextOutlineColor(Color(0, 0, 0))
		.SetOutlineThickness(0)
		.SetFont("Fonts/consola.ttf")
		.SetCharacterSize(30)
		.SetAlignment(AlignmentHorizontal::Left)
		.SetAlignment(AlignmentVertical::Center)
		.SetTextRectType(TextRectType::Bounded)
		.SetEndLastWrap(EndLastWrap::DeleteLastWord)
		// UIregion
		.SetName("S_t1")
		.SetBGColor(Color(0, 0, 0, 0))
		// Rect
		.SetSizeAcrossPos({ 500,35 });
	S_t2
		// UItext
		.SetText(L" Вертикальная синхронизация")
		.SetStyle(sf::Text::Style::Italic)
		.SetTextFillColor(Color(0, 0, 0))
		.SetTextOutlineColor(Color(0, 0, 0))
		.SetOutlineThickness(0)
		.SetFont("Fonts/consola.ttf")
		.SetCharacterSize(30)
		.SetAlignment(AlignmentHorizontal::Left)
		.SetAlignment(AlignmentVertical::Center)
		.SetTextRectType(TextRectType::Bounded)
		.SetEndLastWrap(EndLastWrap::DeleteLastWord)
		// UIregion
		.SetName("S_t2")
		.SetBGColor(Color(0, 0, 0, 0))
		// Rect
		.SetSizeAcrossPos({ 500,35 });
	S_t3
		// UItext
		.SetText(L" Ночная тема")
		.SetStyle(sf::Text::Style::Italic)
		.SetTextFillColor(Color(0, 0, 0))
		.SetTextOutlineColor(Color(0, 0, 0))
		.SetOutlineThickness(0)
		.SetFont("Fonts/consola.ttf")
		.SetCharacterSize(30)
		.SetAlignment(AlignmentHorizontal::Left)
		.SetAlignment(AlignmentVertical::Center)
		.SetTextRectType(TextRectType::Bounded)
		.SetEndLastWrap(EndLastWrap::DeleteLastWord)
		// UIregion
		.SetName("S_t3")
		.SetBGColor(Color(0, 0, 0, 0))
		// Rect
		.SetSizeAcrossPos({ 500,35 });
	S_t4
		// UItext
		.SetText(L" Флаг на ЛКМ")
		.SetStyle(sf::Text::Style::Italic)
		.SetTextFillColor(Color(0, 0, 0))
		.SetTextOutlineColor(Color(0, 0, 0))
		.SetOutlineThickness(0)
		.SetFont("Fonts/consola.ttf")
		.SetCharacterSize(30)
		.SetAlignment(AlignmentHorizontal::Left)
		.SetAlignment(AlignmentVertical::Center)
		.SetTextRectType(TextRectType::Bounded)
		.SetEndLastWrap(EndLastWrap::DeleteLastWord)
		// UIregion
		.SetName("S_t4")
		.SetBGColor(Color(0, 0, 0, 0))
		// Rect
		.SetSizeAcrossPos({ 500,35 });
	S_t5
		// UItext
		.SetText(L" Быстрое вскапывание")
		.SetStyle(sf::Text::Style::Italic)
		.SetTextFillColor(Color(0, 0, 0))
		.SetTextOutlineColor(Color(0, 0, 0))
		.SetOutlineThickness(0)
		.SetFont("Fonts/consola.ttf")
		.SetCharacterSize(30)
		.SetAlignment(AlignmentHorizontal::Left)
		.SetAlignment(AlignmentVertical::Center)
		.SetTextRectType(TextRectType::Bounded)
		.SetEndLastWrap(EndLastWrap::DeleteLastWord)
		// UIregion
		.SetName("S_t5")
		.SetBGColor(Color(0, 0, 0, 0))
		// Rect
		.SetSizeAcrossPos({ 500,35 });
	S_t6
		// UItext
		.SetText(L" Быстрая постановка флага")
		.SetStyle(sf::Text::Style::Italic)
		.SetTextFillColor(Color(0, 0, 0))
		.SetTextOutlineColor(Color(0, 0, 0))
		.SetOutlineThickness(0)
		.SetFont("Fonts/consola.ttf")
		.SetCharacterSize(30)
		.SetAlignment(AlignmentHorizontal::Left)
		.SetAlignment(AlignmentVertical::Center)
		.SetTextRectType(TextRectType::Bounded)
		.SetEndLastWrap(EndLastWrap::DeleteLastWord)
		// UIregion
		.SetName("S_t6")
		.SetBGColor(Color(0, 0, 0, 0))
		// Rect
		.SetSizeAcrossPos({ 500,35 });

	S_b1
		// Toggle
		.SetSelectColor(Color::White)
		.SetSelect(Settings::GetVSunc())
		// Button
		.SetNormalColor(Color::White)
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetTouchColor(Color::White)
		// UIregion
		.SetName("S_b1")
		.SetBGColor(Color::White)
		.SetTextureRect(Rect(0, 0, 40, 40))
		.SetRectType(RectType::Rect)
		// Rect
		.SetSizeAcrossPos({ 40,40 })
		.SetGlobalPosition({ 600,200 });
	if (S_b1.GetSelect()) {
		S_b1.SetTexture("ToggleOn");
	}
	else {
		S_b1.SetTexture("ToggleOff");
	}

	S_b2
		// Toggle
		.SetSelectColor(Color::White)
		.SetSelect((bool)Settings::GetTheme())
		// Button
		.SetNormalColor(Color::White)
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetTouchColor(Color::White)
		// UIregion
		.SetName("S_b2")
		.SetBGColor(Color::White)
		.SetTextureRect(Rect(0, 0, 40, 40))
		.SetRectType(RectType::Rect)
		// Rect
		.SetSizeAcrossPos({ 40,40 })
		.SetGlobalPosition({ 600,250 });
	if (S_b2.GetSelect()) {
		S_b2.SetTexture("ToggleOn");
	}
	else {
		S_b2.SetTexture("ToggleOff");
	}

	S_b3
		// Toggle
		.SetSelectColor(Color::White)
		.SetSelect(Settings::GetLeftClickFlag())
		// Button
		.SetNormalColor(Color::White)
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetTouchColor(Color::White)
		// UIregion
		.SetName("S_b3")
		.SetBGColor(Color::White)
		.SetTextureRect(Rect(0, 0, 40, 40))
		.SetRectType(RectType::Rect)
		// Rect
		.SetSizeAcrossPos({ 40,40 })
		.SetGlobalPosition({ 600,300 });
	if (S_b3.GetSelect()) {
		S_b3.SetTexture("ToggleOn");
	}
	else {
		S_b3.SetTexture("ToggleOff");
	}

	S_b4
		// Toggle
		.SetSelectColor(Color::White)
		.SetSelect(Settings::GetEasyDigging())
		// Button
		.SetNormalColor(Color::White)
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetTouchColor(Color::White)
		// UIregion
		.SetName("S_b4")
		.SetBGColor(Color::White)
		.SetTextureRect(Rect(0, 0, 40, 40))
		.SetRectType(RectType::Rect)
		// Rect
		.SetSizeAcrossPos({ 40,40 })
		.SetGlobalPosition({ 600,350 });
	if (S_b4.GetSelect()) {
		S_b4.SetTexture("ToggleOn");
	}
	else {
		S_b4.SetTexture("ToggleOff");
	}

	S_b5
		// Toggle
		.SetSelectColor(Color::White)
		.SetSelect(Settings::GetEasyFlagging())
		// Button
		.SetNormalColor(Color::White)
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetTouchColor(Color::White)
		// UIregion
		.SetName("S_b5")
		.SetBGColor(Color::White)
		.SetTextureRect(Rect(0, 0, 40, 40))
		.SetRectType(RectType::Rect)
		// Rect
		.SetSizeAcrossPos({ 40,40 })
		.SetGlobalPosition({ 600,400 });
	if (S_b5.GetSelect()) {
		S_b5.SetTexture("ToggleOn");
	}
	else {
		S_b5.SetTexture("ToggleOff");
	}

	S_ti1.SetCallbackOnTextEnter([&]() {
		Settings::SetFPS_limit(std::stoi(S_ti1.GetText()));
		});
	S_b1.SetCallbackOnMousePress([](SuperMouse::Key, UIregion* reg)
		{
			if (dynamic_cast<Toggle*>(reg)->GetSelect()) {
				Settings::SetVSunc(true);
				dynamic_cast<Toggle*>(reg)->SetTexture("ToggleOn");
				
			}
			else {
				Settings::SetVSunc(false);
				dynamic_cast<Toggle*>(reg)->SetTexture("ToggleOff");
			}
		});
	S_b2.SetCallbackOnMousePress([](SuperMouse::Key, UIregion* reg) {
		if (dynamic_cast<Toggle*>(reg)->GetSelect()) {
			Settings::SetTheme(Themes::Dark);
			Windower::Win.SetTitlebarColor(Color(125, 125, 125));
			dynamic_cast<Toggle*>(reg)->SetTexture("ToggleOn");
		}
		else {
			Settings::SetTheme(Themes::Light);
			Windower::Win.SetTitlebarColor(Color::White);
			dynamic_cast<Toggle*>(reg)->SetTexture("ToggleOff");
		}
		});
	S_b3.SetCallbackOnMousePress([](SuperMouse::Key, UIregion* reg) {
		if (dynamic_cast<Toggle*>(reg)->GetSelect()) {
			Settings::SetLeftClickFlag(true);
			dynamic_cast<Toggle*>(reg)->SetTexture("ToggleOn");
		}
		else {
			Settings::SetLeftClickFlag(false);
			dynamic_cast<Toggle*>(reg)->SetTexture("ToggleOff");
		}
		});
	S_b4.SetCallbackOnMousePress([](SuperMouse::Key, UIregion* reg) {
		if (dynamic_cast<Toggle*>(reg)->GetSelect()) {
			Settings::SetEasyDigging(true);
			dynamic_cast<Toggle*>(reg)->SetTexture("ToggleOn");
		}
		else {
			Settings::SetEasyDigging(false);
			dynamic_cast<Toggle*>(reg)->SetTexture("ToggleOff");
		}
		});
	S_b5.SetCallbackOnMousePress([](SuperMouse::Key, UIregion* reg) {
		if (dynamic_cast<Toggle*>(reg)->GetSelect()) {
			Settings::SetEasyFlagging(true);
			dynamic_cast<Toggle*>(reg)->SetTexture("ToggleOn");
		}
		else {
			Settings::SetEasyFlagging(false);
			dynamic_cast<Toggle*>(reg)->SetTexture("ToggleOff");
		}
		});

	// main menu
	MM_t1.SetCallbackOnMousePress([](SuperMouse::Key, UIregion*) {
		Game::type = Game::x9x9;
		Canvas::SceneSettings("MainMenu");
		
		Windower::Win.SetSize({ 660,840 });
		Windower::Win.Centering();

		Canvas::SceneSettings("Game", true, true);
		Settings::Where = WHERE::Game;
		Game::Start();

		if (Settings::GetTheme() == Themes::Dark)
			Windower::Win.SetTitlebarColor(Color(89,112,134));
		else
			Windower::Win.SetTitlebarColor(Color(192,193,188));
		});
	MM_t2.SetCallbackOnMousePress([](SuperMouse::Key, UIregion*) {
		Game::type = Game::x16x16;
		Canvas::SceneSettings("MainMenu");

		Windower::Win.SetSize({ 660,840 });
		Windower::Win.Centering();

		Canvas::SceneSettings("Game", true, true);
		Settings::Where = WHERE::Game;
		Game::Start();

		if (Settings::GetTheme() == Themes::Dark)
			Windower::Win.SetTitlebarColor(Color(89, 112, 134));
		else
			Windower::Win.SetTitlebarColor(Color(192, 193, 188));
		});
	MM_t3.SetCallbackOnMousePress([](SuperMouse::Key, UIregion*) {
		Game::type = Game::x30x16;
		Canvas::SceneSettings("MainMenu");

		Windower::Win.SetSize({ 1140,840 });
		Windower::Win.Centering();

		Canvas::SceneSettings("Game", true, true);
		Settings::Where = WHERE::Game;
		Game::Start();

		if (Settings::GetTheme() == Themes::Dark)
			Windower::Win.SetTitlebarColor(Color(89, 112, 134));
		else
			Windower::Win.SetTitlebarColor(Color(192, 193, 188));
		});
	MM_b3.SetCallbackOnMousePress([](SuperMouse::Key, UIregion*)
		{
			//Settings::WriteSettings();
			Windower::Win.rw.close();
		});
	MM_b2.SetCallbackOnMousePress([](SuperMouse::Key, UIregion* reg)
		{
			Canvas::SceneSettings("MainMenu");
			Canvas::SceneSettings("Settings", true, true);
			Settings::Where = WHERE::Settings;
		});
	// lose
	L_b1.SetCallbackOnMousePress([](SuperMouse::Key, UIregion* reg)
		{
			Canvas::DisableAll();
			Game::Close();
			Canvas::SceneSettings("MainMenu", true, true);
			
			Windower::Win.SetSize({ 800,800 });
			Windower::Win.Centering();

			Settings::Where = WHERE::MainMenu;

			if (Settings::GetTheme() == Themes::Dark)
				Windower::Win.SetTitlebarColor(Color(125, 125, 125));
			else
				Windower::Win.SetTitlebarColor(Color::White);
		});
	L_b2.SetCallbackOnMousePress([](SuperMouse::Key, UIregion* reg)
		{
			Canvas::SceneSettings("LoseGame");
			Canvas::SceneSettings("Game", true, true);
			Settings::Where = WHERE::Game;
			Game::Restart();
		});
	// win
	W_b1.SetCallbackOnMousePress([](SuperMouse::Key, UIregion* reg)
		{
			Canvas::DisableAll();
			Game::Close();
			Canvas::SceneSettings("MainMenu", true, true);

			Windower::Win.SetSize({ 800,800 });
			Windower::Win.Centering();

			Settings::Where = WHERE::MainMenu;

			if (Settings::GetTheme() == Themes::Dark)
				Windower::Win.SetTitlebarColor(Color(125, 125, 125));
			else
				Windower::Win.SetTitlebarColor(Color::White);
		});
	W_b2.SetCallbackOnMousePress([](SuperMouse::Key, UIregion* reg)
		{
			Canvas::SceneSettings("WinGame");
			Canvas::SceneSettings("Game", true, true);
			Settings::Where = WHERE::Game;
			Game::Restart();
		});
	// exit
	E_b1.SetCallbackOnMousePress([](SuperMouse::Key, UIregion* reg)
		{
			Canvas::DisableAll();
			Game::Close();
			Canvas::SceneSettings("MainMenu", true, true);

			Windower::Win.SetSize({ 800,800 });
			Windower::Win.Centering();

			Settings::Where = WHERE::MainMenu;

			if (Settings::GetTheme() == Themes::Dark)
				Windower::Win.SetTitlebarColor(Color(125, 125, 125));
			else
				Windower::Win.SetTitlebarColor(Color::White);
		});
	E_b2.SetCallbackOnMousePress([](SuperMouse::Key, UIregion* reg)
		{
			Canvas::SceneSettings("Exit");
			Canvas::SceneSettings("Game", true, true);
			Settings::Where = WHERE::Game;
			//Game::UnPause();
			Button* b = dynamic_cast<Button*>(reg);
			b->SetBGColor(b->GetNormalColor());
		});
	E_b3.SetCallbackOnMousePress([](SuperMouse::Key, UIregion* reg)
		{
			Canvas::SceneSettings("Exit");
			Canvas::SceneSettings("Game", true, true);
			Settings::Where = WHERE::Game;
			Game::Restart();
		});
}
int main() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	Settings::ReadSettings();
	
	sf::Image ico; ico.loadFromFile("Minesweeper.png");
	Windower::Win.Create({800,800}, "Minesweeper", sf::Style::Close, settings);
	if(Settings::GetTheme() == Themes::Dark)
		Windower::Win.SetTitlebarColor(Color(125, 125, 125));
	else
		Windower::Win.SetTitlebarColor(Color::White);
	Windower::Win.rw.setIcon(ico.getSize().x, ico.getSize().y, ico.getPixelsPtr());
	Windower::Win.rw.setVerticalSyncEnabled(Settings::GetVSunc());
	if(!Settings::GetVSunc()) Windower::Win.rw.setFramerateLimit(Settings::GetFPS_limit());
	Windower::Win.AddEventCallback(sf::Event::KeyPressed, __CloseWindow);
	Windower::Win.AddEventCallback(sf::Event::Closed, __CloseWindow);
	SuperMouse::initialize(&Windower::Win.rw);

	const char* lib1{ "Memory.dll" };
	_LoadLibrary(lib1);
	SizeTFunc f4 = (SizeTFunc)_GetProcAddress(lib1, "GetMemory");

	Init();
	
	////////////////////////////////////////////////////////
	sf::Clock clk;
	sf::Time elTime;
	while (Windower::Win.rw.isOpen()) {
		Windower::Win.rw.clear();
		Windower::Win.CheckEvents();

		// Update
		SuperMouse::update();
		Windower::Win.Update();
		Game::Update(elTime.asSeconds()); 

		// Draw
		Canvas::Draw(Windower::Win.rw);
		
		Windower::Win.rw.display();

		elTime = clk.getElapsedTime();
		clk.restart();
		FPS::Add(int(1./elTime.asSeconds()));
	}
	Windower::Win.rw.close();
	return 0;
}


//
//struct Editor : public UIrectangle {
//	Editor(Vector2 const& pos, Vector2 const& size, Color const& col) {
//		SetGlobalPosition(pos);
//		SetSizeAcrossPos(size);
//		SetBGColor(col);
//
//		ddl_regions = new UIdropDownList({ 0,0 }, { 150, 30 }, col >> 1);
//		ddl_regions->SetParent(this);
//		ddl_regions->SetLocalPosition({ 180,20 });
//
//		ddl_scenes = new UIdropDownList({ 0,0 }, { 150, 30 }, col >> 2);
//		ddl_scenes->SetParent(this);
//		ddl_scenes->SetLocalPosition({ 20,20 });
//
//		ddl_regions->SetCallbackOnDDLSelected([&](UItext* t) {ReSelectRegion(t->GetText()); });
//		ddl_scenes->SetCallbackOnDDLSelected([&](UItext* t) {ReSelectScene(t->GetText()); });
//
//		int cnt{ 0 };
//		for (auto lay : Canvas::layers) {
//			std::wstring ws(lay.begin(), lay.end());
//			ddl_scenes->Set(cnt, ws);
//			cnt++;
//		}
//		ddl_scenes->Select(0);
//
//	}
//	void Update() {
//
//		//if (err.m_region && err.m_region->GetType() == "Button")
//		if(err.m_region)
//			UpdateRegionsForUIbutton();
//
//		ClickUpdate();
//		UIrectangle::Update();
//		ddl_regions->Update();
//		ddl_scenes->Update();
//		err.Update();
//
//		for (auto i : regs) {
//			i->Update();
//		}
//	}
//	void Draw(sf::RenderWindow& rw) {
//		UIrectangle::Draw(rw);
//
//		for (auto i : regs) {
//			i->Draw(rw);
//		}
//
//		ddl_regions->Draw(rw);
//		ddl_scenes->Draw(rw);
//		err.Draw(rw);
//	}
//	std::string GetType() {
//		return "Editor";
//	}
//private:
//	void ClickUpdate() {
//		bool dont_handle_clicks{ false };
//		dont_handle_clicks |= (ddl_scenes->ClickUpdate(dont_handle_clicks));
//		dont_handle_clicks |= (ddl_scenes->ClickUpd(dont_handle_clicks));
//		dont_handle_clicks |= (ddl_regions->ClickUpdate(dont_handle_clicks));
//		dont_handle_clicks |= (ddl_regions->ClickUpd(dont_handle_clicks));
//
//		for (auto i : regs) {
//			dont_handle_clicks |= i->ClickUpdate(dont_handle_clicks);
//		}
//
//	}
//	void ReSelectRegion(std::wstring ws) {
//		for (auto i : regs) {
//			delete i;
//		}
//		regs.clear();
//
//		std::string s(ws.begin(), ws.end());  
//		err.Set(UIregion::FindByName(s)); 
//
//		//if(UIregion::FindByName(s)->GetType() == "Button")
//		CreateRegionsForUIbutton();
//	}
//	void UpdateRegionsForUIbutton() {
//		static_cast<UItextInput*>(regs[0])->SetText(std::to_wstring(err.m_region->GetLeft()));
//		static_cast<UItextInput*>(regs[1])->SetText(std::to_wstring(err.m_region->GetUp()));
//	}
//	void CreateRegionsForUIbutton() {
//		UItext* text1 = new UItext;	 // Name		   // string
//		UItext* text2 = new UItext;	 // Pos X		   // float
//		UItext* text3 = new UItext;	 // Pos Y		   // float
//		UItext* text4 = new UItext;	 // Width		   // float
//		UItext* text5 = new UItext;	 // Height		   // float
//		UItext* text6 = new UItext;	 // BG color	   // color
//		UItext* text7 = new UItext;	 // Frame color	   // color
//		UItext* text8 = new UItext;	 // Frame thikness // float
//		UItext* text9 = new UItext;	 // Visible		   // bool
//
//		UItextInput* text_input1 = new UItextInput;	   // string
//		UItextInput* text_input2 = new UItextInput;	   // float
//		UItextInput* text_input3 = new UItextInput;	   // float
//		UItextInput* text_input4 = new UItextInput;	   // float
//		UItextInput* text_input5 = new UItextInput;	   // float
//		UItextInput* text_input6 = new UItextInput;	   // color
//		UItextInput* text_input7 = new UItextInput;	   // color
//		UItextInput* text_input8 = new UItextInput;	   // float
//		Button*    text_input9 = new Button;	   // bool
//
//		// Paranting
//		text1->SetParent(this);
//		text2->SetParent(this);
//		text3->SetParent(this);
//		text4->SetParent(this);
//		text5->SetParent(this);
//		text6->SetParent(this);
//		text7->SetParent(this);
//		text8->SetParent(this);
//		text9->SetParent(this);
//
//		text_input1->SetParent(this);
//		text_input2->SetParent(this);
//		text_input3->SetParent(this);
//		text_input4->SetParent(this);
//		text_input5->SetParent(this);
//		text_input6->SetParent(this);
//		text_input7->SetParent(this);
//		text_input8->SetParent(this);
//		text_input9->SetParent(this);
//
//
//		// Positing
//		text1->SetLocalPosition({20,80 });
//		text2->SetLocalPosition({20,120}); 
//		text3->SetLocalPosition({20,160});
//		text4->SetLocalPosition({20,200});
//		text5->SetLocalPosition({20,240});
//		text6->SetLocalPosition({20,280});
//		text7->SetLocalPosition({20,320});
//		text8->SetLocalPosition({20,360});
//		text9->SetLocalPosition({20,400});
//
//		text_input1->SetLocalPosition({ 150,80  });
//		text_input2->SetLocalPosition({ 150,120 });
//		text_input3->SetLocalPosition({ 150,160 });
//		text_input4->SetLocalPosition({ 150,200 });
//		text_input5->SetLocalPosition({ 150,240 });
//		text_input6->SetLocalPosition({ 150,280 });
//		text_input7->SetLocalPosition({ 150,320 });
//		text_input8->SetLocalPosition({ 150,360 });
//		text_input9->SetLocalPosition({ 150,400 });
//
//		// Resizing
//		text1->SetSizeAcrossPos({120,30});
//		text2->SetSizeAcrossPos({120,30});
//		text3->SetSizeAcrossPos({120,30});
//		text4->SetSizeAcrossPos({120,30});
//		text5->SetSizeAcrossPos({120,30});
//		text6->SetSizeAcrossPos({120,30});
//		text7->SetSizeAcrossPos({120,30});
//		text8->SetSizeAcrossPos({120,30});
//		text9->SetSizeAcrossPos({120,30});
//
//		text_input1->SetSizeAcrossPos({180,30});
//		text_input2->SetSizeAcrossPos({180,30});
//		text_input3->SetSizeAcrossPos({180,30});
//		text_input4->SetSizeAcrossPos({180,30});
//		text_input5->SetSizeAcrossPos({180,30});
//		text_input6->SetSizeAcrossPos({180,30});
//		text_input7->SetSizeAcrossPos({180,30});
//		text_input8->SetSizeAcrossPos({180,30});
//		text_input9->SetSizeAcrossPos({180,30});
//
//		// Naming
//		text1->SetText(L"Name");
//		text2->SetText(L"Pos X");
//		text3->SetText(L"Pos Y");
//		text4->SetText(L"Width");
//		text5->SetText(L"Height");
//		text6->SetText(L"BG color");
//		text7->SetText(L"Frame color");
//		text8->SetText(L"Thikness");
//		text9->SetText(L"Visible");
//
//		// Text settings
//		text1->SetCharacterSize(24);
//		text2->SetCharacterSize(24);
//		text3->SetCharacterSize(24);
//		text4->SetCharacterSize(24);
//		text5->SetCharacterSize(24);
//		text6->SetCharacterSize(24);
//		text7->SetCharacterSize(24);
//		text8->SetCharacterSize(24);
//		text9->SetCharacterSize(24);
//
//		text1->SetAlignment(AlignmentHorizontal::Left);
//		text2->SetAlignment(AlignmentHorizontal::Left);
//		text3->SetAlignment(AlignmentHorizontal::Left);
//		text4->SetAlignment(AlignmentHorizontal::Left);
//		text5->SetAlignment(AlignmentHorizontal::Left);
//		text6->SetAlignment(AlignmentHorizontal::Left);
//		text7->SetAlignment(AlignmentHorizontal::Left);
//		text8->SetAlignment(AlignmentHorizontal::Left);
//		text9->SetAlignment(AlignmentHorizontal::Left);
//
//		text_input1->SetCharacterSize(24);
//		text_input2->SetCharacterSize(24);
//		text_input3->SetCharacterSize(24);
//		text_input4->SetCharacterSize(24);
//		text_input5->SetCharacterSize(24);
//		text_input6->SetCharacterSize(24);
//		text_input7->SetCharacterSize(24);
//		text_input8->SetCharacterSize(24);
//
//		text_input1->SetAlignment(AlignmentHorizontal::Left);
//		text_input2->SetAlignment(AlignmentHorizontal::Left);
//		text_input3->SetAlignment(AlignmentHorizontal::Left);
//		text_input4->SetAlignment(AlignmentHorizontal::Left);
//		text_input5->SetAlignment(AlignmentHorizontal::Left);
//		text_input6->SetAlignment(AlignmentHorizontal::Left);
//		text_input7->SetAlignment(AlignmentHorizontal::Left);
//		text_input8->SetAlignment(AlignmentHorizontal::Left);
//
//
//		// Registrings
//		regs.push_back(text_input1);
//		regs.push_back(text_input2);
//		regs.push_back(text_input3);
//		regs.push_back(text_input4);
//		regs.push_back(text_input5);
//		regs.push_back(text_input6);
//		regs.push_back(text_input7);
//		regs.push_back(text_input8);
//		regs.push_back(text_input9);
//		regs.push_back(text1);
//		regs.push_back(text2);
//		regs.push_back(text3);
//		regs.push_back(text4);
//		regs.push_back(text5);
//		regs.push_back(text6);
//		regs.push_back(text7);
//		regs.push_back(text8);
//		regs.push_back(text9);
//
//		//{
//		//	UItextInput* tx = new UItextInput;
//		//	tx->SetParent(this);
//		//	tx->SetLocalPosition({ 20,80 });
//		//	tx->SetSizeAcrossPos({ 150, 30 });
//		//	tx->SetBGColor(Color(100, 100, 100, 100));
//		//	tx->SetCallbackOnTextUpdated([&]()
//		//		{
//		//			try {
//		//				err.m_region->SetLeftBorder(std::stof(static_cast<UItextInput*>(regs[0])->GetText()));
//		//			}
//		//			catch (std::exception e) {
//		//				std::cout << e.what() << '\n';
//		//			}
//		//		});
//		//	regs.push_back(tx);
//		//}
//		//{
//		//	UItextInput* tx = new UItextInput;
//		//	tx->SetParent(this);
//		//	tx->SetLocalPosition({ 180,80 });
//		//	tx->SetSizeAcrossPos({ 150, 30 });
//		//	tx->SetBGColor(Color(100, 100, 100, 100));
//		//	tx->SetCallbackOnTextUpdated([&]()
//		//		{
//		//			try {
//		//				err.m_region->SetUpBorder(std::stof(static_cast<UItextInput*>(regs[1])->GetText()));
//		//			}
//		//			catch (std::exception e) {
//		//				std::cout << e.what() << '\n';
//		//			}
//		//		});
//		//	regs.push_back(tx);
//		//}
//	}
//
//	void ReSelectScene(std::wstring ws) {
//		for (auto i : regs) {
//			delete i;
//		}
//		regs.clear();
//
//		err.Set(nullptr);
//		ddl_regions->Clear();
//		std::string s(ws.begin(), ws.end());
//		Canvas::DisableAll();
//		Canvas::SceneSettings(s, true);
//		int cnt{ 0 };
//		for (auto i : Canvas::scenes[s].regions) {
//			std::string ss = i->GetName();
//			std::wstring ww(ss.begin(), ss.end());
//			ddl_regions->Set(cnt, ww);
//			cnt++;
//		}
//	}
//
//private:
//	UIdropDownList* ddl_regions,* ddl_scenes;
//	UIeditorRegionRect err;
//	std::vector<UIregion*> regs;
//};
//
///*
//TODO:
//
//	InputInt
//	InputBool
//	InputFloat
//	InputString
//	DropDownList
//	Color
//	Vector
//
//	setcallbackSetter
//	setcalbackGetter
//
//*/
//
//#include "UI/UIeditorRegion.hpp"
//int MainEditor() {
//	//Settings::ReadSettings();
//	//Settings __set;
//	sf::ContextSettings settings;
//	settings.antialiasingLevel = 8;
//
//	//Windower::Win.Create(__set["WindowSizeX"]+400, __set["WindowSizeY"], "Visual controller", sf::Style::Close, settings);
//	//Windower::Win.rw.setVerticalSyncEnabled(__set["VerticalSync"]);
//	//Windower::Win.rw.setFramerateLimit(__set["FramerateLimit"]);
//	Windower::Win.rw.setActive(true);
//	SuperMouse::initialize(&Windower::Win.rw);
//	Windower::Win.AddEventCallback(sf::Event::Closed, __CloseWindow);
//	Windower::Win.AddEventCallback(sf::Event::KeyPressed, __CloseWindow);
//
//	Settings::WinSize = Windower::Win.GetSize();
//	Settings::Center = Settings::WinSize / 2;
//	Canvas::SceneSettings("MainMenu", true);
//
//	
//	//Editor ed({ __set["WindowSizeX"], 0 }, { 400, __set["WindowSizeY"] }, Color(192, 168, 56));
//
//
//	sf::Clock clk;
//	sf::Time elTime;
//	while (Windower::Win.rw.isOpen()) {
//		Windower::Win.rw.clear({ 101, 165, 186 });
//		Windower::Win.CheckEvents();
//		SuperMouse::update();
//		//ed.Update();
//
//		Canvas::Draw(Windower::Win.rw);
//		//ed.Draw(Windower::Win.rw);
//		Windower::Win.rw.display();
//
//		elTime = clk.getElapsedTime();
//		clk.restart();
//		FPS::Add(int(1. / elTime.asSeconds()));
//	}
//	Windower::Win.rw.close();
//
//	return 0;
//}

//int main() {
//#ifdef GAME
//	MainGame();
//#else
//	MainEditor();
//#endif
//}