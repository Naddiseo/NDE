#pragma once
#include <queue>
#include <SDL/SDL.h>

#include "game/KeyboardMap.hpp"

namespace nde {


class Game;

class Input {
	std::queue<SDL_Event> event_list;
	KeyboardMap keymap;
	const Game* game;
public:
	Input();
	virtual ~Input();

	bool init(const Game* game);

	void pollEvents();
	void processEvents();
	void processEvent(SDL_Event& event);
	void clearEvents();

	KeyboardMap& getKeyMap() { return keymap; }
};

}


