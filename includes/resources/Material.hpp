#pragma once

#include <string>

#include <GL/glu.h>

#include "HasId.hpp"

namespace nde {

class Material : public HasId {
	size_t index;
public:
	GLuint image_id;
	
	std::string file;
	Material();
	Material(const std::string& file);
	Material(size_t index, const std::string& file);

	virtual ~Material();

	size_t getIndex() const { return index; }
};

}
