#pragma once
#include <list>
#include <SDL/SDL.h>

#include "game/KeyboardMap.hpp"
#include "game/EngineModule.hpp"

namespace nde {


class Input : public EngineModule {
	KeyboardMap keymap;
public:
	Input();
	virtual ~Input();

	bool init();

	void pollEvents();

	KeyboardMap& getKeyMap() { return keymap; }
};

}


