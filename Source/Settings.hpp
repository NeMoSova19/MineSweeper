#pragma once
#include "StandartTypes.hpp"
#include "Minesweeper.hpp"


enum class WHERE {
	MainMenu,
	Game,
	WinGame,
	LoseGame,
	Exit,
	Settings,
	Stats
};
enum class Themes {
	Light,
	Dark
};
struct Stat {
	size_t win{ 0 }, lose{ 0 }, time{ INT64_MAX };
};

struct Settings abstract {

	static        void    ReadSettings();
	static        void    WriteSettings();

	static void SetLeftClickFlag(bool b);
	static void SetEasyDigging(bool b);
	static void SetEasyFlagging(bool b);
	static void SetFPS_limit(uint16_t u);
	static void SetVSunc(bool b);
	static void SetTheme(Themes t);
	static void SetStat(Stat s, Game::Type type);
	static void ResetStat(Game::Type type);

	static bool    GetLeftClickFlag();
	static bool    GetEasyDigging();
	static bool    GetEasyFlagging();
	static uint16_t GetFPS_limit();
	static bool    GetVSunc();
	static Themes  GetTheme();
	static Stat	   GetStat(Game::Type type);

	static inline WHERE   Where{ WHERE::MainMenu };

private:
	static inline uint16_t FPS_limit{ 60 };
	static inline bool    VSunc{ false };
	static inline Themes  Theme{ Themes::Light };
	static inline bool    LeftClickFlag{ false };
	static inline bool    EasyDigging{ false };
	static inline bool    EasyFlagging{ false };
	static inline Stat    stat_9x9{}, stat_16x16{}, stat_30x16{};


	static inline std::string settings_path{ "Saves/Settings.json" };
};

#define GAME