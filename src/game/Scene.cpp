#include "game/Scene.hpp"

namespace nde {

Scene::Scene() : sceneMin(1e10f, 1e10f, 1e10f), sceneMax(-1e10f,-1e10f,-1e10f), sceneCenter(), to_render() {
}

Scene::~Scene() {
	for (IsRendered* r : to_render) {
		delete r;
	}
}

bool
Scene::loadScene(const std::string& path) {
	getBoundingBox();

	sceneCenter.x = (sceneMin.x + sceneMax.x) / 2.0f;
	sceneCenter.y = (sceneMin.y + sceneMax.y) / 2.0f;
	sceneCenter.z = (sceneMin.z + sceneMax.z) / 2.0f;

	return true;
}

void
Scene::getBoundingBox() {}



} //namespace nde
