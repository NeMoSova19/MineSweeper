#include <string>
#include "SuperMouse.hpp"
#include "Settings.hpp"
#include "UIregion.hpp"
#include "Windower.hpp"
#include "Text.hpp"
#include "Button.hpp"
#include "Toggle.hpp"
#include "LayoutGroup.hpp"
#include "Canvas.hpp"
#include "Minesweeper.hpp"
#include "Time.hpp"
#include <iostream>

void __CloseWindow(sf::Event const e) {
	if (e.type == sf::Event::Closed || (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Key::Escape)) {
		switch (Settings::Where)
		{
		case WHERE::MainMenu:
			if (e.type == sf::Event::Closed)
				Windower::Win.rw.close();
			return;
		case WHERE::Stats:
			Scene::CanvasSettings("Stats");
			Scene::CanvasSettings("MainMenu", true, true);
			Settings::Where = WHERE::MainMenu;
			return;

		case WHERE::Game:
			Scene::CanvasSettings("Game", true, false);
			Scene::CanvasSettings("Exit", true, true);
			Settings::Where = WHERE::Exit;
			return;

		case WHERE::Exit:
			Scene::CanvasSettings("Exit");
			Scene::CanvasSettings("Game", true, true);
			Settings::Where = WHERE::Game;
			return;

		case WHERE::Settings:
			Scene::CanvasSettings("Settings");
			Scene::CanvasSettings("MainMenu", true, true);
			Settings::Where = WHERE::MainMenu;
			return;
		}
	}
}

void Init();

int main() {
	Settings::ReadSettings();
	
	sf::Image ico; ico.loadFromFile("Minesweeper.png");
	Windower::Win.Create({800,800}, "Minesweeper", sf::Style::Close);
	Windower::Win.rw.setIcon(ico.getSize().x, ico.getSize().y, ico.getPixelsPtr());
	Windower::Win.rw.setVerticalSyncEnabled(Settings::GetVSunc());
	Windower::Win.AddEventCallback(sf::Event::KeyPressed, __CloseWindow);
	Windower::Win.AddEventCallback(sf::Event::Closed, __CloseWindow);
	Scene::CreateCanvas("Window");
	Scene::CanvasSettings("Window", true, true);
	Scene::AddOnCanvas("Window", &Windower::Win);
	SuperMouse::Init();
	Time::Init();

	if(!Settings::GetVSunc()) Windower::Win.rw.setFramerateLimit(Settings::GetFPS_limit());

	if(Settings::GetTheme() == Themes::Dark)
		Windower::Win.SetTitlebarColor(Color(125, 125, 125));
	else
		Windower::Win.SetTitlebarColor(Color::White);

	Init();

	////////////////////////////////////////////////////////
	while (Windower::Win.rw.isOpen()) {
		// Update
		UIregion::FindByName<UItext>("S_t8")->SetText(L"fps: " + std::to_wstring(Time::GetFPS()));
		Windower::Win.CheckEvents();
		SuperMouse::Update();
		Game::Update();
		Scene::Update();
	
		// Draw
		Windower::Win.rw.clear();
		Scene::Draw();
		Windower::Win.rw.display();
		Time::Update();
	}

	Windower::Win.rw.close();
	return 0;
}

