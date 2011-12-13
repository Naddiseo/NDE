#include <GL/gl.h>
#include <IL/il.h>
#include <IL/ilut.h>
#include "resources/Assets.hpp"

namespace nde {

Assets::Assets() : texture_map() {}

Assets::~Assets() {
	for (intmap_t::value_type& it : texture_map) {
		glDeleteTextures(1, &it.second);
	}
}

} //namespace nde
