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
	top->add(1, 1, 1);
	top->add(1, 1, -1);
	top->add(-1, 1, -1);
	top->add(-1, 1, 1);
	top->hasTexBox();
	top->textureid =  Game::getInstance().loadAsset("assets/sky.tga");

	Face* bottom = new Face();
	bottom->add(1, -1, -1);
	bottom->add(-1, -1, -1);
	bottom->add(-1, -1, 1);
	bottom->add(1, -1, 1);
	bottom->hasTexBox();
	bottom->textureid =  Game::getInstance().loadAsset("assets/sky.tga");
	bottom->col = Color(255, 255, 255);

	Face* back = new Face();
	back->add(1, -1, -1);
	back->add(1, 1, -1);
	back->add(-1, 1, 1);
	back->add(-1, -1, 1);
	back->hasTexBox();
	back->textureid =  Game::getInstance().loadAsset("assets/sky.tga");

	Face* front = new Face();
	front->add(1, -1, -1);
	front->add(1, 1, -1);
	front->add(1, 1, 1);
	front->add(1, -1, 1);
	front->hasTexBox();
	front->textureid =  Game::getInstance().loadAsset("assets/sky.tga");

	Face* right = new Face();
	right->add(1, -1, 1);
	right->add(-1, -1, 1);
	right->add(-1, 1, 1);
	right->add(1, 1, 1);
	right->hasTexBox();
	right->textureid =  Game::getInstance().loadAsset("assets/sky.tga");

	Face* left = new Face();
	left->add(1, 1, -1);
	left->add(1, -1, -1);
	left->add(-1, -1, -1);
	left->add(-1, 1, -1);
	left->hasTexBox();
	left->textureid =  Game::getInstance().loadAsset("assets/sky.tga");


	faces.push_back(top);
	faces.push_back(bottom);
	faces.push_back(front);
	faces.push_back(back);
	faces.push_back(right);
	faces.push_back(left);

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
