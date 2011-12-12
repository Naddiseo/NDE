#pragma once
/*
 * SkyBox.hpp
 *
 *  Created on: 2011-12-11
 *      Author: richard
 */
#include "common.hpp"
#include "graphics/Face.hpp"

namespace nde {

class SkyBox {
	Face faces[6];
public:
	SkyBox();
	virtual ~SkyBox();
};

} /* namespace nde */
