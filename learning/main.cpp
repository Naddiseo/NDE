#define __GXX_EXPERIMENTAL_CXX0X__  1
#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <map>
#include <cassert>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

const int HEIGHT = 480;
const int WIDTH = 640;

bool has_shift(SDL_Event& event) {
	return (event.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT;
}

struct Color {
	unsigned char r, g, b;
	Color(unsigned char _r, unsigned char _g, unsigned char _b)
		: r(_r), g(_g), b(_b) {}

	void set() {
		glColor3ub(r, g, b);
	}
};


Color yellow(200, 200, 0);
Color green(0, 255, 0);
Color red(255, 0, 0);
Color purple(0xee, 0x82, 0xee);
Color white(0xff, 0xff, 0xff);
Color blue(0,0, 0xff);

#define V3(x,y,z) glVertex3d(x,y,z)

int main() {

	double angleZ = 0, angleX = 0;


	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface* screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_OPENGL);

	SDL_Flip(screen);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(70, WIDTH/HEIGHT, 1, 1000);

	SDL_EnableKeyRepeat(10,10);

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
				}
			}
		}
		angleZ+=1;
		angleX+=1;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		gluLookAt(3,3,3,0,0,0,0,0,1);

		glRotated(angleZ, 0, 0, 1);
		glRotated(angleX, 1,0,0);

		glBegin(GL_QUADS);

		red.set();
			V3(-1,-1,-1);
			V3(1,-1,-1);
			V3(1,-1,1);
			V3(-1,-1,1);
		green.set();
			V3(-1,1,-1);
			V3(-1,-1,-1);
			V3(1,-1,-1);
			V3(1,1,-1);
		blue.set();
			V3(-1,-1,1);
			V3(-1,1,1);
			V3(-1,1,-1);
			V3(-1,-1,-1);
		yellow.set();
			V3(-1,1,-1);
			V3(1,1,-1);
			V3(1,1,1);
			V3(-1,1,1);
		purple.set();
			V3(1,1,-1);
			V3(1,-1,-1);
			V3(1,-1,1);
			V3(1,1,1);
		white.set();
			V3(-1,-1,1);
			V3(-1,1,1);
			V3(1,1,1);
			V3(1,-1,1);
		glEnd();

		glFlush();
		SDL_GL_SwapBuffers();

	}

	SDL_Quit();

	return 0;
}
