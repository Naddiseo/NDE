/*
 * Game.cpp
 *
 *  Created on: 2011-12-01
 *      Author: richard
 */
#include <SDL/SDL.h>
#include "game/Game.hpp"
#include "game/Settings.hpp"
#include "graphics/IsRendered.hpp"
#include "graphics/Face.hpp"

namespace nde {

Game::Game() : assets(), world(), renderer(), camera(), event() {

	camera.move({
		SGET_F("cam_x"),
		SGET_F("cam_y"),
		SGET_F("cam_z")
	});

	camera.rotateX(SGET_F("cam_rot_x"));
	camera.rotateY(SGET_F("cam_rot_y"));
	camera.rotateZ(SGET_F("cam_rot_z"));

#ifdef WINDOWS
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
#endif
}

Game::~Game() {}

void
Game::handleEvents() {
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			exit(0);
			break;
		case SDL_MOUSEMOTION:
			camera.onMouseMotion(event.motion);
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
			case SDLK_q:
				exit(0);
				break;
			case SDLK_UP:
				camera.rotateX(3);
				break;
			case SDLK_DOWN:
				camera.rotateX(-3);
				break;
			case SDLK_RIGHT:
				camera.rotateY(-1);
				break;
			case SDLK_LEFT:
				camera.rotateY(1);
				break;
			case SDLK_w:
				camera.moveForwards(-0.3);
				break;
			case SDLK_s:
				camera.moveForwards(0.3);
				break;
			case SDLK_a:
				camera.strafeRight(0.1);
				break;
			case SDLK_d:
				camera.strafeRight(-0.1);
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
}

void
Game::handleMouse() {
	static int width = SGET_I("WIDTH");
	static int height = SGET_I("HEIGHT");
	int mouseX = 0, mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);

	if (mouseX < 30) {
		camera.rotateY(0.5);
	}
	else if (mouseX > (width-30)) {
		camera.rotateY(-0.5);
	}

	if (mouseY < 30) {
		camera.rotateX(0.5);
	}
	else if (mouseY > (height - 30)) {
		camera.rotateX(-0.5);
	}
}

void
Game::mainLoop() {
	for (;;) {
		handleEvents();
		handleMouse();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		camera.render();

		for (IsRendered* r : world.getScene().getToRender()) {
			for (Face* face : r->faces) {
				face->draw();
			}
		}

		glFlush();
		SDL_GL_SwapBuffers();
	}
}

} /* namespace nde */
