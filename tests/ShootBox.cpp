/*
 * ShootBox.cpp
 *
 *  Created on: 2011-12-25
 *      Author: richard
 */

#include "ShootBox.hpp"
#include "Box.hpp"

ShootBox::ShootBox() {}

ShootBox::~ShootBox() {}

bool ShootBox::init() {
	return true;
}

void ShootBox::shootbox() {
	nde::iBufferObject* buffer = graphics->createBuffer(8, 12);
	Box* box = new Box(world, 3, 1);
}
