#include <GL/gl.h>

#include "resources/Assets.hpp"
#include "resources/Material.hpp"

namespace nde {

Assets::Assets() : materials(), uvmaps(), models(), meshes(), cameras() {}

Assets::~Assets() {
	for (Material* m : materials) {
		glDeleteTextures(1, &m->image_id);
	}
}

} //namespace nde
