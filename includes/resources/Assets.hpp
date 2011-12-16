#pragma once

#include <map>
#include <vector>

#include "common.hpp"
#include "resources/Material.hpp"
#include "resources/UVMap.hpp"
#include "resources/Mesh.hpp"
#include "graphics/Color.hpp"


namespace nde {

class Camera;

class Assets {

	std::vector<Material*> materials;
	std::vector<UVMap*> uvmaps;
	std::vector<Mesh*> meshes;
	std::vector<Camera*> cameras;
	std::map<std::string, Color*> colors;

public:
	Assets();
	virtual ~Assets();

	template<typename ...Args>
	Material* allocMaterial(Args&&... params);

	template<typename ...Args>
	UVMap* allocUVMap(Args&&... params);

	template<typename ...Args>
	Mesh* allocMesh(Args&&... params);

	/*template<typename ...Args>
	Camera* allocCamera(Args&&... params);*/

	template<typename ...Args>
	Color* allocColor(Args&&... params);

	GLuint loadMaterial(const std::string& path);

	Color* getColor(std::string name) { return colors[name]; }
	Mesh* getMesh(size_t id) { return meshes[id]; }
};

template<typename ...Args>
Material* Assets::allocMaterial(Args&&... params) {
	Material* ret = new Material(std::forward<Args>(params)...);
	materials.push_back(ret);
	ret->setId(materials.size() - 1);
	return ret;
}

template<typename ...Args>
UVMap* Assets::allocUVMap(Args&&... params) {
	UVMap* ret = new UVMap(std::forward<Args>(params)...);
	uvmaps.push_back(ret);
	ret->setId(uvmaps.size() - 1);
	return ret;
}



template<typename ...Args>
Mesh* Assets::allocMesh(Args&&... params) {
	Mesh* ret = new Mesh(std::forward<Args>(params)...);
	meshes.push_back(ret);
	ret->setId(meshes.size() - 1);
	return ret;
}
/*
 template<typename ...Args>
Camera* Assets::allocCamera(Args&&... params) {
	Camera* ret = new Camera(std::forward<Args>(params)...);
	cameras.push_back(ret);
	return ret;
}*/

template<typename ...Args>
Color* Assets::allocColor(Args&&... params) {
	Color* ret = new Color(std::forward<Args>(params)...);
	if (colors.find(ret->name) != colors.end()) {
		// color already exists with this name
		std::string _name = ret->name; // make a copy
		delete ret;
		ret =  colors[_name];
	}
	else {
		colors[ret->name] = ret; // new color
	}

	return ret;
}

} // namespace nde
