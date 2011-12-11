#define __GXX_EXPERIMENTAL_CXX0X__ 1

#if WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#define _WIN32_WINNT 0x0500
	#include <windows.h>
#endif

#include <iostream>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "ResourceReader.hpp"
#include "Terrain.hpp"
#include "Camera.hpp"

const int HEIGHT = 480;
const int WIDTH = 640;

bool has_shift(SDL_Event& event) {
	return (event.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT;
}
#if WINDOWS
int APIENTRY WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow
) {
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
#else
int main() {
#endif
	nde::Camera camera;
	int mouseX = 0, mouseY = 0;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface* screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_OPENGL);

	SDL_Flip(screen);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	//glCullFace(GL_BACK);

	//glEnable(GL_CULL_FACE);

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(70, WIDTH/HEIGHT, 1, 1000);

	SDL_EnableKeyRepeat(10,10);

	//ResourceReader resource("test.txt");
	nde::Terrain terrain;
	SDL_Event event;

	camera.move({0,0, 45});
	camera.moveForwards(1);
	camera.rotateY(90);

	for (;;) {
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
					camera.rotateX(1);
					break;
				case SDLK_DOWN:
					camera.rotateX(-1);
					break;
				case SDLK_RIGHT:
					camera.strafeRight(0.1);
					break;
				case SDLK_LEFT:
					camera.strafeRight(-0.1);
					break;
				case SDLK_w:
					camera.moveForwards(-0.1);
					break;
				case SDLK_s:
					camera.moveForwards(0.1);
					break;
				case SDLK_a:
					camera.rotateY(1);
					break;
				case SDLK_d:
					camera.rotateY(-1);
					break;
				default:
					break;
				}
			default:
				break;
			}
		}

		SDL_GetMouseState(&mouseX, &mouseY);

		if (mouseX < 30) {
			camera.rotateY(0.5);
		}
		else if (mouseX > (WIDTH-30)) {
			camera.rotateY(-0.5);
		}

		if (mouseY < 30) {
			camera.rotateX(0.5);
		}
		else if (mouseY > (HEIGHT - 30)) {
			camera.rotateX(-0.5);
		}


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		camera.render();

		for (face_t* face : terrain.faces) {
			face->draw();
		}

		glFlush();
		SDL_GL_SwapBuffers();
	}

	SDL_Quit();

	return 0;
}
