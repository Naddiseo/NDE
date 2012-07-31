
#include <SDL/SDL.h>
#include <IL/il.h>
#include "common.hpp"
#include "graphics/Renderer.hpp"
#ifdef USE_OPENGL
#	include "graphics/OpenGL.hpp"
#endif
#include "game/Game.hpp"
#include "game/Settings.hpp"

namespace nde {

Renderer::Renderer() : screen(nullptr), graphics(nullptr) {}

Renderer::~Renderer() {
	if (graphics) {
		delete graphics;
	}
	SDL_Quit();
}


bool Renderer::init(GLibrary gl) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) == -1) {
		NDE_ERROR(SDL_GetError());
		return false;
	}

	switch (gl) {
#ifdef USE_OPENGL
	case GLibrary::OPENGL: {
		int height = SGET_I("HEIGHT");
		int width = SGET_I("WIDTH");

		screen = SDL_SetVideoMode(width, height, 32, SDL_OPENGL);

		if (screen == NULL) {
			Game::GetInstance().setError(SDL_GetError());
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

}

