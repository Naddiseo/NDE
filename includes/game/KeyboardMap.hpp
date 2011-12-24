#pragma once
#include <functional>
#include <SDL/SDL.h>
#include "game/EngineModule.hpp"

namespace nde {

typedef std::function<void(size_t)> keyboard_callback_t;


class KeyboardMap {
	keyboard_callback_t callbacks[SDLK_LAST];
	bool pressed[SDLK_LAST];
public:
	KeyboardMap();
	virtual ~KeyboardMap();

	void installCallback(SDLKey key, keyboard_callback_t callback);
	void uninstallCallback(SDLKey key);

	void dispatch(size_t mods);

	void press(const SDLKey key);
	void depress(const SDLKey key);
};

}


