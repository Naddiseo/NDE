/*
 * Terrain.cpp
 *
 *  Created on: 2011-12-10
 *      Author: richard
 */


#include <cstdlib>
#include <ctime>
#include "game/Game.hpp"
#include "graphics/Face.hpp"
#include "resources/Terrain.hpp"

float frand(float a, float b) {
	return ((b-a) * ((float)rand())/RAND_MAX) + a;
}

namespace nde {


void createPeak(int x, int y, int w, int h, float seed, std::vector<vec_list_t>& points) {
	w--;
	h--;

	if (x >= w || y >= h) {
		return;
	}

	int cx = (w-x)>>1;
	int cy = (h-y)>>1;


	Vector3f* a = points[x][y];
	Vector3f* b = points[x][h];
	Vector3f* c = points[w][h];
	Vector3f* d = points[w][y];

	a->y += frand(-seed, +seed);
	b->y += frand(-seed, +seed);
	c->y += frand(-seed, +seed);
	d->y += frand(-seed, +seed);

	Vector3f* center = points[cx][cy];
	center->y += (a->y + b->y + c->y + d->y)/ 4;

	seed -= 0.01;
	createPeak(x, y, cx, cy, seed, points);
	createPeak(cx, cy, w, cy, seed, points);
	createPeak(x, cy, x, h, seed, points);
	createPeak(cx, cy, w, h, seed, points);


}

Terrain::Terrain() {
	std::vector<vec_list_t> points;
	const int n_faces = (1<<5);
	srand(time(NULL));

	std::cout << "Starting Terrain Generation..." << std::flush;

	for (int i = 0; i < n_faces; i++) {
		vec_list_t row;
		for (int j = 0; j < n_faces; j++) {
			row.push_back(new Vector3f(i, 0, j));
		}
		points.push_back(row);
	}

	createPeak(0, 0, n_faces>>1, n_faces>>1, 5.0f, points);


	for (int i = 0; i < n_faces - 1; i++) {
		for (int j = 0; j < n_faces - 1; j++) {
			Face* face = new Face();

			face->vertexes.push_back(points[i][j]);
			face->vertexes.push_back(points[i+1][j]);
			face->vertexes.push_back(points[i+1][j+1]);
			face->vertexes.push_back(points[i][j+1]);

#if 0
			face->tex_points.push_back(new Vector2f(0,0));
			face->tex_points.push_back(new Vector2f(0,1));
			face->tex_points.push_back(new Vector2f(1,1));
			face->tex_points.push_back(new Vector2f(1,0));

			float avg = face->avgHeight();
			if (avg < 5) {
				face->textureid = Game::getInstance().loadAsset("assets/grass.tga");
			}
			else if (avg >= 5) {
				face->textureid = Game::getInstance().loadAsset("assets/snow.tga");
			}
#else
			face->col = Color((rand()%255), (rand()%255), (rand()%255));
#endif
			faces.push_back(face);
		}
	}

	std::cout << "done." << std::endl;
}

Terrain::~Terrain() { std::cout << "Terrain::~Terrain()" << std::endl; }

} /* namespace nde */
