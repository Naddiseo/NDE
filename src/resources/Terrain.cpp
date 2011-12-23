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
	return std::max((a + ((b-a) * rand())%b), b);
}

namespace nde {

#define WH (1<<7)

Terrain::Terrain(World* _world)
	: Entity(_world), scale(1), height(WH), width(WH)
{
	scalar min = -1, max = 1;
	heightmap = new scalar[height * width];
	colormap = new _col[height * width * sizeof(_col)];

	srand(time(NULL));

	for (size_t i = 0; i < height*width; i++) {
		heightmap[i] = frand(min, max);
		colormap[i].r = crand(100, 255);
		colormap[i].g = crand(100, 255);
		colormap[i].b = crand(100, 255);
	}

	heightfieldShape = new btHeightfieldTerrainShape(
		width, height, heightmap,
		5.0,
		min, max,
		1,
		PHY_FLOAT,
		false
	);

	heightfieldShape->setLocalScaling({scale, 1, scale});

	addCollisionShape(heightfieldShape);


	mesh = Game::getInstance().getAssets().allocMesh();
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	// setup vertex arrays
	//size_t vobId = mesh->reserve(height * width);
	{
		//int x, y;
		//size_t hh = height >> 1;
		//size_t hw = width >> 1;

		for (size_t i = 0; i < height; i++) {
			for (size_t j = 0; j < width; j++) {
				//x = i - hh;
				//y = j - hw;

				//*ptr++ = ((float)x)*scale;
				//*ptr++ = heightmap[i * height + j];
				//*ptr++ = ((float)y)*scale;

				//_col c = colormap[(int)(((i * height + j)>>2)+0.5)];
				//*cptr++ = c.r;
				//*cptr++ = c.g;
				//*cptr++ = c.b;
			}
		}

	}

	mass = 0.0;
}

void Terrain::tick() {
	/*int x, y;
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
	glEnd();*/

	mesh->flush();

	glBegin(GL_LINES);
	glLineWidth(100);
	{
		glColor4b(255, 78, 78, 255);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 50, 0);
	}
	glEnd();
}

Terrain::~Terrain() {
	delete heightfieldShape;
	delete[] heightmap;
	delete[] colormap;
}

} /* namespace nde */
