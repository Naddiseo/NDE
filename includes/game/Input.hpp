#pragma once
#include <queue>
#include <SDL/SDL.h>

#include "game/KeyboardMap.hpp"

namespace nde {

class Input {
	std::queue<SDL_Event> event_list;
	KeyboardMap keymap;
public:
	Input();
	virtual ~Input();

	void pollEvents();
	void processEvents();
	void clearEvents();

	KeyboardMap& getKeyMap() { return keymap; }
};

}


