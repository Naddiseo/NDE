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
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "math/vector.hpp"

namespace nde {


typedef std::vector<Vector3f*> vec_list_t;
typedef std::vector<Vector2f*> point_list_t;

class Face;
class IsRendered;
typedef std::vector<Face*> faces_t;
typedef std::vector<IsRendered*> rendered_list_t;


typedef std::map<std::string, GLuint> intmap_t;


// defined in misc.cpp
GLuint loadNewTexture(const char * filename,bool useMipMap=true);


}
