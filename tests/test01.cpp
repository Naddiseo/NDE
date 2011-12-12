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


int main() {
	nde::ResourceReader r();
	nde::Terrain* t = new nde::Terrain(r);

	nde::Game::getInstance().getWorld().getScene().addRenderObject(t);

	nde::Game::getInstance().mainLoop();

	return 0;
}
