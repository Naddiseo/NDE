#pragma once
/*
 * common.hpp
 *
 *  Created on: 2011-12-11
 *      Author: richard
 */
#include <string>
#include <vector>
#include <map>

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "math/vector.hpp"

#ifdef NDEBUG
	#include "debug.hpp"
#endif

namespace nde {


typedef std::vector<Vector3f*> vec_list_t;
typedef std::vector<Vector2f*> point_list_t;

class Face;
class IsRendered;
class Entity;
typedef std::vector<Face*> faces_t;
typedef std::vector<Entity*> rendered_list_t;

typedef std::map<std::string, GLuint> intmap_t;

}

#if WINDOWS
#	define BEGIN_MAIN \
	int APIENTRY WinMain(\
		HINSTANCE hInstance,\
		HINSTANCE hPrevInstance,\
		LPSTR     lpCmdLine,\
		int       nCmdShow\
	)
#else
#	define BEGIN_MAIN int main(int argc, char* argv[])
#endif
