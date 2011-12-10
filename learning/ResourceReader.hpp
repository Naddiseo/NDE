#pragma once
/*
 * TextReader.h
 *
 *  Created on: 2011-11-28
 *      Author: richard
 */
#include <string>
#include <vector>
#include <map>
#include <GL/gl.h>
#include "matrix.hpp"
#include "Color.hpp"


GLuint loadTexture(const char * filename,bool useMipMap = true);

typedef std::vector<Vector3f*> vec_list_t;
typedef std::vector<Vector2f*> point_list_t;

struct face_t {
	std::string tex_name;
	GLuint textureid;
	vec_list_t vertexes;
	point_list_t tex_points;
	GLenum mode;

	Color col;

	face_t() : tex_name(""), textureid(0), vertexes(), tex_points(), col() {}

	~face_t() {
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

	void load() {
		if (tex_name.size() > 0) {
			textureid = loadTexture(tex_name.c_str());
		}
	}

	void setEnum() {
		switch (vertexes.size()) {
		case 1: mode = GL_POINTS; break;
		case 2: mode = GL_LINES; break;
		case 3: mode = GL_TRIANGLES; break;
		case 4: mode = GL_QUADS; break;
		default: mode = GL_POLYGON; break;
		}
	}

	void draw() {
		point_list_t::iterator tex_iter = tex_points.begin();

		if (tex_name.size() > 0) {
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

};
typedef std::vector<face_t*> faces_t;

class ResourceReader {
public:
	faces_t faces;
	ResourceReader(std::string filename);
	virtual ~ResourceReader();
};

