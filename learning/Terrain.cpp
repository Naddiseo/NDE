/*
 * Terrain.cpp
 *
 *  Created on: 2011-12-10
 *      Author: richard
 */

#include "Terrain.hpp"
#include <cstdlib>
#include <ctime>

float frand(float a, float b) {
	return ((b-a) * ((float)rand())/RAND_MAX) + a;
}

namespace nde {


void createPeak(int x, int y, int w, int h, float seed, std::vector<vec_list_t>& points) {
	// Three iterations
	w--;
	h--;

	if (x >= w || h >= y) {
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

	seed -= 0.001;
	createPeak(x, y, cx, cy, seed, points);
	createPeak(cx, cy, w, cy, seed, points);
	createPeak(x, cy, x, h, seed, points);
	createPeak(cx, cy, w, h, seed, points);


}

Terrain::Terrain() : faces() {
	std::vector<vec_list_t> points;
	const int n_faces = (1<<5);
	srand(time(NULL));

	std::cout << "Starting Terrain Generation...";
	fflush(stdout);

	for (int i = 0; i < n_faces; i++) {
		vec_list_t row;
		for (int j = 0; j < n_faces; j++) {
			row.push_back(new Vector3f(i, frand(-1,1), j));
		}
		points.push_back(row);
	}

	createPeak(0, 0, n_faces, n_faces, 5.0f, points);


	for (int i = 0; i < n_faces - 1; i++) {
		for (int j = 0; j < n_faces - 1; j++) {
			face_t* face = new face_t();

			face->vertexes.push_back(points[i][j]);
			face->vertexes.push_back(points[i+1][j]);
			face->vertexes.push_back(points[i+1][j+1]);
			face->vertexes.push_back(points[i][j+1]);

			face->tex_points.push_back(new Vector2f(0,0));
			face->tex_points.push_back(new Vector2f(0,1));
			face->tex_points.push_back(new Vector2f(1,1));
			face->tex_points.push_back(new Vector2f(1,0));
#if 1
			float avg = face->avgHeight();
			if (avg < 5) {
				face->tex_name = "grass.tga";
				face->load();
			}
			else if (avg >= 5) {
				face->tex_name = "snow.tga";
				face->load();
			}
#else
			face->col = Color((rand()%255), (rand()%255), (rand()%255));
#endif
			faces.push_back(face);
		}
	}

	std::cout << "done." << std::endl;
}

Terrain::~Terrain() {
	for (face_t* face : faces) {
		delete face;
	}
}

} /* namespace nde */
