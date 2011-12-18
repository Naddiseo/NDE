/*
 * Face.cpp
 *
 *  Created on: 2011-12-11
 *      Author: richard
 */

#include "graphics/Face.hpp"

namespace nde {

Face::Face()
	: textureid(0), mode(GL_TRIANGLES), col() {}

Face::~Face() {
	// Mesh will delete vertexes
	for (Vector2f* v : tex_points) {
		if (v) {
			delete v;
		}
	}
}

void
Face::draw() {
	point_list_t::iterator tex_iter = tex_points.begin();

	if (textureid > 0) {
		glBindTexture(GL_TEXTURE_2D, textureid);
	}
	else {
		col.set();
	}

	glBegin(mode);
	for (Vector3f* v : vertexes) {
		if (tex_iter != tex_points.end()) {
			glTexCoord2f((*tex_iter)->x, (*tex_iter)->y);
			tex_iter++;
		}
		glVertex3f(v->x, v->y, v->z);
	}
	glEnd();

	col.reset();
}

void Face::setEnum() {
	switch (vertexes.size()) {
	case 1: mode = GL_POINTS; break;
	case 2: mode = GL_LINES; break;
	case 3: mode = GL_TRIANGLES; break;
	case 4: mode = GL_QUADS; break;
	default: mode = GL_POLYGON; break;
	}
}

scalar Face::avgHeight() const {
	scalar sum = 0;
	for (const Vector3f* v  : vertexes) {
		sum += v->y;
	}
	return sum/vertexes.size();
}

void
Face::add(Vector3f* v) {
	vertexes.push_back(v);
}

void
Face::tex(scalar x, scalar y) {
	tex_points.push_back(new Vector2f(x, y));
}

void
Face::hasTexBox() {
	tex(0, 0);
	tex(1, 0);
	tex(1, 0.5);
}

} /* namespace nde */
