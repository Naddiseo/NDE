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
	float speed = 1.0;
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
		case SDL_KEYUP:
			if ((event.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT) {
				speed = 15.0;
			}
			else {
				speed = 1.0;
			}
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
			case SDLK_q:
				game->stopGame();
				return;
				break;
			case SDLK_UP:
				camera->rotate(0, 0.015625);
				break;
			case SDLK_DOWN:
				camera->rotate(0, -0.015625);
				break;
			case SDLK_RIGHT:
				camera->rotate(0.015625, 0);
				break;
			case SDLK_LEFT:
				camera->rotate(-0.015625, 0);
				break;
			case SDLK_w:
				if ((event.key.keysym.mod & KMOD_LCTRL) == KMOD_LCTRL) {
					Vector3f tmp(0, 0.375 * speed, 0);
					camera->move(tmp);
				}
				else {
					camera->moveForwards(0.375 * speed);
				}
				break;
			case SDLK_s:
				if ((event.key.keysym.mod & KMOD_LCTRL) == KMOD_LCTRL) {
					Vector3f tmp(0, -0.375 * speed, 0);
					camera->move(tmp);
				}
				else {
					camera->moveForwards(-0.375 * speed);
				}
				break;
			case SDLK_a:
				camera->strafeRight(0.125 * speed);
				break;
			case SDLK_d:
				camera->strafeRight(-0.125 * speed);
				break;

			case SDLK_KP0:
				if ((event.key.keysym.mod & KMOD_LCTRL) == KMOD_LCTRL) {
					Vector3f tmp = -camera->getPosition();
					camera->move(tmp);
				}
				else {
					camera->rotate(-camera->getPhi(), -camera->getTheta());
				}
				break;
			case SDLK_PRINT: {
				graphics->takeScreenshot("Screenshot.png");
			};
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
}


}

