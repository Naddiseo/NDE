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
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) == -1) {
		NDE_ERROR(SDL_GetError());
		return false;
	}
	
	switch (gl) {
#ifdef USE_OPENGL
	case GLibrary::OPENGL: {
		Settings& settings = Settings::getInstance();
		
		int height = settings["HEIGHT"];
		int width = settings["WIDTH"];
	
		screen = SDL_SetVideoMode(width, height, 32, SDL_OPENGL);

		if (screen == NULL) {
			Game::getInstance().setError(SDL_GetError());
			return false;
		}

		graphics = new OpenGL();

		break;
	}
#endif
	default:
		NDE_FATAL_ERROR("Unsupported Graphics library");
		break;
	}
	SDL_Flip(screen);

	if (SDL_EnableKeyRepeat(100, 100) == -1) {
		NDE_ERROR(SDL_GetError());
		return false;
	}

	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION) {
		NDE_ERROR("Couldn't find correct devIL version");
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
