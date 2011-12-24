#include "game/KeyboardMap.hpp"

namespace nde {

KeyboardMap::KeyboardMap() {
	for (size_t i = 0; i < SDLK_LAST; i++) {
		callbacks[i] = NULL;
		pressed[i] = false;
	}
}

KeyboardMap::~KeyboardMap() {}

void KeyboardMap::installCallback(SDLKey key, const keyboard_callback_t& callback) {
	callbacks[key] = callback;
}

void KeyboardMap::uninstallCallback(SDLKey key) {
	callbacks[key] = NULL;
}

void KeyboardMap::dispatch(const SDL_KeyboardEvent& event) {
	keyboard_callback_t c = callbacks[event.keysym.sym];
	
	if (c) {
		c((unsigned int)event.keysym.mod);
	}
}

}

