#include "game/Input.hpp"

namespace nde {

Input::Input() {}

Input::~Input() {}

void Input::pollEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) == 0) {
		event_list.push(event);
	}
}

void Input::processEvents() {

}

void Input::clearEvents() {
	event_list.empty();
}

}

