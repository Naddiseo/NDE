#pragma once

#include <string>

#include <GL/glu.h>

namespace nde
{

class Material
{
	GLuint image_id;
	
public:
	uint32_t id;
	std::string file;
	
	Material(uint32_t id, const std::string& file);
};

}
