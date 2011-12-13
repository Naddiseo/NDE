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



Game::Game() : assets(), world(), renderer(), camera(), event(), fov(70) {

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
	static int speed = 1.0;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			exit(0);
			break;
		case SDL_MOUSEMOTION:
			camera.onMouseMotion(event.motion);
			break;
		case SDL_MOUSEWHEEL:
			if (event.button.button == SDL_BUTTON_WHEELUP) {
				fov -= 1;
			}
			else {
				fov += 1;
			}
			break;
		case SDL_KEYDOWN:
			if ((event.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT) {
				speed = 15.0;
			}
			else {
				speed = 1.0;
			}

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
				if ((event.key.keysym.mod & KMOD_LCTRL) == KMOD_LCTRL) {
					Vector3f tmp(0, 0.3 * speed, 0);
					camera.move(tmp);
				}
				else {
					camera.moveForwards(-0.3 * speed);
				}
				break;
			case SDLK_s:
				if ((event.key.keysym.mod & KMOD_LCTRL) == KMOD_LCTRL) {
					Vector3f tmp(0, -0.3 * speed, 0);
					camera.move(tmp);
				}
				else {
					camera.moveForwards(0.3 * speed);
				}
				break;
			case SDLK_a:
				camera.strafeRight(0.1 * speed);
				break;
			case SDLK_d:
				camera.strafeRight(-0.1 * speed);
				break;

			case SDLK_KP0:
				if ((event.key.keysym.mod & KMOD_LCTRL) == KMOD_LCTRL) {
					Vector3f tmp = -camera.getPos();
					camera.move(tmp);
				}
				else {
					camera.rotateX(-camera.getRotX());
					camera.rotateY(-camera.getRotY());
					camera.rotateZ(-camera.getRotZ());
				}
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
}

void Game::drawAxis() {
	float fvViewMatrix[16];
	double cx = 0, cy = 0, l = 1000;
	double xx, xy, yx, yy, zx, zy;
	glGetFloatv(GL_MODELVIEW_MATRIX, fvViewMatrix);


	xx = l * fvViewMatrix[0];
	xy = l * fvViewMatrix[1];
	yx = l * fvViewMatrix[4];
	yy = l * fvViewMatrix[5];
	zx = l * fvViewMatrix[8];
	zy = l * fvViewMatrix[9];

	glPushMatrix();
	glLineWidth(20);

	glViewport     (0, 0, 150, 150);
	glMatrixMode   (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (65.0, 1.0, 1.0, 20.0);
	glMatrixMode   (GL_MODELVIEW);
	glLoadIdentity ();

	glTranslatef (0, 0, -2);   // Place small triad between clipping planes.

	glRotatef (camera.getRotZ(), 0,0,1);   // Viewing rotations.
	glRotatef (camera.getRotY(), 0,1,0);
	glRotatef (camera.getRotX(), 1,0,0);

	glBegin(GL_LINES);
	Color(255, 255/3, 255/3).set(); //x axis
	glVertex2d(cx, cy);
	glVertex2d(cx + xx, cy + xy);
	Color(255/3, 255, 255/3).set(); // y axis
	glVertex2d(cx, cy);
	glVertex2d(cx + yx, cy + yy);
	Color(255/3, 255/3, 255).set(); // z axis
	glVertex2d(cx, cy);
	glVertex2d(cx + zx, cy + zy);
	glEnd();
	glColor4f(1,1,1,1);
	glPopMatrix();

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
	int height = SGET_I("HEIGHT");
	int width = SGET_I("WIDTH");

	for (;;) {

		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluPerspective(fov, width/height, 1, 500);
		glViewport     (0, 0, width, height);

		handleEvents();
		handleMouse();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		camera.render();

		for (IsRendered* r : world.getScene().getToRender()) {
			r->predraw();
			for (Face* face : r->faces) {
				face->draw();
			}
			r->postdraw();
		}

		drawAxis();

		glFlush();
		SDL_GL_SwapBuffers();
	}
}

} /* namespace nde */