void Init() {
	// Layer0
	Scene::CreateCanvas("Layer0");
	Scene::CanvasSettings("Layer0", true, true);
	auto& BG_r = Scene::AddOnCanvas("Layer0", new UIregion);

	BG_r
		.SetName("L_r")
		.SetTexture("Textures/BG.png")
		.SetTextureRect({ 0,0,0,0 })
		.SetBGColor(Color(255, 255, 255, 255))
		.SetSizeAcrossPos({ 800,800 })
		.SetGlobalPosition({ 0,0 });

	// MainMenu
	Scene::CreateCanvas("MainMenu");
	Scene::CanvasSettings("MainMenu", true, true);
	auto& MM_bg = Scene::AddOnCanvas("MainMenu", new UIregion); // bg
	auto& MM_t = Scene::AddOnCanvas("MainMenu", new UItext); // text
	auto& MM_t1 = Scene::AddOnCanvas("MainMenu", new Button); // gm
	auto& MM_t2 = Scene::AddOnCanvas("MainMenu", new Button); // gm
	auto& MM_t3 = Scene::AddOnCanvas("MainMenu", new Button); // gm
	auto& MM_b1 = Scene::AddOnCanvas("MainMenu", new Button); // stats
	auto& MM_b2 = Scene::AddOnCanvas("MainMenu", new Button); // settings
	auto& MM_b3 = Scene::AddOnCanvas("MainMenu", new Button); // exit

	auto& MM_vlg1 = Scene::AddOnCanvas("MainMenu", new VerticalLayoutGroup);
	auto& MM_hlg1 = Scene::AddOnCanvas("MainMenu", new HorizontalLayoutGroup);
	auto& MM_vlg2 = Scene::AddOnCanvas("MainMenu", new VerticalLayoutGroup);

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

	MM_bg
		.SetName("MM_bg")
		.SetBGColor(Color(255, 255, 255, 240))
		.SetTexture("MenuBG")
		.SetTextureRect({ 0,0,600,700 })
		.SetSizeAcrossPos({ 600,700 });

	MM_t
		.SetText(L"Сапер")
		.SetStyle(sf::Text::Style::Bold | sf::Text::Style::Italic)
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(3.f)
		.SetCharacterSize(120)
		
		.SetName("MM_T_Saper")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 320,120 });

	MM_t1
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetName("MM_B_t1")
		.SetTexture("Button1k1")
		.SetTextureRect(Rect(0, 0, 128, 128))
		.SetSizeAcrossPos({ 140,140 })
		.SetCenter({ 250,350 });
	MM_t1.text
		->SetText(L"9 на 9")
		.SetStyle(sf::Text::Style::Regular)
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetCharacterSize(28)
		.SetName("MM_B_T_8x8")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 140,140 });

	MM_t2
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetName("MM_B_t2")
		.SetTexture("Button1k1")
		.SetTextureRect(Rect(0, 0, 128, 128))
		.SetSizeAcrossPos({ 140,140 })
		.SetCenter({ 400,350 });
	MM_t2.text
		->SetText(L"16 на 16")
		.SetStyle(sf::Text::Style::Regular)
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetCharacterSize(28)
		.SetName("MM_B_T_16x16")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 140,140 });

	MM_t3
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetName("MM_B_t3")
		.SetTexture("Button1k1")
		.SetTextureRect(Rect(0, 0, 128, 128))
		.SetSizeAcrossPos({ 140,140 })
		.SetCenter({ 550,350 });
	MM_t3.text
		->SetText(L"30 на 16")
		.SetStyle(sf::Text::Style::Regular)
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetCharacterSize(28)
		.SetName("MM_B_T_32x32")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 140,140 });

	MM_b1
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetName("MM_B_b1")
		.SetTexture("Button3k1")
		.SetTextureRect(Rect(0, 0, 128 * 3, 128))
		.SetSizeAcrossPos({ 300,100 })
		.SetCenter({ 400,500 });
	MM_b1.text
		->SetText(L"Статистика")
		.SetStyle(sf::Text::Style::Italic)
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetCharacterSize(50)
		.SetName("MM_B_T_stat")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 300,100 });

	MM_b2
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetName("MM_B_b2")
		.SetTexture("Button3k1")
		.SetTextureRect(Rect(0, 0, 128 * 3, 128))
		.SetSizeAcrossPos({ 300,100 })
		.SetCenter({ 400,500 });
	MM_b2.text
		->SetText(L"Настройки")
		.SetStyle(sf::Text::Style::Italic)
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetCharacterSize(50)
		.SetName("MM_B_T_settings")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 300,100 });

	MM_b3
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetName("MM_B_b3")
		.SetTexture("Button3k1")
		.SetTextureRect(Rect(0, 0, 128 * 3, 128))
		.SetSizeAcrossPos({ 300,100 })
		.SetCenter({ 400,620 });
	MM_b3.text
		->SetText(L"Выйти")
		.SetStyle(sf::Text::Style::Italic)
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetCharacterSize(50)
		.SetName("MM_B_T_exit")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 300,100 });

	// Game
	Scene::CreateCanvas("Game");
	Scene::CanvasSettings("Game", false, false);


	// WinGame
	Scene::CreateCanvas("WinGame");
	Scene::CanvasSettings("WinGame", false, false);
	auto& W_bg = Scene::AddOnCanvas("WinGame", new UIregion);
	auto& W_t = Scene::AddOnCanvas("WinGame", new UItext);
	auto& W_b1 = Scene::AddOnCanvas("WinGame", new Button);
	auto& W_b2 = Scene::AddOnCanvas("WinGame", new Button);
	auto& W_hlg = Scene::AddOnCanvas("WinGame", new VerticalLayoutGroup);
	auto& W_vlg = Scene::AddOnCanvas("WinGame", new VerticalLayoutGroup);

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
		.SetName("E_bg")
		.SetBGColor(Color(255, 255, 255, 200))
		.SetTexture("MenuBG")
		.SetTextureRect({ 0,0,600,700 })
		.SetSizeAcrossPos({ 400,400 });

	W_t
		.SetText(L"Вы выиграли")
		.SetStyle(sf::Text::Style::Bold | sf::Text::Style::Italic)
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(3.f)
		.SetCharacterSize(50)
		.SetName("E_T_Exit")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 400,60 });

	W_b1
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetName("E_B_b1")
		.SetTexture("Button3k1")
		.SetTextureRect(Rect(0, 0, 128 * 3, 128))
		.SetSizeAcrossPos({ 300,100 });
	W_b1.text
		->SetText(L"Выйти")
		.SetStyle(sf::Text::Style::Regular)
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetCharacterSize(50)
		.SetName("MM_B_T_yes")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 300,100 });

	W_b2
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetName("E_B_b2")
		.SetTexture("Button3k1")
		.SetTextureRect(Rect(0, 0, 128 * 3, 128))
		.SetSizeAcrossPos({ 300,100 });
	W_b2.text
		->SetText(L"Ещё раз")
		.SetStyle(sf::Text::Style::Regular)
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetCharacterSize(50)
		.SetName("MM_B_T_no")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 300,100 });

	// LoseGame
	Scene::CreateCanvas("LoseGame");
	Scene::CanvasSettings("LoseGame", false, false);
	auto& L_bg = Scene::AddOnCanvas("LoseGame", new UIregion);
	auto& L_t = Scene::AddOnCanvas("LoseGame", new UItext);
	auto& L_b1 = Scene::AddOnCanvas("LoseGame", new Button);
	auto& L_b2 = Scene::AddOnCanvas("LoseGame", new Button);
	auto& L_hlg = Scene::AddOnCanvas("LoseGame", new VerticalLayoutGroup);
	auto& L_vlg = Scene::AddOnCanvas("LoseGame", new VerticalLayoutGroup);

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
		.SetName("E_bg")
		.SetBGColor(Color(255, 255, 255, 200))
		.SetTexture("MenuBG")
		.SetTextureRect({ 0,0,600,700 })
		.SetSizeAcrossPos({ 400,400 });

	L_t
		.SetText(L"Вы проиграли")
		.SetStyle(sf::Text::Style::Bold | sf::Text::Style::Italic)
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(3.f)
		.SetCharacterSize(50)
		.SetName("E_T_Exit")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 400,60 });

	L_b1
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetName("E_B_b1")
		.SetTexture("Button3k1")
		.SetTextureRect(Rect(0, 0, 128 * 3, 128))
		.SetSizeAcrossPos({ 300,100 });
	L_b1.text
		->SetText(L"Выйти")
		.SetStyle(sf::Text::Style::Regular)
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetCharacterSize(50)
		.SetName("MM_B_T_yes")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 300,100 });

	L_b2
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetName("E_B_b2")
		.SetTexture("Button3k1")
		.SetTextureRect(Rect(0, 0, 128 * 3, 128))
		.SetSizeAcrossPos({ 300,100 });
	L_b2.text
		->SetText(L"Ещё раз")
		.SetStyle(sf::Text::Style::Regular)
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetCharacterSize(50)
		.SetName("MM_B_T_no")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 300,100 });

	// Exit
	Scene::CreateCanvas("Exit");
	Scene::CanvasSettings("Exit", false, false);
	auto& E_bg = Scene::AddOnCanvas("Exit", new UIregion);
	auto& E_t = Scene::AddOnCanvas("Exit", new UItext);
	auto& E_b1 = Scene::AddOnCanvas("Exit", new Button);
	auto& E_b2 = Scene::AddOnCanvas("Exit", new Button);
	auto& E_b3 = Scene::AddOnCanvas("Exit", new Button);
	auto& E_vlg = Scene::AddOnCanvas("Exit", new VerticalLayoutGroup);
	auto& E_vlg1 = Scene::AddOnCanvas("Exit", new VerticalLayoutGroup);

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
		.SetName("E_bg")
		.SetBGColor(Color(255, 255, 255, 200))
		.SetTexture("MenuBG")
		.SetTextureRect({ 0,0,600,700 })
		.SetSizeAcrossPos({ 400,500 });

	E_t
		.SetText(L"Пауза")
		.SetStyle(sf::Text::Style::Bold | sf::Text::Style::Italic)
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(3.f)
		.SetCharacterSize(50)
		.SetName("E_T_Exit")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 400,50 });

	E_b1
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetName("E_B_b1")
		.SetTexture("Button3k1")
		.SetTextureRect({ 0,0,0,0 })
		.SetSizeAcrossPos({ 300,100 });

	E_b1.text
		->SetText(L"Выйти")
		.SetStyle(sf::Text::Style::Regular)
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetCharacterSize(50)
		.SetName("MM_B_T_yes")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 300,100 });

	E_b2
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetName("E_B_b2")
		.SetTexture("Button3k1")
		.SetTextureRect({ 0,0,0,0 })
		.SetSizeAcrossPos({ 300,100 });
	E_b2.text
		->SetText(L"Продолжить")
		.SetStyle(sf::Text::Style::Regular)
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetCharacterSize(50)
		.SetName("MM_B_T_no")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 300,100 });

	E_b3
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetName("E_B_b2")
		.SetTexture("Button3k1")
		.SetTextureRect({ 0,0,0,0 })
		.SetSizeAcrossPos({ 300,100 });
	E_b3.text
		->SetText(L"Заново")
		.SetStyle(sf::Text::Style::Regular)
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetCharacterSize(50)
		.SetName("MM_B_T_no")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 300,100 });

	// Settings
	Scene::CreateCanvas("Settings");
	Scene::CanvasSettings("Settings", false, false);
	auto& S_bg = Scene::AddOnCanvas("Settings", new UIregion);

	auto& S_t = Scene::AddOnCanvas("Settings", new UItext);
	auto& S_t1 = Scene::AddOnCanvas("Settings", new UItext);
	auto& S_t2 = Scene::AddOnCanvas("Settings", new UItext);
	auto& S_t3 = Scene::AddOnCanvas("Settings", new UItext);
	auto& S_t4 = Scene::AddOnCanvas("Settings", new UItext);
	auto& S_t5 = Scene::AddOnCanvas("Settings", new UItext);
	auto& S_t6 = Scene::AddOnCanvas("Settings", new UItext);
	auto& S_t7 = Scene::AddOnCanvas("Settings", new UItext);
	auto& S_t8 = Scene::AddOnCanvas("Settings", new UItext);

	auto& S_ti1 = Scene::AddOnCanvas("Settings", new TextInput);
	auto& S_b1 = Scene::AddOnCanvas("Settings", new Toggle);
	auto& S_b2 = Scene::AddOnCanvas("Settings", new Toggle);
	auto& S_b3 = Scene::AddOnCanvas("Settings", new Toggle);
	auto& S_b4 = Scene::AddOnCanvas("Settings", new Toggle);
	auto& S_b5 = Scene::AddOnCanvas("Settings", new Toggle);

	auto& S_cntr = Scene::AddOnCanvas("Settings", new VerticalLayoutGroup);
	auto& S_grid = Scene::AddOnCanvas("Settings", new ColumnGridLayoutGroup);

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
	S_b1.SetParent(&S_grid);

	S_t3.SetParent(&S_grid);
	S_b2.SetParent(&S_grid);

	S_t4.SetParent(&S_grid);
	S_b3.SetParent(&S_grid);

	S_t5.SetParent(&S_grid);
	S_b4.SetParent(&S_grid);

	S_t6.SetParent(&S_grid);
	S_b5.SetParent(&S_grid);

	S_t.SetParent(&S_bg);
	S_t7.SetParent(&S_bg);


	S_ti1
		.SetTextContent(TextContent::digits)
		.SetText(std::to_wstring(Settings::GetFPS_limit()))
		.SetStyle(sf::Text::Style::Bold | sf::Text::Style::Italic)
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(3.f)
		.SetCharacterSize(30)
		.SetName("S_TI1")
		.SetTexture("ToggleOff")
		.SetTextureRect({ 0,0,0,0 })
		.SetSizeAcrossPos({ 60,40 });

	S_bg
		.SetName("S_bg")
		.SetBGColor(Color(255, 255, 255, 240))
		.SetTexture("MenuBG")
		.SetTextureRect({ 0,0,600,700 })
		.SetSizeAcrossPos({ 600,700 });

	S_t
		.SetText(L"Настройки")
		.SetStyle(sf::Text::Style::Italic | sf::Text::Style::Bold)
		.SetTextOutlineColor(Color(0, 0, 0))
		.SetOutlineThickness(0)
		.SetFont("Fonts/consola.ttf")
		.SetCharacterSize(60)
		.SetName("S_t")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 320,120 })
		.SetLocalPosition({ 140,0 });

	S_t1
		.SetText(L" Ограничение FPS")
		.SetStyle(sf::Text::Style::Italic)
		.SetTextOutlineColor(Color(0, 0, 0))
		.SetOutlineThickness(0)
		.SetFont("Fonts/consola.ttf")
		.SetCharacterSize(30)
		.SetAlignment(AlignmentHorizontal::Left)
		.SetName("S_t1")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 500,35 });

	S_t2
		.SetText(L" Вертикальная синхронизация")
		.SetStyle(sf::Text::Style::Italic)
		.SetTextOutlineColor(Color(0, 0, 0))
		.SetOutlineThickness(0)
		.SetFont("Fonts/consola.ttf")
		.SetCharacterSize(30)
		.SetAlignment(AlignmentHorizontal::Left)
		.SetName("S_t2")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 500,35 });

	S_t3
		.SetText(L" Ночная тема")
		.SetStyle(sf::Text::Style::Italic)
		.SetTextOutlineColor(Color(0, 0, 0))
		.SetOutlineThickness(0)
		.SetFont("Fonts/consola.ttf")
		.SetCharacterSize(30)
		.SetAlignment(AlignmentHorizontal::Left)
		.SetName("S_t3")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 500,35 });

	S_t4
		.SetText(L" Флаг на ЛКМ")
		.SetStyle(sf::Text::Style::Italic)
		.SetTextOutlineColor(Color(0, 0, 0))
		.SetOutlineThickness(0)
		.SetFont("Fonts/consola.ttf")
		.SetCharacterSize(30)
		.SetAlignment(AlignmentHorizontal::Left)
		.SetName("S_t4")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 500,35 });

	S_t5
		.SetText(L" Быстрое вскапывание")
		.SetStyle(sf::Text::Style::Italic)
		.SetTextOutlineColor(Color(0, 0, 0))
		.SetOutlineThickness(0)
		.SetFont("Fonts/consola.ttf")
		.SetCharacterSize(30)
		.SetAlignment(AlignmentHorizontal::Left)
		.SetName("S_t5")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 500,35 });

	S_t6
		.SetText(L" Быстрая постановка флага")
		.SetStyle(sf::Text::Style::Italic)
		.SetTextOutlineColor(Color(0, 0, 0))
		.SetOutlineThickness(0)
		.SetFont("Fonts/consola.ttf")
		.SetCharacterSize(30)
		.SetAlignment(AlignmentHorizontal::Left)
		.SetName("S_t6")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 500,35 });

	S_t7
		.SetText(L"Нажмите ESC для выхода в меню")
		.SetStyle(sf::Text::Style::Italic)
		.SetTextOutlineColor(Color(0, 0, 0))
		.SetOutlineThickness(0)
		.SetFont("Fonts/consola.ttf")
		.SetCharacterSize(20)
		.SetAlignment(AlignmentHorizontal::Left)
		.SetName("S_t7")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 500,35 })
		.SetLocalPosition({ 12,665 });

	S_t8
		.SetText(L"fps:")
		.SetStyle(sf::Text::Style::Italic)
		.SetTextOutlineColor(Color(0, 0, 0))
		.SetOutlineThickness(0)
		.SetFont("Fonts/consola.ttf")
		.SetCharacterSize(30)
		.SetAlignment(AlignmentHorizontal::Left)
		.SetAlignment(AlignmentVertical::Top)
		.SetName("S_t8")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 300,50 })
		.SetLocalPosition({ 0,0 });

	S_b1
		.SetSelectColor(Color::White)
		.SetSelect(Settings::GetVSunc())
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetName("S_b1")
		.SetTextureRect(Rect(0, 0, 40, 40))
		.SetSizeAcrossPos({ 40,40 })
		.SetGlobalPosition({ 600,200 });

	if (S_b1.GetSelect()) {
		S_b1.SetTexture("ToggleOn");
	}
	else {
		S_b1.SetTexture("ToggleOff");
	}

	S_b2
		.SetSelectColor(Color::White)
		.SetSelect((bool)Settings::GetTheme())
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetName("S_b2")
		.SetTextureRect(Rect(0, 0, 40, 40))
		.SetSizeAcrossPos({ 40,40 })
		.SetGlobalPosition({ 600,250 });

	if (S_b2.GetSelect()) {
		S_b2.SetTexture("ToggleOn");
	}
	else {
		S_b2.SetTexture("ToggleOff");
	}

	S_b3
		.SetSelectColor(Color::White)
		.SetSelect(Settings::GetLeftClickFlag())
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetName("S_b3")
		.SetTextureRect(Rect(0, 0, 40, 40))
		.SetSizeAcrossPos({ 40,40 })
		.SetGlobalPosition({ 600,300 });

	if (S_b3.GetSelect()) {
		S_b3.SetTexture("ToggleOn");
	}
	else {
		S_b3.SetTexture("ToggleOff");
	}

	S_b4
		.SetSelectColor(Color::White)
		.SetSelect(Settings::GetEasyDigging())
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetName("S_b4")
		.SetTextureRect(Rect(0, 0, 40, 40))
		.SetSizeAcrossPos({ 40,40 })
		.SetGlobalPosition({ 600,350 });

	if (S_b4.GetSelect()) {
		S_b4.SetTexture("ToggleOn");
	}
	else {
		S_b4.SetTexture("ToggleOff");
	}

	S_b5
		.SetSelectColor(Color::White)
		.SetSelect(Settings::GetEasyFlagging())
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetName("S_b5")
		.SetTextureRect(Rect(0, 0, 40, 40))
		.SetSizeAcrossPos({ 40,40 })
		.SetGlobalPosition({ 600,400 });

	if (S_b5.GetSelect()) {
		S_b5.SetTexture("ToggleOn");
	}
	else {
		S_b5.SetTexture("ToggleOff");
	}


	Scene::CreateCanvas("Stats");
	Scene::CanvasSettings("Stats", false, false);
	auto& Ss_bg = Scene::AddOnCanvas("Stats", new UIregion);

	auto& Ss_t = Scene::AddOnCanvas("Stats", new UItext);
	auto& Ss_t1 = Scene::AddOnCanvas("Stats", new UItext); // Выиграно матчей
	auto& Ss_t2 = Scene::AddOnCanvas("Stats", new UItext); // Проиграно матчей
	auto& Ss_t3 = Scene::AddOnCanvas("Stats", new UItext); // Лучшее время
	auto& Ss_t4 = Scene::AddOnCanvas("Stats", new UItext); // Выиграно матчей (число)
	auto& Ss_t5 = Scene::AddOnCanvas("Stats", new UItext); // Проиграно матчей (число)
	auto& Ss_t6 = Scene::AddOnCanvas("Stats", new UItext); // Лучшее время (число)
	auto& Ss_t7 = Scene::AddOnCanvas("Stats", new UItext);

	auto& Ss_b1 = Scene::AddOnCanvas("Stats", new Toggle); // Режим 9х9
	auto& Ss_b2 = Scene::AddOnCanvas("Stats", new Toggle); // Режим 16х16
	auto& Ss_b3 = Scene::AddOnCanvas("Stats", new Toggle); // Режим 30х16
	auto& Ss_b4 = Scene::AddOnCanvas("Stats", new Button); // Сбросить статистику

	auto& Ss_cntr = Scene::AddOnCanvas("Stats", new VerticalLayoutGroup);
	auto& Ss_hlg = Scene::AddOnCanvas("Stats", new HorizontalLayoutGroup);
	auto& Ss_grid = Scene::AddOnCanvas("Stats", new ColumnGridLayoutGroup);

	auto Ss_toggle_group = new ToggleGroup;
	Ss_b1.SetGroup(Ss_toggle_group);
	Ss_b2.SetGroup(Ss_toggle_group);
	Ss_b3.SetGroup(Ss_toggle_group);


	Ss_grid.SetCount(2);
	Ss_grid.SetPercent(0, 0.85f);
	Ss_grid.SetPercent(1, 0.15f);
	Ss_grid.SetCellHeight(60.f);
	Ss_grid.SetSkipRows(5);

	Ss_cntr.alignment = LayoutGroup::MC;
	Ss_cntr.connection = LayoutGroup::Connection::Both;
	Ss_hlg.alignment = LayoutGroup::MC;
	Ss_hlg.connection = LayoutGroup::Connection::Width;
	Ss_hlg.SetHeight(140);
	Ss_hlg.SetLocalY(130);
	Ss_grid.alignment = LayoutGroup::ML;
	Ss_grid.connection = LayoutGroup::Connection::Both;


	Ss_cntr.SetParent(&Windower::Win);
	Ss_bg.SetParent(&Ss_cntr);
	Ss_t.SetParent(&Ss_bg);
	Ss_hlg.SetParent(&Ss_bg);
	Ss_b1.SetParent(&Ss_hlg);
	Ss_b2.SetParent(&Ss_hlg);
	Ss_b3.SetParent(&Ss_hlg);
	Ss_b4.SetParent(&Ss_bg);
	Ss_grid.SetParent(&Ss_bg);
	Ss_t1.SetParent(&Ss_grid);
	Ss_t4.SetParent(&Ss_grid);
	Ss_t2.SetParent(&Ss_grid);
	Ss_t5.SetParent(&Ss_grid);
	Ss_t3.SetParent(&Ss_grid);
	Ss_t6.SetParent(&Ss_grid);
	Ss_t7.SetParent(&Ss_bg);

	Ss_b1
		.SetSelectColor(Color(127, 255, 127))
		.SetSelect(true)
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetName("Ss_b1")
		.SetBGColor(Color(127, 255, 127))
		.SetTexture("Button1k1")
		.SetTextureRect(Rect(0, 0, 128, 128))
		.SetSizeAcrossPos({ 140,140 });
	Ss_b1.text
		->SetText(L"9 на 9")
		.SetStyle(sf::Text::Style::Regular)
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetCharacterSize(28)
		.SetName("Ss_B_T_8x8")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 140,140 });
	
	Ss_b2
		.SetSelectColor(Color(127, 255, 127))
		.SetSelect(false)
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetName("Ss_b2")
		.SetTexture("Button1k1")
		.SetTextureRect(Rect(0, 0, 128, 128))
		.SetSizeAcrossPos({ 140,140 });
	Ss_b2.text
		->SetText(L"16 на 16")
		.SetStyle(sf::Text::Style::Regular)
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetCharacterSize(28)
		.SetName("Ss_B_T_16x16")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 140,140 });
	
	Ss_b3
		.SetSelectColor(Color(127, 255, 127))
		.SetSelect(false)
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetName("Ss_b3")
		.SetTexture("Button1k1")
		.SetTextureRect(Rect(0, 0, 128, 128))
		.SetSizeAcrossPos({ 140,140 });
	Ss_b3.text
		->SetText(L"30 на 16")
		.SetStyle(sf::Text::Style::Regular)
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetCharacterSize(28)
		.SetName("Ss_B_T_32x32")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 140,140 });

	Ss_b4
		.SetHoverColor(Color(0, 0, 0, 25))
		.SetName("MM_B_b1")
		.SetTexture("Button3k1")
		.SetTextureRect(Rect(0, 0, 128 * 3, 128))
		.SetSizeAcrossPos({ 300,100 })
		.SetLocalPosition({ 150,540 });
	Ss_b4.text
		->SetText(L"Сбросить")
		.SetStyle(sf::Text::Style::Italic)
		.SetTextOutlineColor(Color(126, 200, 14))
		.SetOutlineThickness(2.f)
		.SetCharacterSize(50)
		.SetName("Ss_B_T_reset")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 300,100 });

	Ss_bg
		.SetName("Ss_bg")
		.SetBGColor(Color(255, 255, 255, 240))
		.SetTexture("MenuBG")
		.SetTextureRect({ 0,0,600,700 })
		.SetSizeAcrossPos({ 600,700 });

	Ss_t
		.SetText(L"Статистика")
		.SetStyle(sf::Text::Style::Italic | sf::Text::Style::Bold)
		.SetTextOutlineColor(Color(0, 0, 0))
		.SetOutlineThickness(0)
		.SetFont("Fonts/consola.ttf")
		.SetCharacterSize(60)
		.SetName("Ss_t")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 320,120 })
		.SetLocalPosition({ 140,0 });

	Ss_t1
		.SetText(L" Выиграно матчей")
		.SetStyle(sf::Text::Style::Italic)
		.SetTextOutlineColor(Color(0, 0, 0))
		.SetOutlineThickness(0)
		.SetFont("Fonts/consola.ttf")
		.SetCharacterSize(30)
		.SetAlignment(AlignmentHorizontal::Left)
		.SetName("Ss_t1")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 500,35 });

	Ss_t2
		.SetText(L" Проиграно матчей")
		.SetStyle(sf::Text::Style::Italic)
		.SetTextOutlineColor(Color(0, 0, 0))
		.SetOutlineThickness(0)
		.SetFont("Fonts/consola.ttf")
		.SetCharacterSize(30)
		.SetAlignment(AlignmentHorizontal::Left)
		.SetName("Ss_t2")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 500,35 });

	Ss_t3
		.SetText(L" Лучшее время")
		.SetStyle(sf::Text::Style::Italic)
		.SetTextOutlineColor(Color(0, 0, 0))
		.SetOutlineThickness(0)
		.SetFont("Fonts/consola.ttf")
		.SetCharacterSize(30)
		.SetAlignment(AlignmentHorizontal::Left)
		.SetName("Ss_t3")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 500,35 });

	Ss_t4
		.SetText(L"0")
		.SetStyle(sf::Text::Style::Italic)
		.SetTextOutlineColor(Color(0, 0, 0))
		.SetOutlineThickness(0)
		.SetFont("Fonts/consola.ttf")
		.SetCharacterSize(30)
		.SetAlignment(AlignmentHorizontal::Left)
		.SetName("Ss_t4")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 500,35 });

	Ss_t5
		.SetText(L"0")
		.SetStyle(sf::Text::Style::Italic)
		.SetTextOutlineColor(Color(0, 0, 0))
		.SetOutlineThickness(0)
		.SetFont("Fonts/consola.ttf")
		.SetCharacterSize(30)
		.SetAlignment(AlignmentHorizontal::Left)
		.SetName("Ss_t5")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 500,35 });

	Ss_t6
		.SetText(L"0:0")
		.SetStyle(sf::Text::Style::Italic)
		.SetTextOutlineColor(Color(0, 0, 0))
		.SetOutlineThickness(0)
		.SetFont("Fonts/consola.ttf")
		.SetCharacterSize(30)
		.SetAlignment(AlignmentHorizontal::Left)
		.SetName("Ss_t6")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 500,35 });

	Ss_t7
		.SetText(L"Нажмите ESC для выхода в меню")
		.SetStyle(sf::Text::Style::Italic)
		.SetTextOutlineColor(Color(0, 0, 0))
		.SetOutlineThickness(0)
		.SetFont("Fonts/consola.ttf")
		.SetCharacterSize(20)
		.SetAlignment(AlignmentHorizontal::Left)
		.SetName("Ss_t7")
		.SetBGColor(Color(0, 0, 0, 0))
		.SetSizeAcrossPos({ 500,35 })
		.SetLocalPosition({ 12,665 });


	S_ti1.SetCallbackOnTextOffFocus([&]() {
		Settings::SetFPS_limit(stoi(S_ti1.GetText()));
		});
	S_ti1.SetCallbackOnTextEnter([&]() {
		Settings::SetFPS_limit(stoi(S_ti1.GetText()));
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
	// Stats
	Ss_b1.SetCallbackOnMousePress([&](SuperMouse::Key, UIregion*) {
		Ss_t4.SetText(std::to_wstring(Settings::GetStat(Game::Type::x9x9).win));
		Ss_t5.SetText(std::to_wstring(Settings::GetStat(Game::Type::x9x9).lose));
		size_t t = Settings::GetStat(Game::Type::x9x9).time;
		if (t == INT64_MAX)
			Ss_t6.SetText(L"N/A");
		else {
			Ss_t6.SetText(std::to_wstring(t / 60) + L":" + std::to_wstring(t % 60));
		}
		});
	Ss_b2.SetCallbackOnMousePress([&](SuperMouse::Key, UIregion*) {
		Ss_t4.SetText(std::to_wstring(Settings::GetStat(Game::Type::x16x16).win));
		Ss_t5.SetText(std::to_wstring(Settings::GetStat(Game::Type::x16x16).lose));
		size_t t = Settings::GetStat(Game::Type::x16x16).time;
		if (t == INT64_MAX)
			Ss_t6.SetText(L"N/A");
		else {
			Ss_t6.SetText(std::to_wstring(t / 60) + L":" + std::to_wstring(t % 60));
		}
		});
	Ss_b3.SetCallbackOnMousePress([&](SuperMouse::Key, UIregion*) {
		Ss_t4.SetText(std::to_wstring(Settings::GetStat(Game::Type::x30x16).win));
		Ss_t5.SetText(std::to_wstring(Settings::GetStat(Game::Type::x30x16).lose));
		size_t t = Settings::GetStat(Game::Type::x30x16).time;
		if (t == INT64_MAX)
			Ss_t6.SetText(L"N/A");
		else {
			Ss_t6.SetText(std::to_wstring(t / 60) + L":" + std::to_wstring(t % 60));
		}
		});
	Ss_b4.SetCallbackOnMousePress([&](SuperMouse::Key, UIregion*) {
		Game::Type type = Game::Type(Ss_b1.GetSelect() + Ss_b2.GetSelect() * 2 + Ss_b3.GetSelect() * 3);
		Settings::ResetStat(type);
		Ss_t4.SetText(std::to_wstring(Settings::GetStat(type).win));
		Ss_t5.SetText(std::to_wstring(Settings::GetStat(type).lose));
		size_t t = Settings::GetStat(type).time;
		if (t == INT64_MAX)
			Ss_t6.SetText(L"N/A");
		else {
			Ss_t6.SetText(std::to_wstring(t / 60) + L":" + std::to_wstring(t % 60));
		}
		});
	// main menu
	MM_t1.SetCallbackOnMousePress([](SuperMouse::Key, UIregion*) {
		Game::type = Game::x9x9;
		Scene::CanvasSettings("MainMenu");

		Windower::Win.SetSize({ 660,840 });
		Windower::Win.Centering();

		Scene::CanvasSettings("Game", true, true);
		Settings::Where = WHERE::Game;
		Game::Start();

		if (Settings::GetTheme() == Themes::Dark)
			Windower::Win.SetTitlebarColor(Color(89, 112, 134));
		else
			Windower::Win.SetTitlebarColor(Color(192, 193, 188));
		});
	MM_t2.SetCallbackOnMousePress([](SuperMouse::Key, UIregion*) {
		Game::type = Game::x16x16;
		Scene::CanvasSettings("MainMenu");

		Windower::Win.SetSize({ 660,840 });
		Windower::Win.Centering();

		Scene::CanvasSettings("Game", true, true);
		Settings::Where = WHERE::Game;
		Game::Start();

		if (Settings::GetTheme() == Themes::Dark)
			Windower::Win.SetTitlebarColor(Color(89, 112, 134));
		else
			Windower::Win.SetTitlebarColor(Color(192, 193, 188));
		});
	MM_t3.SetCallbackOnMousePress([](SuperMouse::Key, UIregion*) {
		Game::type = Game::x30x16;
		Scene::CanvasSettings("MainMenu");

		Windower::Win.SetSize({ 1140,840 });
		Windower::Win.Centering();

		Scene::CanvasSettings("Game", true, true);
		Settings::Where = WHERE::Game;
		Game::Start();

		if (Settings::GetTheme() == Themes::Dark)
			Windower::Win.SetTitlebarColor(Color(89, 112, 134));
		else
			Windower::Win.SetTitlebarColor(Color(192, 193, 188));
		});
	MM_b3.SetCallbackOnMousePress([](SuperMouse::Key, UIregion*) // exit
		{
			Windower::Win.rw.close();
		});
	MM_b2.SetCallbackOnMousePress([](SuperMouse::Key, UIregion* reg) // settings
		{
			Scene::CanvasSettings("MainMenu");
			Scene::CanvasSettings("Settings", true, true);
			Settings::Where = WHERE::Settings;
		});
	MM_b1.SetCallbackOnMousePress([&](SuperMouse::Key, UIregion* reg) // stats
		{
			Scene::CanvasSettings("MainMenu");
			Scene::CanvasSettings("Stats", true, true);
			Settings::Where = WHERE::Stats;

			Ss_b1.SetSelect(true);

			Ss_t4.SetText(std::to_wstring(Settings::GetStat(Game::Type::x9x9).win));
			Ss_t5.SetText(std::to_wstring(Settings::GetStat(Game::Type::x9x9).lose));
			size_t t = Settings::GetStat(Game::Type::x9x9).time;
			if (t == INT64_MAX)
				Ss_t6.SetText(L"N/A");
			else {
				Ss_t6.SetText(std::to_wstring(t / 60) + L":" + std::to_wstring(t % 60));
			}
		});
	// lose
	L_b1.SetCallbackOnMousePress([](SuperMouse::Key, UIregion* reg)
		{
			Scene::CanvasSettings("LoseGame");
			Scene::CanvasSettings("Game");
			Game::Close();
			Scene::CanvasSettings("MainMenu", true, true);

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
			Scene::CanvasSettings("LoseGame");
			Scene::CanvasSettings("Game", true, true);
			Settings::Where = WHERE::Game;
			Game::Restart();
		});
	// win
	W_b1.SetCallbackOnMousePress([](SuperMouse::Key, UIregion* reg)
		{
			Scene::CanvasSettings("WinGame");
			Scene::CanvasSettings("Game");
			Game::Close();
			Scene::CanvasSettings("MainMenu", true, true);

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
			Scene::CanvasSettings("WinGame");
			Scene::CanvasSettings("Game", true, true);
			Settings::Where = WHERE::Game;
			Game::Restart();
		});
	// exit
	E_b1.SetCallbackOnMousePress([](SuperMouse::Key, UIregion* reg)
		{
			Scene::CanvasSettings("Game");
			Scene::CanvasSettings("Exit");
			Game::Close();
			Scene::CanvasSettings("MainMenu", true, true);

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
			Scene::CanvasSettings("Exit");
			Scene::CanvasSettings("Game", true, true);
			Settings::Where = WHERE::Game;
			Button* b = dynamic_cast<Button*>(reg);
			b->SetBGColor(b->GetNormalColor());
		});
	E_b3.SetCallbackOnMousePress([](SuperMouse::Key, UIregion* reg)
		{
			Scene::CanvasSettings("Exit");
			Scene::CanvasSettings("Game", true, true);
			Settings::Where = WHERE::Game;
			Game::Restart();
		});
}