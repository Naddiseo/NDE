/*
 * Face.cpp
 *
 *  Created on: 2011-12-11
 *      Author: richard
 */

#include "graphics/Face.hpp"

namespace nde {

Face::Face()
	: textureid(0), vertexes(), tex_points(), mode(GL_QUADS), col() {}

Face::~Face() {
	for (Vector3f* v : vertexes) {
		if (v) {
			delete v;
		}
	}
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

	/*glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA);
	glPolygonMode (GL_BACK, GL_LINE);
	glLineWidth (1);
	glCullFace (GL_FRONT);
	glDepthFunc (GL_LEQUAL);
	glColor3f(33,33,33);
	 */
	glBegin(mode);
	for (Vector3f* v : vertexes) {
		if (tex_iter != tex_points.end()) {
			glTexCoord2f((*tex_iter)->x, (*tex_iter)->y);
			tex_iter++;
		}
		glVertex3f(v->x, v->y, v->z);
	}
	glEnd();

	/*
	glDepthFunc (GL_LESS);
	glCullFace (GL_BACK);
	glPolygonMode (GL_BACK, GL_FILL);
	glEnable(GL_BLEND);
	*/
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

void
Face::add(float x, float y, float z) {
	vertexes.push_back(new Vector3f(x, y, z));
}

void
Face::tex(float x, float y) {
	tex_points.push_back(new Vector2f(x, y));
}

void
Face::hasTexBox() {
	tex(0, 0);
	tex(1, 0);
	tex(1, 1);
	tex(0, 1);
}

} /* namespace nde */
