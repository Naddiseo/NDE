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
#include "Color.hpp"

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
	double angleZ = 0, angleX = 0;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface* screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_OPENGL);

	SDL_Flip(screen);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(70, WIDTH/HEIGHT, 1, 1000);

	SDL_EnableKeyRepeat(10,10);

	ResourceReader resource("test.txt");
	SDL_Event event;

	for (;;) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
				case SDLK_q:
					exit(0);
					break;
				default:
					break;
				}
			default:
				break;
			}
		}
		angleZ+=1;
		angleX+=1;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(3, 3, 3, 0, 0, 0, 0, 0, 1);

		glRotated(angleZ, 0, 0, 1);
		glRotated(angleX, 1, 0, 0);

		for (face_t* face : resource.faces) {
			face->draw();
		}

		glFlush();
		SDL_GL_SwapBuffers();
	}

	SDL_Quit();

	return 0;
}
