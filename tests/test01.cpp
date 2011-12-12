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


BEGIN_MAIN {
	nde::Terrain* t = new nde::Terrain(); // Scene will delete this
	nde::SkyBox* s = new nde::SkyBox();

	nde::Game::getInstance().loadAsset("assets/grass.tga");

	nde::Game::getInstance().getWorld().getScene().addRenderObjects(t, s);

	nde::Game::getInstance().mainLoop();

	return 0;
}
