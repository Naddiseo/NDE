/*
 * Game.cpp
 *
 *  Created on: 2011-12-01
 *      Author: richard
 */
#include <SDL/SDL.h>
#include <IL/ilu.h>

#include "game/Game.hpp"
#include "game/Settings.hpp"
#include "game/Entity.hpp"
#include "graphics/IsRendered.hpp"
#include "graphics/Face.hpp"
#include "game/Entity.hpp"

#ifdef WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#define _WIN32_WINNT 0x0500
	#include <windows.h>
#endif

namespace nde {

Game::Game()
	: fov(70), haserror(false), shutdown(false), errorstring(0)
{
	camera.setPosition(SGET_V("cam_pos"));
	camera.rotate(SGET_F("cam_phi"), SGET_F("cam_theta"));
	
#ifdef WINDOWS
	//HWND hWnd = GetConsoleWindow();
	//ShowWindow(hWnd, SW_HIDE);
#endif
}

Game::~Game() {}

void
Game::handleEvents() {
	static scalar speed = 1.0;
	
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			shutdown = true;
			return;
			break;
		case SDL_MOUSEMOTION:
			camera.onMouseMotion(event.motion);
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_WHEELUP) {
				fov -= 1;
			}
			else if (event.button.button == SDL_BUTTON_WHEELDOWN) {
				fov += 1;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			camera.onMouseClick(event.button);
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
				shutdown = true;
				return;
				break;
			case SDLK_UP:
				camera.rotate(0, 0.015625);
				break;
			case SDLK_DOWN:
				camera.rotate(0, -0.015625);
				break;
			case SDLK_RIGHT:
				camera.rotate(0.015625, 0);
				break;
			case SDLK_LEFT:
				camera.rotate(-0.015625, 0);
				break;
			case SDLK_w:
				if ((event.key.keysym.mod & KMOD_LCTRL) == KMOD_LCTRL) {
					Vector3f tmp(0, 0.375 * speed, 0);
					camera.move(tmp);
				}
				else {
					camera.moveForwards(0.375 * speed);
				}
				break;
			case SDLK_s:
				if ((event.key.keysym.mod & KMOD_LCTRL) == KMOD_LCTRL) {
					Vector3f tmp(0, -0.375 * speed, 0);
					camera.move(tmp);
				}
				else {
					camera.moveForwards(-0.375 * speed);
				}
				break;
			case SDLK_a:
				camera.strafeRight(0.125 * speed);
				break;
			case SDLK_d:
				camera.strafeRight(-0.125 * speed);
				break;

			case SDLK_KP0:
				if ((event.key.keysym.mod & KMOD_LCTRL) == KMOD_LCTRL) {
					Vector3f tmp = -camera.getPos();
					camera.move(tmp);
				}
				else {
					camera.rotate(-camera.getPhi(), -camera.getTheta());
				}
				break;
			case SDLK_PRINT: {
				int width = SGET_I("WIDTH");
				int height = SGET_I("HEIGHT");
				unsigned char* imageData = new unsigned char[width * height * 4];

				glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

				ilLoadDataL(imageData, width*height*4, width, height, 1, 4);
				iluFlipImage();
				ilEnable(IL_FILE_OVERWRITE);
				ilSave(IL_PNG, "Screenshot.png");

				delete[] imageData;
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

void Game::drawAxis() {
	scalar fvViewMatrix[16] = {
		0.f, 0.f, 0.f, 0.f,
		0.f, 0.f, 0.f, 0.f,
		0.f, 0.f, 0.f, 0.f,
		0.f, 0.f, 0.f, 0.f,
	};
	
	scalar cx = 0, cy = 0, l = 1000;
	scalar xx, xy, yx, yy, zx, zy;
	static Color* red = assets.getColor("red");
	static Color* green = assets.getColor("green");
	static Color* blue = assets.getColor("blue");
	
	glPushMatrix();
	glLineWidth(20);

	glViewport     (0, 0, 150, 150);
	glMatrixMode   (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (65.0, 1.0, 1.0, 20.0);
	glMatrixMode   (GL_MODELVIEW);
	glLoadIdentity ();

	// Place small triad between clipping planes.
	glTranslatef (0, 0, -2);
	
	// Viewing rotations.
	glRotatef(camera.getTheta(), 0, 1, 0);
	glRotatef(camera.getPhi()  , 1, 0, 0);

	glGetFloatv(GL_MODELVIEW_MATRIX, fvViewMatrix);
	
	xx = l * fvViewMatrix[0];
	xy = l * fvViewMatrix[1];
	yx = l * fvViewMatrix[4];
	yy = l * fvViewMatrix[5];
	zx = l * fvViewMatrix[8];
	zy = l * fvViewMatrix[9];

	glBegin(GL_LINES);
		red->set(); // x axis
		glVertex2d(cx, cy);
		glVertex2d(cx + xx, cy + xy);
		green->set(); //y axis
		glVertex2d(cx, cy);
		glVertex2d(cx + yx, cy + yy);
		blue->set();  // z axis
		glVertex2d(cx, cy);
		glVertex2d(cx + zx, cy + zy);
	glEnd();
	glColor4f(1,1,1,1);
	glPopMatrix();
}

void
Game::handleMouse() {
#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION >= 3
	static int width = SGET_I("WIDTH");
	static int height = SGET_I("HEIGHT");
	int mouseX = 0, mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);

	if (mouseX < 30) {
		camera.rotate(0, 0.1);
	}
	else if (mouseX > (width-30)) {
		camera.rotate(0, -0.1);
	}

	if (mouseY < 30) {
		camera.rotate(0.1, 0);
	}
	else if (mouseY > (height - 30)) {
		camera.rotate(-0.1, 0);
	}
#endif
}

void
Game::mainLoop() {
	int height = SGET_I("HEIGHT");
	int width = SGET_I("WIDTH");

	//set up basic colors
	assets.allocColor("red", 1.f, 0.3f, 0.3f);
	assets.allocColor("green", 0.3f, 1.f, 0.3f);
	assets.allocColor("blue", 0.3f, 0.3f, 1.f);
	assets.allocColor("black", 0.f, 0.f, 0.f);
	assets.allocColor("white", 1.f, 1.f, 1.f);

	while (!(haserror || shutdown)) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(fov, width/height, 1, 500);
		glViewport(0, 0, width, height);

		handleEvents();
		handleMouse();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		camera.render();
		world.step();
		

		/*{
			//print positions of all objects
			for (int j=world.dynamicsWorld->getNumCollisionObjects()-1; j>=0 ;j--)
			{
				btCollisionObject* obj = world.dynamicsWorld->getCollisionObjectArray()[j];
				btRigidBody* body = btRigidBody::upcast(obj);
				if (body && body->getMotionState())
				{
					btTransform trans;
					body->getMotionState()->getWorldTransform(trans);
					printf("world pos = %f,%f,%f\n",float(trans.getOrigin().getX()),float(trans.getOrigin().getY()),float(trans.getOrigin().getZ()));
				}
			}
		}*/


		for (Entity* r : world.getScene().getToRender()) {
			r->tick();
		}

		drawAxis();
		glFlush();
		SDL_GL_SwapBuffers();
	}

	if (haserror) {
		std::cerr << "Game Error: " << errorstring << std::endl;
	}
}

} /* namespace nde */
