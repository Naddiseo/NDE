/*
 * Renderer.cpp
 *
 *  Created on: 2011-12-01
 *      Author: richard
 */
#include <GL/gl.h>
#include <GL/glu.h>
#include "graphics/Renderer.hpp"
#include "game/Settings.hpp"


namespace nde {

Renderer::Renderer() : screen(NULL) {
	int height = Settings::getInstance().get_int("HEIGHT");
	int width = Settings::getInstance().get_int("WIDTH");

	SDL_Init(SDL_INIT_VIDEO);
	screen = SDL_SetVideoMode(width, height, 32, SDL_OPENGL);

	SDL_Flip(screen);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
}

Renderer::~Renderer() {
	SDL_Quit();
}


} /* namespace nde */
