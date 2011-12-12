#include <GL/gl.h>
#include <IL/il.h>
#include <IL/ilut.h>
#include "resources/Assets.hpp"

namespace nde {

Assets::Assets() : texture_map() {}

Assets::~Assets() {
	for (intmap_t::value_type& it : texture_map) {
		glDeleteTextures(1, &it.second);
	}
}

GLuint
Assets::loadTexture(std::string path) {
	ILuint texid = 0;
	GLuint imageid = 0;
	if (texture_map.find(path) == texture_map.end()) {
		texid = ilGenImage();
		ilBindImage(texid);

		if (ilLoadImage(path.c_str())) {

			if (ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE)) {
				glGenTextures(1, &imageid);
				glBindTexture(GL_TEXTURE_2D, imageid);


				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					ilGetInteger(IL_IMAGE_BPP),
					ilGetInteger(IL_IMAGE_WIDTH),
					ilGetInteger(IL_IMAGE_HEIGHT),
					0,
					ilGetInteger(IL_IMAGE_FORMAT),
					GL_UNSIGNED_BYTE,
					ilGetData()
				);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				texture_map[path] = imageid;
			}
			else {
				// TODO: runtime error
			}

		}
		else {
			// could not load file
			// TODO: runtime error
		}

		ilDeleteImage(texid);
	}

	return texture_map[path];
}


} //namespace nde
