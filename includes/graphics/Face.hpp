#pragma once
/*
 * Face.hpp
 *
 *  Created on: 2011-12-11
 *      Author: richard
 */

#include <GL/gl.h>

#include "common.hpp"
#include "resources/Color.hpp"
namespace nde {

class Face {
public:

	GLuint textureid;
	vec_list_t vertexes;
	point_list_t tex_points;
	GLenum mode;
	Color col;

	Face();
	virtual ~Face();

	void add(Vector3f* v);
	void tex(scalar x, scalar y);

	void draw();

	void setEnum();
	void hasTexBox();
	scalar avgHeight() const;
};

} /* namespace nde */
