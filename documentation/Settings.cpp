#include "Settings.hpp"
#include "fstream"
#include <nlohmann/json.hpp>
#include "Windower.hpp"
#include "ResourceManager.hpp"

using json = nlohmann::json;

void Settings::ReadSettings()
{
	std::ifstream f(settings_path);
	json js;
	f >> js;
	f.close();

	LeftClickFlag  = js["LeftClickFlag"];
	EasyDigging    = js["EasyDigging"];
	EasyFlagging   = js["EasyFlagging"];
	AnimationSpeed = js["AnimationSpeed"];
	FPS_limit      = js["FPS_limit"];
	VSunc          = js["VSunc"];
	SetTheme(js["Theme"]);
}

void Settings::WriteSettings()
{
	json js;
	
	js["LeftClickFlag"] = LeftClickFlag;
	js["EasyDigging"] = EasyDigging;
	js["EasyFlagging"] = EasyFlagging;
	js["AnimationSpeed"] = AnimationSpeed;
	js["FPS_limit"] = FPS_limit;
	js["VSunc"] = VSunc;
	js["Theme"] = Theme;

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

void Settings::SetAnimationSpeed(uint8_t u)
{
	AnimationSpeed = u;
	WriteSettings();
}

void Settings::SetFPS_limit(uint8_t u)
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
	}
	Theme = t;
	WriteSettings();
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

uint8_t Settings::GetAnimationSpeed()
{
	return AnimationSpeed;
}

uint8_t Settings::GetFPS_limit()
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
