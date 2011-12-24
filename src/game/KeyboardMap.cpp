#include "game/KeyboardMap.hpp"

namespace nde {

KeyboardMap::KeyboardMap() {
	for (size_t i = 0; i < SDLK_LAST; i++) {
		callbacks[i] = NULL;
		pressed[i] = false;
	}
}

KeyboardMap::~KeyboardMap() {}

void KeyboardMap::installCallback(SDLKey key, keyboard_callback_t callback) {
	callbacks[key] = callback;
}

void KeyboardMap::uninstallCallback(SDLKey key, keyboard_callback_t callback) {
	callbacks[key] = NULL;
}

void KeyboardMap::dispatch(SDL_KeyboardEvent& event) {

	keyboard_callback_t c = callbacks[event.keysym.sym];
	if (c) {
		c((long unsigned int)event.keysym.mod); // TODO
	}
}

}

