/*
 * ResourceReader.cpp
 *
 *  Created on: 2011-11-28
 *      Author: richard
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include "resources/ResourceReader.hpp"
#include "graphics/Face.hpp"


extern FILE* yyin;
extern int yyparse();
extern nde::faces_t& get_faces();

namespace nde {

ResourceReader::ResourceReader() : texture_map(), faces() {}

void
ResourceReader::load(std::string filename)  {
	yyin = fopen(filename.c_str(), "r");
	if (yyin == NULL) {
		std::cerr << "Could not open file" << std::endl;
		return;
	}

	while (yyparse()) {}

	faces = get_faces();
}

ResourceReader::~ResourceReader() {
	for (Face* face : faces) {
		delete face;
	}
}

GLuint ResourceReader::loadTexture(std::string name) {
	if (texture_map.find(name) == texture_map.end()) {
		texture_map[name] = loadNewTexture(name.c_str());
	}

	return texture_map[name];
}

}
