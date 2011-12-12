#pragma once
/*
 * TextReader.h
 *
 *  Created on: 2011-11-28
 *      Author: richard
 */
#include <string>
#include "common.hpp"

namespace nde {

class ResourceReader {
	intmap_t texture_map;
public:
	faces_t faces;
	ResourceReader();

	virtual ~ResourceReader();

	void load(std::string filename);
	GLuint loadTexture(std::string name);
};

}
