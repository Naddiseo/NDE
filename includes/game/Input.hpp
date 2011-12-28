#pragma once
#include <list>
#include <SDL/SDL.h>

#include "game/KeyboardMap.hpp"
#include "game/MouseMap.hpp"
#include "game/EngineModule.hpp"

namespace nde {


class Input : public EngineModule {
	KeyboardMap keymap;
	MouseMap mousemap;
public:
	Input();
	virtual ~Input();

	bool init();

	void pollEvents();

	KeyboardMap& getKeyMap() { return keymap; }
	MouseMap& getMouseMap() { return mousemap; }
};

}


