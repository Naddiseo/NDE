/*
 * Renderer.cpp
 *
 *  Created on: 2011-12-01
 *      Author: richard
 */
#include <SDL/SDL.h>
#include <IL/il.h>
#include "graphics/Renderer.hpp"
#ifdef USE_OPENGL
#	include "graphics/OpenGL.hpp"
#endif
#include "game/Settings.hpp"
#include "game/Game.hpp"


namespace nde {

Renderer::Renderer() : screen(NULL) {}

bool Renderer::init(GLibrary gl) {
	int height = Settings::getInstance().get_int("HEIGHT");
	int width = Settings::getInstance().get_int("WIDTH");

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) == -1) {
		ERROR(SDL_GetError());
		return false;
	}


	switch (gl) {
#ifdef USE_OPENGL
	case GLibrary::OPENGL:
		screen = SDL_SetVideoMode(width, height, 32, SDL_OPENGL);

		if (screen == NULL) {
			Game::getInstance().setError(SDL_GetError());
			return false;
		}

		graphics = new OpenGL();

		break;
#endif
	default:
		FATAL_ERROR("Unsupported Graphics library");
		break;
	}
	SDL_Flip(screen);

	if (SDL_EnableKeyRepeat(10,10) == -1) {
		ERROR(SDL_GetError());
		return false;
	}

	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION) {
		ERROR("Couldn't find correct devIL version");
		return false;
	}
	// initialize devIL
	ilInit();

	return true;
}

Renderer::~Renderer() {
	delete graphics;

	SDL_Quit();
}


} /* namespace nde */
