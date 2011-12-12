#pragma once

#include <map>
#include "common.hpp"

namespace nde
{

class Assets {
	intmap_t texture_map;
public:
	Assets();
	virtual ~Assets();

	GLuint loadTexture(std::string path);
};

} // namespace nde
