#pragma once
#include <string>
#include <assimp/aiScene.h>

#include "math/vector.hpp"

namespace nde {

class Scene {
	const aiScene* scene;
	Vector3f sceneMin, sceneMax, sceneCenter;
public:
	Scene();
	virtual ~Scene();

	const aiScene* getScene() { return scene; }
	Vector3f const&  getMin() const { return sceneMin; }
	Vector3f const&  getMax() const { return sceneMax; }
	Vector3f const&  getCenter() const { return sceneCenter; }

	bool loadScene(std::string const& path);
private:
	void getBoundingBox();
	void getBoundingBoxForNode(const aiNode* nd, aiMatrix4x4* trafo);
};

} // namespace nde
