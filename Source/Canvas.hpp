#pragma once
#include<vector>
#include<map>
#include<string>
#include"UIregion.hpp"


struct Scene {
	struct Canvas {
		std::vector<UIregion*> regions;
		bool isVisible : 1 { false };
		bool isUpdatable : 1 { false };
	};

	static void CreateCanvas(std::string name);
	template<class T> static T& AddOnCanvas(std::string name, T* what) {
		scenes[name].regions.push_back(what);
		return *what;
	}
	static void CanvasSettings(std::string name, bool visible = false, bool updatable = false);
	static void Update();
	static void Draw();
	static void Clear(std::string name);

	static inline std::vector<std::string> layers;
	static inline std::map<std::string, Canvas> scenes;
};