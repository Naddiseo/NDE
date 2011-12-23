/*
 * Terrain.cpp
 *
 *  Created on: 2011-12-10
 *      Author: richard
 */


#include <cstdlib>
#include <ctime>
#include <BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>
#include "game/Game.hpp"
#include "graphics/Face.hpp"
#include "resources/Terrain.hpp"

scalar frand(scalar a, scalar b) {
	return ((b-a) * ((scalar)rand())/RAND_MAX) + a;
}

char crand(size_t a, size_t b) {
	return (a + ((b-a) * rand()))%b;
}

namespace nde {

Terrain::Terrain(World* _world) : Entity(_world), scale(20), height(1<<7), width(1<<7){
	heightmap = new scalar[height * width];
	colormap = new _col[height * width * sizeof(_col)];

	float heightt = 5*scale/10;

	srand(time(NULL));

	for (size_t i = 0; i < height*width; i++) {
		heightmap[i] = frand(-heightt, heightt);
		colormap[i].r = crand(80, 255);
		colormap[i].g = crand(80, 255);
		colormap[i].b = crand(80, 255);
	}

	heightfieldShape = new btHeightfieldTerrainShape(
		width, height, heightmap,
		5.0,
		-heightt, heightt,
		1,
		PHY_FLOAT,
		false
	);

	heightfieldShape->setLocalScaling({scale, 1, scale});

	addCollisionShape(heightfieldShape);

	mass = 0.0;
}

void Terrain::tick() {
	int x, y;
	float x1, x2, y1, y2;
	size_t hh = height >> 1;
	size_t hw = width >> 1;
	glBegin(GL_QUADS);
	for (size_t i = 0; i < height-1; i++) {
		for (size_t j = 0; j < width-1; j++) {
			_col c = colormap[i * height + j];
			glColor3b(c.r, c.b, c.g);

			x = i - hh;
			y = j - hw;

			x1 = ((float)x)*scale;
			x2 = ((float)x+1)*scale;
			y1 = ((float)y)*scale;
			y2 = ((float)y+1)*scale;

			glVertex3f(x1,  heightmap[i * height + j], y1);
			glVertex3f(x1,  heightmap[(i) * height + j+1], y2);
			glVertex3f(x2,  heightmap[(i+1) * height + j+1], y2);
			glVertex3f(x2,  heightmap[(i+1) * height + j], y1);
		}

	}

	glEnd();
	glBegin(GL_LINES);
	glLineWidth(100);
	{
		glColor4b(255, 78, 78, 255);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 100, 0);
	}
	glEnd();
}

Terrain::~Terrain() {
	delete heightfieldShape;
	delete[] heightmap;
	delete[] colormap;
}

} /* namespace nde */
