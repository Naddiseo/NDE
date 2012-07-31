#pragma once

#include <SDL/SDL.h>
#include "common.hpp"

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

	const iGraphicsLibrary* getGraphics() const { return graphics; }

	Renderer(const Renderer &other);
	Renderer& operator=(const Renderer &other);
};

}


