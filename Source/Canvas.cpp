#include "Canvas.hpp"


//json Canvas::GetJson(std::string name) {
//	auto& scen = scenes[name];
//	json js;
//	js["name"] = name;
//	js["isVisible"] = (bool)scen.isVisible;
//	js["isUpdatable"] = (bool)scen.isUpdatable;
//	js["regions"] = json::array();
//	for (auto i : scen.regions) {
//		js["regions"].push_back(i->GetJson());
//		if (js["regions"].back()["type"] == "UIButton") {
//			Button* uib = dynamic_cast<Button*>(i);
//			js["regions"].push_back(uib->text->GetJson());
//		}
//	}
//	return js;
//}

void Canvas::CreateScene(std::string name) {
	scenes[name];
	layers.push_back(name);
}

void Canvas::DeleteFromScene(std::string name, UIregion* what) {
	auto scene = scenes[name].regions;
	for (size_t i = 0; i < scene.size(); i++)
	{
		if (scene[i] == what) {
			scene.erase(scene.begin() + i);
			return;
		}
	}
}

void Canvas::SceneOnLayer(std::string name, size_t layer) {
	static const size_t npose{ static_cast<size_t>(-1) };
	layer = (layer >= layers.size() ? layers.size() - 1 : layer);

	size_t now{ npose };
	for (size_t i = 0; i < layers.size(); i++)
	{
		if (layers[i] == name) {
			now = i;
			break;
		}
	}
	if (now == npose) return;

	layers.erase(layers.begin() + now);
	layers.insert(layers.begin() + layer, name);
}

void Canvas::SceneSettings(std::string name, bool visible, bool updatable, bool always_visible) {
	auto& scene = scenes[name];
	scene.isVisible = visible;
	scene.isUpdatable = updatable;
	scene.AlwaysVisible = always_visible;
}

void Canvas::Draw(sf::RenderWindow& rw) {
	[]() {
		bool dont_handle_click{ false };
		for (int64_t i = (int64_t)layers.size() - 1; i >= 0; i--)
		{
			auto& scene = scenes[layers[i]];
			if (scene.isUpdatable) {
				for (int64_t j = (int64_t)scene.regions.size() - 1; j >= 0; j--) {
					dont_handle_click |= scene.regions[j]->ClickUpdate(dont_handle_click);
				}
			}
		}
		}();

		for (auto& layer : layers) {
			auto& scene = scenes[layer];
			if (scene.isVisible) {
				for (auto region : scene.regions) {
					region->Update();
				}
			}
			if (scene.isVisible) {
				for (auto region : scene.regions) {
					region->Draw(rw);
				}
			}
		}
}

void Canvas::Clear(std::string name) {
	for (auto u : scenes[name].regions) {
		delete u;
	}
	scenes[name].regions.clear();
}

void Canvas::Save() {
	save.clear();

	for (auto& u : scenes) {
		_Save s;
		s.name = u.first;
		s = u.second;
		save.push_back(s);
	}
}

void Canvas::LoadSave() {
	for (auto& u : save) {
		scenes[u.name] = u;
	}
}

void Canvas::DisableAll() {
	for (auto& u : scenes) {
		if (!u.second.AlwaysVisible)
			u.second.isUpdatable = u.second.isVisible = false;
	}
}

void Canvas::ForUsedTurnOnlyVisible() {
	for (auto& u : scenes) {
		if (!u.second.AlwaysVisible && (u.second.isUpdatable || u.second.isVisible)) u.second.isUpdatable = false;
	}
}

void Canvas::ForUsedTurnOn() {
	for (auto& u : scenes) {
		if (!u.second.AlwaysVisible && (u.second.isUpdatable || u.second.isVisible)) {
			u.second.isUpdatable = true;
			u.second.isVisible = true;
		}
	}
}