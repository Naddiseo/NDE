#pragma once
/*
 * Box.hpp
 *
 *  Created on: 2011-12-25
 *      Author: richard
 */

#include "game/Entity.hpp"

class Box: public nde::Entity {
	scalar dimension;
public:
	Box(nde::World* _world, scalar _mass = 3.f, scalar dimension = 0.5f);
	virtual ~Box();

	void init(Vector3f from, Vector3f dir, scalar speed, nde::iBufferObject* buffer);

	void tick();

	void predraw();
	void postdraw();


	void onDie();
};

