#include "resources/Material.hpp"

#include <string>

#include <GL/glu.h>

namespace nde
{

typedef std::map<std::string, GLuint> intmap_t;

intmap_t texture_map;

GLuint
loadTexture(const std::string& path) {
	if (texture_map.find(path) == texture_map.end()) {
		ILuint texid = ilGenImage();
		ilBindImage(texid);

		if (ilLoadImage(path.c_str())) {
			if (ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE)) {
				GLuint imageid = 0;
				
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

Material::Material(uint32_t id, const std::string& file)
	: image_id(loadTexture(file)), id(id), file(file)
{ }

}
