#pragma once
#include <string>

#include "math/vector.hpp"

namespace nde {

class Scene {
	Vector3f sceneMin, sceneMax, sceneCenter;
public:
	Scene();
	virtual ~Scene();

	Vector3f const&  getMin() const { return sceneMin; }
	Vector3f const&  getMax() const { return sceneMax; }
	Vector3f const&  getCenter() const { return sceneCenter; }

	bool loadScene(std::string const& path);
private:
	void getBoundingBox();
};

} // namespace nde
