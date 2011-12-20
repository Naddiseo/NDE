#include <algorithm>
#include "game/Scene.hpp"

namespace nde {

Scene::Scene() : sceneMin(1e10f, 1e10f, 1e10f), sceneMax(-1e10f,-1e10f,-1e10f), sceneCenter() {
}

Scene::~Scene() {
	// assests owns the pointers in to_render
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

void
Scene::removeRenderObject(const Entity* obj) {
	rendered_list_t::iterator it = std::find_if(to_render.begin(), to_render.end(), [&obj](Entity* other){ return other == obj; });
	to_render.erase(it);
}



} //namespace nde
