#pragma once
/*
 * SkyBox.hpp
 *
 *  Created on: 2011-12-11
 *      Author: richard
 */
#include "common.hpp"
#include "graphics/Face.hpp"
#include "game/Entity.hpp"

namespace nde {

class SkyBox : public Entity {
public:
	SkyBox();
	virtual ~SkyBox();

	virtual void predraw();
	virtual void postdraw();

};

} /* namespace nde */
