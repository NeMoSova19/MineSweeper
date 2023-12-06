#include "Settings.hpp"
#include "fstream"
#include <nlohmann/json.hpp>
#include "Windower.hpp"
#include "ResourceManager.hpp"

using json = nlohmann::json;

void Settings::ReadSettings()
{
	try {

		std::ifstream f(settings_path);
		json js;
		f >> js;
		f.close();

		LeftClickFlag = js["LeftClickFlag"];
		EasyDigging = js["EasyDigging"];
		EasyFlagging = js["EasyFlagging"];
		FPS_limit = js["FPS_limit"];
		VSunc = js["VSunc"];
		auto& _9x9 = js["_9x9"];
		auto& _16x16 = js["_16x16"];
		auto& _30x16 = js["_30x16"];
		stat_9x9 = { _9x9["win"],_9x9["lose"],_9x9["time"] };
		stat_16x16 = { _16x16["win"],_16x16["lose"],_16x16["time"] };
		stat_30x16 = { _30x16["win"],_30x16["lose"],_30x16["time"] };
		SetTheme(js["Theme"]);
	}
	catch (std::exception const& e) {
		SetTheme(Theme);
	}
}

void Settings::WriteSettings()
{
	json js;
	
	js["LeftClickFlag"] = LeftClickFlag;
	js["EasyDigging"] = EasyDigging;
	js["EasyFlagging"] = EasyFlagging;
	js["FPS_limit"] = FPS_limit;
	js["VSunc"] = VSunc;
	js["Theme"] = Theme;

	js["_9x9"]["win"] = stat_9x9.win;
	js["_9x9"]["lose"] = stat_9x9.lose;
	js["_9x9"]["time"] = stat_9x9.time;

	js["_16x16"]["win"]  = stat_16x16.win;
	js["_16x16"]["lose"] = stat_16x16.lose;
	js["_16x16"]["time"] = stat_16x16.time;

	js["_30x16"]["win"]  = stat_30x16.win;
	js["_30x16"]["lose"] = stat_30x16.lose;
	js["_30x16"]["time"] = stat_30x16.time;

	std::ofstream f(settings_path);
	f << std::setw(4) << js;
	f.close();
}

void Settings::SetLeftClickFlag(bool b)
{
	LeftClickFlag = b;
	WriteSettings();
}

void Settings::SetEasyDigging(bool b)
{
	EasyDigging = b;
	WriteSettings();
}

void Settings::SetEasyFlagging(bool b)
{
	EasyFlagging = b;
	WriteSettings();
}

void Settings::SetFPS_limit(uint16_t u)
{
	FPS_limit = u;
	WriteSettings();
	if(VSunc)
		Windower::Win.rw.setFramerateLimit(0);
	else
		Windower::Win.rw.setFramerateLimit(u);
}

void Settings::SetVSunc(bool b)
{
	VSunc = b;
	WriteSettings();
	Windower::Win.rw.setVerticalSyncEnabled(b);
	if (VSunc)
		Windower::Win.rw.setFramerateLimit(0);
	else
		Windower::Win.rw.setFramerateLimit(FPS_limit);
}



void Settings::SetTheme(Themes t)
{
	if (t == Themes::Dark) {
		ResourceManager::SetTexture("Textures/Tiles_dark.png", "Tiles");
		ResourceManager::SetTexture("Textures/Button1k1_dark.png", "Button1k1");
		ResourceManager::SetTexture("Textures/Button3k1_dark.png", "Button3k1");
		ResourceManager::SetTexture("Textures/ToggleOn_dark.png", "ToggleOn");
		ResourceManager::SetTexture("Textures/ToggleOff_dark.png", "ToggleOff");
		ResourceManager::SetTexture("Textures/numbers_dark.png", "Numbers");
		ResourceManager::SetTexture("Textures/BG9x9_dark.png", "BG9x9");
		ResourceManager::SetTexture("Textures/BG30x16_dark.png", "BG30x16");
		ResourceManager::SetTexture("Textures/MenuBG_dark.png", "MenuBG");
	}
	else {
		ResourceManager::SetTexture("Textures/Tiles_light.png", "Tiles");
		ResourceManager::SetTexture("Textures/Button1k1_light.png", "Button1k1");
		ResourceManager::SetTexture("Textures/Button3k1_light.png", "Button3k1");
		ResourceManager::SetTexture("Textures/ToggleOn_light.png", "ToggleOn");
		ResourceManager::SetTexture("Textures/ToggleOff_light.png", "ToggleOff");
		ResourceManager::SetTexture("Textures/numbers_light.png", "Numbers");
		ResourceManager::SetTexture("Textures/BG9x9_light.png", "BG9x9");
		ResourceManager::SetTexture("Textures/BG30x16_light.png", "BG30x16");
		ResourceManager::SetTexture("Textures/MenuBG_light.png", "MenuBG");
	}
	Theme = t;
	WriteSettings();
}

void Settings::SetStat(Stat s, Game::Type type)
{
	Stat* ss{nullptr};
	switch (type)
	{
	case Game::none:
		return;
	case Game::x9x9:
		ss = &stat_9x9;
		break;
	case Game::x16x16:
		ss = &stat_16x16;
		break;
	case Game::x30x16:
		ss = &stat_30x16;
		break;
	}

	ss->win += s.win;
	ss->lose += s.lose;
	if (s.win) {
		ss->time = std::min(ss->time, s.time);
	}
	WriteSettings();
}

void Settings::ResetStat(Game::Type type)
{
	switch (type)
	{
	case Game::none:
		return;
	case Game::x9x9:
		stat_9x9 = Stat();
		return;
	case Game::x16x16:
		stat_16x16 = Stat();
		return;
	case Game::x30x16:
		stat_30x16 = Stat();
		return;
	}
}


bool Settings::GetLeftClickFlag()
{
	return LeftClickFlag;
}

bool Settings::GetEasyDigging()
{
	return EasyDigging;
}

bool Settings::GetEasyFlagging()
{
	return EasyFlagging;
}

uint16_t Settings::GetFPS_limit()
{
	return FPS_limit;
}

bool Settings::GetVSunc()
{
	return VSunc;
}

Themes Settings::GetTheme()
{
	return Theme;
}

Stat Settings::GetStat(Game::Type type)
{
	switch (type)
	{
	case Game::none:
		return Stat();
	case Game::x9x9:
		return stat_9x9;
	case Game::x16x16:
		return stat_16x16;
	case Game::x30x16:
		return stat_30x16;
	}
}
