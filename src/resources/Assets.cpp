#include <cstdlib>

#include <GL/gl.h>

#include "resources/Assets.hpp"
#include "resources/Material.hpp"
#include "resources/UVMap.hpp"
#include "game/Entity.hpp"

namespace nde {

Assets::Assets() {}

Assets::~Assets() {

	for (Mesh* m : meshes) {
		delete m;
	}
	for (Material* m : materials) {
		delete m;
	}
	for (std::pair<std::string, Color*> p : colors) {
		delete p.second;
	}
}

bool Assets::init() {
	//set up basic colors
	allocColor("red", 1.f, 0.3f, 0.3f);
	allocColor("green", 0.3f, 1.f, 0.3f);
	allocColor("blue", 0.3f, 0.3f, 1.f);
	allocColor("black", 0.f, 0.f, 0.f);
	allocColor("white", 1.f, 1.f, 1.f);

	return true;
}

GLuint
Assets::loadMaterial(const std::string& path) {
	Material* m = allocMaterial(path);
	return m->image_id;
}

} //namespace nde
