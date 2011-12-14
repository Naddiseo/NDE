/*
 * SkyBox.cpp
 *
 *  Created on: 2011-12-11
 *      Author: richard
 */

#include "graphics/SkyBox.hpp"
#include "game/Game.hpp"

namespace nde {

SkyBox::SkyBox() {
	// top face
	Face* top = new Face();
	top->add(mesh.add(1, 1, 1));
	top->add(mesh.add(1, 1, -1));
	top->add(mesh.add(-1, 1, -1));
	top->add(mesh.add(-1, 1, 1));
	top->col = Color(255, 255, 255);

	Face* bottom = new Face();
	bottom->add(mesh.add(1, -1, 1));
	bottom->add(mesh.add(1, -1, -1));
	bottom->add(mesh.add(-1, -1, -1));
	bottom->add(mesh.add(-1, -1, 1));
	bottom->col = Color(255, 255, 255);

	Face* back = new Face();
	back->add(mesh.add(-1, -1, -1));
	back->add(mesh.add(-1, 1, -1));
	back->add(mesh.add(-1, 1, 1));
	back->add(mesh.add(-1, -1, 1));
	back->col = Color(255, 255, 255);

	Face* front = new Face();
	front->add(mesh.add(1, 1, 1));
	front->add(mesh.add(1, -1, 1));
	front->add(mesh.add(1, -1, -1));
	front->add(mesh.add(1, 1, -1));
	front->col = Color(255, 255, 255);

	Face* right = new Face();
	right->add(mesh.add(1, -1, 1));
	right->add(mesh.add(-1, -1, 1));
	right->add(mesh.add(-1, 1, 1));
	right->add(mesh.add(1, 1, 1));
	right->col = Color(255, 255, 255);

	Face* left = new Face();
	left->add(mesh.add(1, 1, -1));
	left->add(mesh.add(1, -1, -1));
	left->add(mesh.add(-1, -1, -1));
	left->add(mesh.add(-1, 1, -1));
	left->col = Color(255, 255, 255);

	mesh.addFaces(top, bottom, front, back, right, left);

	mass = 0.f; // We're a static body

}

SkyBox::~SkyBox() {}

void SkyBox::predraw() {
	glPushMatrix();
	glScalef(50, 50, 50);
	glTranslated(0, 0, 0);
}
void SkyBox::postdraw() {
	glPopMatrix();
}

} /* namespace nde */
