#include <GL/gl.h>

#include "resources/Assets.hpp"
#include "resources/Material.hpp"
#include "resources/UVMap.hpp"
#include "game/Entity.hpp"

namespace nde {

Assets::Assets() : materials(), uvmaps(), entities(), meshes(), cameras(), colors() {}

Assets::~Assets() {
	for (Entity* e : entities) {
		delete e;
	}
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

GLuint
Assets::loadMaterial(const std::string& path) {
	Material* m = allocMaterial(path);
	return m->image_id;
}


} //namespace nde
