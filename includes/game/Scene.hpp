#pragma once
#include <string>

#include "common.hpp"
#include "math/vector.hpp"
#include "graphics/IsRendered.hpp"

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

	void addRenderObject(IsRendered* obj);
private:
	void getBoundingBox();
};

} // namespace nde
