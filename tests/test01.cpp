/*
 * test01.cpp
 *
 *  Created on: 2011-12-01
 *      Author: richard
 */
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <btBulletDynamicsCommon.h>

#include "NDE.hpp"

BEGIN_MAIN {
	nde::Assets& assets = nde::Game::getInstance().getAssets();
	assets.loadMaterial("assets/grass.tga"); // preload this
	assets.loadMaterial("assets/sky.tga"); // preload this

	//nde::Terrain* t = new nde::Terrain(); // Scene will delete this
	nde::SkyBox* s = new nde::SkyBox();

	/*
	nde::Entity* ball = new nde::Entity();
	btCollisionShape* colShape = new btSphereShape(btScalar(1.));
	ball->setMass(1);
	ball->setOrigin({30, 30, 0});
	ball->addCollisionShape(colShape);
	*/
	
	nde::Game& game = nde::Game::getInstance();
	game.getWorld().getScene().addRenderObjects(s);
	game.mainLoop();

	return 0;
}
