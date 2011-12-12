#pragma once
/*
 * Terrain.hpp
 *
 *  Created on: 2011-12-10
 *      Author: richard
 */
#include "ResourceReader.hpp"

namespace nde {

class Terrain {
public:
	Terrain(ResourceReader resources);
	virtual ~Terrain();

	faces_t faces;
};

} /* namespace nde */
