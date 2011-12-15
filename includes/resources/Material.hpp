#pragma once

#include <string>

#include <GL/glu.h>

#include "HasId.hpp"

namespace nde {

class Material : public HasId {
public:
	GLuint image_id;
	
	std::string file;
	Material();
	Material(const std::string& file);

	virtual ~Material();
};

}
