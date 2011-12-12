#pragma once
/*
 * SkyBox.hpp
 *
 *  Created on: 2011-12-11
 *      Author: richard
 */
#include "common.hpp"
#include "graphics/Face.hpp"
#include "graphics/IsRendered.hpp"

namespace nde {

class SkyBox : public IsRendered {
public:
	SkyBox();
	virtual ~SkyBox();
};

} /* namespace nde */
