#pragma once
/*
 * Terrain.hpp
 *
 *  Created on: 2011-12-10
 *      Author: richard
 */
#include "resources/ResourceReader.hpp"
#include "graphics/IsRendered.hpp"

namespace nde {

class Terrain : public IsRendered {
public:
	Terrain();
	virtual ~Terrain();

};

} /* namespace nde */
