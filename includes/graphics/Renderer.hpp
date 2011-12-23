#pragma once
/*
 * Renderer.h
 *
 *  Created on: 2011-12-01
 *      Author: richard
 */
#include <SDL/SDL.h>
#include "graphics/iGraphicsLibrary.hpp"
namespace nde {

enum class GLibrary : char {
	OPENGL,
	//DIRECTX
};

class Renderer {
	SDL_Surface* screen;
	iGraphicsLibrary* graphics;
public:
	Renderer();
	virtual ~Renderer();

	bool init(GLibrary gl = GLibrary::OPENGL);

	iGraphicsLibrary* getGraphics() const { return graphics; }

	Renderer(const Renderer &other);
	Renderer& operator=(const Renderer &other);
};

} /* namespace nde */
