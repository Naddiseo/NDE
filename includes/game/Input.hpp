#pragma once
#include <list>
#include <SDL/SDL.h>

#include "game/KeyboardMap.hpp"
#include "game/EngineModule.hpp"

namespace nde {


class Input : public EngineModule {
	std::list<SDL_Event> event_list;
	KeyboardMap keymap;
public:
	Input();
	virtual ~Input();

	bool init();

	void pollEvents();
	void processEvents();
	void processEvent(SDL_Event& event);
	void clearEvents();

	KeyboardMap& getKeyMap() { return keymap; }
};

}


