#include "Settings.hpp"
#include <fstream>
#include <iostream>
#include "UI/Uiobjects.hpp"
#include "UI/Toggle.hpp"

void Settings::ReadSettings()
{
	std::ifstream f(settings_path);

	f >> settings;

	f.close();

	CreateCanvases();


}



void Settings::WriteSettings()
{
	SaveCanvases();

	std::ofstream f(settings_path);

	f << std::setw(4) << settings;

	f.close();

}

void Settings::CreateCanvases()
{
	for (auto& i : settings["Canvas"]) {
		std::string name = i;
		Canvas::CreateScene(name);

		json js;
		std::ifstream f(working_path + "Canvas_" + name + ".json");
		f >> js;
		f.close();

		Canvas::SceneSettings(name, js["isVisible"], js["isUpdatable"]);

		for (auto& reg : js["regions"]) {
			std::string type = reg["type"];
			
			UIregion* obj;
			if (type == "UIregion") {
				obj = new UIregion;
				goto CC_OK;
			}
			if (type == "UIbutton") {
				obj = new Button;
				goto CC_OK;
			}
			if (type == "Toggle") {
				obj = new Toggle;
				goto CC_OK;
			}
			if (type == "UItext") {
				obj = new UItext;
				goto CC_OK;
			}
			std::cout << "Escape: " << type << '\n';
			continue;

		CC_OK:
			//std::cout << "Add on " << name << " " << type << '\n';
			obj->SetJson(reg);
			Canvas::AddOnScene(name, obj);
		}

	}

	for (auto& i : settings["Canvas"]) {
		std::string name = i;

		json js;
		std::ifstream f(working_path + "Canvas_" + name + ".json");
		f >> js;
		f.close();

		for (auto& reg : js["regions"]) {
			std::string type = reg["type"];
			std::string reg_name = reg["name"];
			UIregion* obj = UIregion::FindByName<UIregion>(reg_name);
			obj->PostSetJson(reg);
		}

	}
}

void Settings::SaveCanvases()
{
	settings["Canvas"].clear();
	for (auto lay : Canvas::layers) {
		settings["Canvas"].push_back(lay);

		std::ofstream f(working_path+"Canvas_"+lay+".json");

		f << std::setw(4) << Canvas::GetJson(lay);

		f.close();
	}
}
