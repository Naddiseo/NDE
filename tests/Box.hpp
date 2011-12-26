#pragma once
/*
 * Box.hpp
 *
 *  Created on: 2011-12-25
 *      Author: richard
 */

#include "Entity.hpp"

class Box: public nde::Entity {
public:
	Box(scalar _mass = 3.f, scalar dimension = 0.5f);
	virtual ~Box();

	void init(Vector3f from, Vector3f dir, scalar speed);

	void tick();

	void predraw() {}
	void postdraw() {}


	void onDie();
};

