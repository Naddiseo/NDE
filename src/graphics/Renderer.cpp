/*
 * Renderer.cpp
 *
 *  Created on: 2011-12-01
 *      Author: richard
 */
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <IL/il.h>
#include "graphics/Renderer.hpp"
#include "game/Settings.hpp"
#include "game/Game.hpp"


namespace nde {

Renderer::Renderer() : screen(NULL) {}

bool Renderer::Init() {
	int height = Settings::getInstance().get_int("HEIGHT");
	int width = Settings::getInstance().get_int("WIDTH");


	GLenum err = glewInit();

	if (err != GLEW_OK) {
		Game::getInstance().setError((char*)glewGetErrorString(err));
		return false;
	}

	if (glewGetExtension("GL_ARB_vertex_buffer_object")) {
		std::cerr << "Vertex Buffer Object available" << std::endl;
	}

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) == -1) {
		Game::getInstance().setError(SDL_GetError());
		return false;
	}
	screen = SDL_SetVideoMode(width, height, 32, SDL_OPENGL);

	if (screen == NULL) {
		Game::getInstance().setError(SDL_GetError());
		return false;
	}

	SDL_Flip(screen);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(70, width/height, 1, 35);

	if (SDL_EnableKeyRepeat(10,10) == -1) {
		Game::getInstance().setError(SDL_GetError());
		return false;
	}

	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION) {
		// TODO: throw error
		Game::getInstance().setError("Couldn't init devIL");
		return false;
	}
	// initialize devIL
	ilInit();

	return true;
}

Renderer::~Renderer() {
	SDL_Quit();
}


} /* namespace nde */
