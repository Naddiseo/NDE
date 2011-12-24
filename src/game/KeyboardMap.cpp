#include "game/KeyboardMap.hpp"
#include "debug.hpp"

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

void KeyboardMap::uninstallCallback(SDLKey key) {
	callbacks[key] = NULL;
}

void KeyboardMap::dispatch(size_t mods) {
	
	for (size_t i = 0; i < SDLK_LAST; i++) {
		if (pressed[i]) {
			keyboard_callback_t c = callbacks[i];
			if (static_cast<bool>(c)) {
				c((size_t)mods);
			}
		}
	}


}

void KeyboardMap::press(const SDLKey key) {
	pressed[key] = true;
}
void KeyboardMap::depress(const SDLKey key) {
	pressed[key] = false;
}

}

