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

#include "NDE.hpp"
#include "KeyboardMapSetup.hpp"

BEGIN_MAIN {
	nde::Game& game = nde::Game::getInstance();
	
	nde::World& world = game.getWorld();
	//nde::Assets& assets = nde::Game::getInstance().getAssets();
	//assets.loadMaterial("assets/grass.tga"); // preload this
	//assets.loadMaterial("assets/sky.tga"); // preload this

	nde::Terrain* t = new nde::Terrain(&world); // Scene will delete this
	//nde::SkyBox* s = new nde::SkyBox(&world);
	
	KeyboardMapSetup mapsetup;

	world.getScene().addRenderObjects(t);
	
	game.mainLoop();

	return 0;
}
