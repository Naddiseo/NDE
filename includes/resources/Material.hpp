#pragma once

#include <string>

#include <GL/glu.h>

namespace nde {

class Material {
public:
	GLuint image_id;
	
	uint32_t id;
	std::string file;
	
	Material(uint32_t id, const std::string& file);
};

}
