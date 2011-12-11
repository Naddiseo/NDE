/*
 * Terrain.cpp
 *
 *  Created on: 2011-12-10
 *      Author: richard
 */

#include "Terrain.hpp"
#include <cstdlib>
#include <ctime>

namespace nde {


void createPeak(int center_x, int center_y, int r, std::vector<vec_list_t>& points) {
	// Three iterations
	for (int i = 0; i < 3; i++) {
		for (int x = center_x-r; x < center_x+r; x++) {
			for (int y = center_y-r; y < center_y+r; y++) {
				points[x][y]->y += (rand()%5);
			}
		}
		r /= 2;
	}
}

Terrain::Terrain() : faces() {
	std::vector<vec_list_t> points;
	const int n_faces = 1<<6;
	const int n_face_h = n_faces >> 1;
	srand(time(NULL));

	for (int i = -n_face_h; i < n_face_h; i++) {
		vec_list_t row;
		for (int j = -n_face_h; j < n_face_h; j++) {
			row.push_back(new Vector3f(i, 0, j));
		}
		points.push_back(row);
	}

	createPeak(30, 30, 20, points);


	for (int i = 0; i < n_faces - 1; i++) {
		for (int j = 0; j < n_faces - 1; j++) {
			face_t* face = new face_t();

			face->vertexes.push_back(points[i][j]);
			face->vertexes.push_back(points[i+1][j]);
			face->vertexes.push_back(points[i+1][j+1]);
			face->vertexes.push_back(points[i][j+1]);
			face->col = Color((rand()%255), (rand()%255), (rand()%255));

			faces.push_back(face);
		}
	}

}

Terrain::~Terrain() {
	for (face_t* face : faces) {
		delete face;
	}
}

} /* namespace nde */
