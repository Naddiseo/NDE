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
#include "DrawAxis.hpp"
#include "ShootBox.hpp"

BEGIN_MAIN {
	nde::Game& game = nde::Game::getInstance();
	
	nde::World& world = game.getWorld();
	//nde::Assets& assets = nde::Game::getInstance().getAssets();
	//assets.loadMaterial("assets/grass.tga"); // preload this
	//assets.loadMaterial("assets/sky.tga"); // preload this

	nde::Terrain* t = new nde::Terrain(&world); // Scene will delete this
	DrawAxis* axis = new DrawAxis(&world);

	//nde::SkyBox* s = new nde::SkyBox(&world);
	
	KeyboardMapSetup* mapsetup = new KeyboardMapSetup();
	ShootBox* boxShooter = new ShootBox();
	game.addModule(mapsetup);
	game.addModule(boxShooter);

	world.getScene().addRenderObjects(t, axis);
	game.mainLoop();

	return 0;
}
