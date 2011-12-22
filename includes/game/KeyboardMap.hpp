#pragma once
#include <SDL/SDL.h>

namespace nde {

typedef void (*keyboard_callback_t)(size_t mods);

class KeyboardMap {
	keyboard_callback_t callbacks[SDLK_LAST];
public:
	KeyboardMap();
	virtual ~KeyboardMap();

	void installCallback(SDLKey key, keyboard_callback_t callback);
	void uninstallCallback(SDLKey key, keyboard_callback_t callback);

	void dispatch(SDL_KeyboardEvent& event);
};

}


