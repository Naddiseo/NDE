#include "game/MouseMap.hpp"

namespace nde {

MouseMap::MouseMap() : last_clicked(NONE), last_click(0) {}

MouseMap::~MouseMap() {}

void MouseMap::installOnMove(mousemove_callback_t callback) {
	move_callbacks.push_back(callback);
}

void MouseMap::dispatchMove(const SDL_MouseMotionEvent& event) {
	for (const mousemove_callback_t& callback : move_callbacks) {
		callback(event);
	}
}

void MouseMap::dispatchClick(const SDL_MouseButtonEvent& event) {
	static size_t click_duration = nde::Settings::getInstance()["mouse_click_duration"];
	size_t diff = 0, tick = SDL_GetTicks();
	bool is_dblclick = false;

	if (last_clicked != NONE) {
		diff = tick - last_click;
	}
	last_click = tick;

	// possible double click?
	is_dblclick = (event.button == last_clicked && diff < click_duration);


	switch (event.button) {
	case SDL_BUTTON_LEFT: break;
	case SDL_BUTTON_MIDDLE: break;
	case SDL_BUTTON_RIGHT: break;
	default:
		// unknown
		return;
	}
	last_clicked = event.button;

}

}

