#include "Canvas.hpp"

void Scene::CreateCanvas(std::string name) {
	scenes[name];
	layers.push_back(name);
}

void Scene::CanvasSettings(std::string name, bool visible, bool updatable) {
	auto& scene = scenes[name];
	scene.isVisible = visible;
	scene.isUpdatable = updatable;
}

void Scene::Update()
{
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
		}
}

void Scene::Draw() {

		for (auto& layer : layers) {
			auto& scene = scenes[layer];
			if (scene.isVisible) {
				for (auto region : scene.regions) {
					region->Draw();
				}
			}
		}
}

void Scene::Clear(std::string name) {
	for (auto u : scenes[name].regions) {
		delete u;
	}
	scenes[name].regions.clear();
}