#pragma once
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Settings
{
public:
	static void ReadSettings();
	static void WriteSettings();

	auto& operator [] (auto param) {
		return settings[param];
	}

private:
	static inline json settings{};
	static inline std::string working_path{"Data/"};
	static inline std::string settings_path{ working_path + "Settings.json"};

	static void CreateCanvases();
	static void SaveCanvases();
};