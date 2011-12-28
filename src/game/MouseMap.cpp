#include "game/MouseMap.hpp"

namespace nde {

MouseMap::MouseMap() {}

MouseMap::~MouseMap() {}

void MouseMap::installOnMove(mousemove_callback_t callback) {
	move_callbacks.push_back(callback);
}
void MouseMap::installOnClick(mouseclick_callback_t callback) {
	click_callbacks.push_back(callback);
}


void MouseMap::dispatchMove(const SDL_MouseMotionEvent& event) {
	for (const mousemove_callback_t& callback : move_callbacks) {
		callback(event);
	}
}

void MouseMap::dispatchClick(const SDL_MouseButtonEvent& event) {
	for (const mouseclick_callback_t& callback : click_callbacks) {
		callback(event);
	}
}

}

