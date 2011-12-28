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
			mousemap.dispatchMove(event.motion);
			break;
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEBUTTONDOWN:
			mousemap.dispatchClick(event.button);
			break;
		case SDL_KEYDOWN:
			keymap.press(event.key.keysym.sym);
			break;
		case SDL_KEYUP:
			keymap.depress(event.key.keysym.sym);
			break;
		default:
			break;
		}
	}
	keymap.dispatch(event.key.keysym.mod);

}


}

