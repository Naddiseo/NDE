#pragma once

#include <map>
#include <vector>

#include "common.hpp"

namespace nde {

class Material;
class UVMap;
class Entity;
class Mesh;
class Camera;

class Assets {

	std::vector<Material*> materials;
	std::vector<UVMap*> uvmaps;
	std::vector<Entity*> entities;
	std::vector<Mesh*> meshes;
	std::vector<Camera*> cameras;

public:
	Assets();
	virtual ~Assets();

	template<typename ...Args>
	Material* allocMaterial(Args&&... params);

	template<typename ...Args>
	UVMap* allocUVMap(Args&&... params);

	template<typename ...Args>
	Entity* allocEntity(Args&&... params);

	template<typename ...Args>
	Mesh* allocMesh(Args&&... params);

	/*template<typename ...Args>
	Camera* allocCamera(Args&&... params);*/

	GLuint loadMaterial(const std::string& path);
};

template<typename ...Args>
Material* Assets::allocMaterial(Args&&... params) {
	Material* ret = new Material(std::forward<Args>(params)...);
	materials.push_back(ret);
	return ret;
}

template<typename ...Args>
UVMap* Assets::allocUVMap(Args&&... params) {
	UVMap* ret = new UVMap(std::forward<Args>(params)...);
	uvmaps.push_back(ret);
	return ret;
}

template<typename ...Args>
Entity* Assets::allocEntity(Args&&... params) {
	Entity* ret = new Entity(std::forward<Args>(params)...);
	entities.push_back(ret);
	return ret;
}

template<typename ...Args>
Mesh* Assets::allocMesh(Args&&... params) {
	Mesh* ret = new Mesh(std::forward<Args>(params)...);
	meshes.push_back(ret);
	return ret;
}
/*
 template<typename ...Args>
Camera* Assets::allocCamera(Args&&... params) {
	Camera* ret = new Camera(std::forward<Args>(params)...);
	cameras.push_back(ret);
	return ret;
}*/

} // namespace nde
