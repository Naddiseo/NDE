#include "game/Input.hpp"
#include "game/Game.hpp"
namespace nde {

Input::Input() {}

Input::~Input() {}

bool Input::init() {
	return true;
}

void Input::pollEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch ((short)event.type) {
		case SDL_QUIT:
			game->stopGame();
			return;
			break;
		case SDL_MOUSEMOTION:
			camera->onMouseMotion(event.motion);
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_WHEELUP) {
				//fov -= 1;
			}
			else if (event.button.button == SDL_BUTTON_WHEELDOWN) {
				//fov += 1;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			camera->onMouseClick(event.button);
			break;
		case SDL_KEYDOWN:
			keymap.press(event.key.keysym.sym);
			break;
		case SDL_KEYUP:
			keymap.depress(event.key.keysym.sym);
		default:
			break;
		}
		keymap.dispatch(0);
	}

}


}

