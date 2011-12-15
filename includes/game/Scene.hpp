#pragma once
#include <string>

#include "common.hpp"
#include "math/vector.hpp"
#include "game/Entity.hpp"

namespace nde {

class Scene {
	Vector3f sceneMin, sceneMax, sceneCenter;

	rendered_list_t to_render;
public:
	Scene();
	virtual ~Scene();

	Vector3f const&  getMin() const { return sceneMin; }
	Vector3f const&  getMax() const { return sceneMax; }
	Vector3f const&  getCenter() const { return sceneCenter; }

	bool loadScene(std::string const& path);
	rendered_list_t& getToRender() { return to_render; }

	template<typename H = Entity*>
	void addRenderObjects(const H& obj);

	template<typename H = Entity*, typename... T>
	void addRenderObjects(const H& obj, const T&... tail);

private:
	void getBoundingBox();
};

template<typename H>
void Scene::addRenderObjects(const H& obj) {
	to_render.push_back(obj);
}

template<typename H, typename... T>
void Scene::addRenderObjects(const H& obj, const T&... tail) {
	addRenderObjects(obj);
	addRenderObjects(tail...);
}

} // namespace nde
