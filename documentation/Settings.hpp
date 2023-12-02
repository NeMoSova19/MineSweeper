#pragma once
#include "StandartTypes.hpp"


enum class WHERE {
	MainMenu,
	Game,
	WinGame,
	LoseGame,
	Exit,
	Settings
};
enum class Themes {
	Light,
	Dark
};

struct Settings {

	static        void    ReadSettings();
	static        void    WriteSettings();

	static void SetLeftClickFlag(bool b);
	static void SetEasyDigging(bool b);
	static void SetEasyFlagging(bool b);
	static void SetAnimationSpeed(uint8_t u);
	static void SetFPS_limit(uint8_t u);
	static void SetVSunc(bool b);
	static void SetTheme(Themes t);
	//static void SetWhere(WHERE w);

	static bool    GetLeftClickFlag();
	static bool    GetEasyDigging();
	static bool    GetEasyFlagging();
	static uint8_t GetAnimationSpeed();
	static uint8_t GetFPS_limit();
	static bool    GetVSunc();
	static Themes  GetTheme();
	//static WHERE   GetWhere();

	static inline WHERE   Where{ WHERE::MainMenu };

private:
	static inline uint8_t FPS_limit{ 60 };
	static inline bool    VSunc{ false };
	static inline Themes  Theme{ Themes::Light };
	static inline bool    LeftClickFlag{ false };
	static inline bool    EasyDigging{ false };
	static inline bool    EasyFlagging{ false };
	static inline uint8_t AnimationSpeed{ 100 };     // percents

	static inline std::string settings_path{ "Saves/Settings.json" };
};

#define GAME