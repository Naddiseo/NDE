#pragma once
/*
 * Renderer.h
 *
 *  Created on: 2011-12-01
 *      Author: richard
 */
#include <SDL/SDL.h>

namespace nde {

class Renderer {
	SDL_Surface* screen;
public:
	Renderer();
	virtual ~Renderer();

	bool Init();

	Renderer(const Renderer &other);
	Renderer& operator=(const Renderer &other);
};

} /* namespace nde */
