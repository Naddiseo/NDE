#pragma once
/*
 * Face.hpp
 *
 *  Created on: 2011-12-11
 *      Author: richard
 */

#include <GL/gl.h>

#include "common.hpp"
#include "graphics/Color.hpp"
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

	void add(float x, float y, float z);
	void tex(float x, float y);

	void draw();

	void setEnum();
	void hasTexBox();
	float avgHeight() const;
};

} /* namespace nde */
