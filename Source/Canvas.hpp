#pragma once
#include<vector>
#include<map>
#include<string>
#include"UI/UIregion.hpp"

struct Canvas {
	struct _Save;

	struct Scene {
		void operator = (_Save s) {
			isVisible = s.isVisible;
			isUpdatable = s.isUpdatable;
		}
		std::vector<UIregion*> regions;
		bool isVisible : 1 { false };
		bool isUpdatable : 1 { false };
		bool AlwaysVisible : 1 {false};
	};
	struct _Save {
		void operator = (Scene s) {
			isVisible = s.isVisible;
			isUpdatable = s.isUpdatable;
		}
		bool isVisible : 1 { false };
		bool isUpdatable : 1 { false };
		std::string name;
	};

	//static json GetJson(std::string name);
	static void CreateScene(std::string name);
	template<class T> static T& AddOnScene(std::string name, T* what) {
		scenes[name].regions.push_back(what);
		return *what;
	}
	static void DeleteFromScene(std::string name, UIregion* what);
	static void SceneOnLayer(std::string name, size_t layer);
	static void SceneSettings(std::string name, bool visible = false, bool updatable = false, bool always_visible = false);
	static void Draw(sf::RenderWindow& rw);
	static void Clear(std::string name);
	static void Save();
	static void LoadSave();
	static void DisableAll();
	static void ForUsedTurnOnlyVisible();
	static void ForUsedTurnOn();


	static inline std::vector<std::string> layers;
	static inline std::string selected_scene{};
	static inline std::map<std::string, Scene> scenes;

	static inline std::vector<_Save> save{};
};