#pragma once
/*
 * DrawAxis.hpp
 *
 *  Created on: 2011-12-23
 *      Author: richard
 */
#include "game/Entity.hpp"

class DrawAxis : public nde::Entity {
public:
	DrawAxis(nde::World* _world);
	virtual ~DrawAxis();

	virtual void tick();
};

