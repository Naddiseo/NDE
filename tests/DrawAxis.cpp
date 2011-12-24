#include "DrawAxis.hpp"

/*
 * DrawAxis.cpp
 *
 *  Created on: 2011-12-23
 *      Author: richard
 */
 
#include "game/Game.hpp"

DrawAxis::DrawAxis(nde::World* _world) : nde::Entity(_world) {}

DrawAxis::~DrawAxis() {}

void
DrawAxis::tick() {
#if 0
	using namespace nde;
	//Camera& camera = Game::getInstance().getCamera();
	//Vector3f camerapos = camera.getPosition();
	//Vector3f forward = camera.getForward();
	
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

	glViewport    (0, 0, 150, 150);
	glMatrixMode  (GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, 1.0, 1.0, 20.0);
	glMatrixMode  (GL_MODELVIEW);
	glLoadIdentity();

	// Place small triad between clipping planes.
	glTranslatef(0, 0, -2);

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
#endif
}
