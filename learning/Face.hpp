#pragma once
/*
 * Face.hpp
 *
 *  Created on: 2011-12-11
 *      Author: richard
 */

#include <GL/gl.h>

#include "common.hpp"
#include "Color.hpp"
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

	void draw();

	void setEnum();
	float avgHeight() const;
};

} /* namespace nde */
