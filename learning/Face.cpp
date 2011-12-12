/*
 * Face.cpp
 *
 *  Created on: 2011-12-11
 *      Author: richard
 */

#include "Face.hpp"

namespace nde {

Face::Face()
	: textureid(0), vertexes(), tex_points(), mode(GL_QUADS), col() {}

Face::~Face() {
	for (Vector3f* v : vertexes) {
		delete v;
	}
	for (Vector2f* v : tex_points) {
		delete v;
	}

	if (textureid) {
		glDeleteTextures(1, &textureid);
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

float Face::avgHeight() const {
	float sum = 0;
	for (const Vector3f* v  : vertexes) {
		sum += v->y;
	}
	return sum/vertexes.size();
}

} /* namespace nde */
