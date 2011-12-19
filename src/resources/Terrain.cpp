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

Terrain::Terrain(World* _world) : Entity(_world), height(1<<5), width(1<<5){
	heightmap = new scalar[height * width];
	colormap = new _col[height * width * sizeof(_col)];

	srand(time(NULL));

	for (size_t i = 0; i < height*width; i++) {
		heightmap[i] = frand(-1.0, 1.0);
		colormap[i].r = crand(80, 255);
		colormap[i].g = crand(80, 255);
		colormap[i].b = crand(80, 255);

		std::cout << (int)colormap[i].r << ", "<< (int)colormap[i].g << ", "<< (int)colormap[i].b << std::endl;
	}

	heightfieldShape = new btHeightfieldTerrainShape(
		width, height, heightmap,
		5.0,
		-1.0, 1.0,
		1,
		PHY_FLOAT,
		false
	);

	addCollisionShape(heightfieldShape);

	mass = 0.0;
}

void Terrain::tick() {
	glBegin(GL_QUADS);
	for (size_t i = 0; i < height-1; i++) {
		for (size_t j = 0; j < width-1; j++) {
			_col c = colormap[i * height + j];
			glColor3b(c.r, c.b, c.g);
			glVertex3f((float)i,  heightmap[i * height + j], j);
			glVertex3f((float)i,  heightmap[(i) * height + j+1], j+1);
			glVertex3f((float)i+1,  heightmap[(i+1) * height + j+1], j+1);
			glVertex3f((float)i+1,  heightmap[(i+1) * height + j], j);
		}

	}
	glEnd();
}

Terrain::~Terrain() {
	delete heightfieldShape;
	delete[] heightmap;
	delete[] colormap;
}

} /* namespace nde */
