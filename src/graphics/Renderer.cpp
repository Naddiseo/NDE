/*
 * Renderer.cpp
 *
 *  Created on: 2011-12-01
 *      Author: richard
 */
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <IL/il.h>
#include "graphics/Renderer.hpp"
#include "game/Settings.hpp"
#include "game/Game.hpp"


namespace nde {

Renderer::Renderer() : screen(NULL) {
	int height = Settings::getInstance().get_int("HEIGHT");
	int width = Settings::getInstance().get_int("WIDTH");

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) == -1) {
		Game::getInstance().setError(SDL_GetError());
		return;
	}
	screen = SDL_SetVideoMode(width, height, 32, SDL_OPENGL);

	if (screen == NULL) {
		Game::getInstance().setError(SDL_GetError());
		return;
	}

	SDL_Flip(screen);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(70, width/height, 1, 35);

	if (SDL_EnableKeyRepeat(10,10) == -1) {
		Game::getInstance().setError(SDL_GetError());
		return;
	}

	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION) {
		// TODO: throw error

	}
	// initialize devIL
	ilInit();


}

Renderer::~Renderer() {
	SDL_Quit();
}


} /* namespace nde */
