#include <cstring>

#ifdef WINDOWS
# include <windows.h>
#	include <GL/gl.h>
#	include <GL/glext.h>
#	define glGetProcAddress(a) wglGetProcAddress(a)
#elif defined(__linux__)
#	include <GL/glx.h>
#	define glGetProcAddress(a) glXGetProcAddress(reinterpret_cast<const unsigned char*>(a))
#else
#	error "Your platform is currently not supported"
#endif
/*
 * VBO from:
 * http://nehe.gamedev.net/tutorial/vertex_buffer_objects/22002/
 * http://stackoverflow.com/questions/4317062/opengl-how-to-check-if-the-user-supports-glgenbuffers
 */

#include "graphics/OpenGL.hpp"

PFNGLGENBUFFERSARBPROC glGenBuffersARB = nullptr;                  // VBO Name Generation Procedure
PFNGLBINDBUFFERARBPROC glBindBufferARB = nullptr;                  // VBO Bind Procedure
PFNGLBUFFERDATAARBPROC glBufferDataARB = nullptr;                  // VBO Data Loading Procedure
PFNGLBUFFERSUBDATAARBPROC glBufferSubDataARB = nullptr;            // VBO Sub Data Loading
PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB = nullptr;

namespace nde {

static bool isSupported(const char* extension) {
	unsigned char* where = (unsigned char*)strchr(extension, ' ');

	if (where || *extension == 0) {
		return false;
	}

	const unsigned char* extensions = glGetString(GL_EXTENSIONS);

	const unsigned char* start = extensions;

	for (;;) {
		where = (unsigned char*)strstr((const char*)start, extension);

		if (!where) {
			break;
		}

		unsigned char* terminator = where + strlen(extension);

		if (where == start || *(where - 1) == ' ') {
			if (*terminator == ' ' || *terminator == 0) {
				return true;
			}
		}

		start = terminator;
	}

	return false;
}


OpenGL::OpenGL() {}
OpenGL::~OpenGL() {}

bool
OpenGL::init() {
	if (!isSupported("GL_ARB_vertex_buffer_object")) {
		NDE_ERROR("Vertex Buffer Objects not supported");
		return false;
	}

	glGenBuffersARB = (PFNGLGENBUFFERSARBPROC)glGetProcAddress("glGenBuffersARB");
	glBindBufferARB = (PFNGLBINDBUFFERARBPROC)glGetProcAddress("glBindBufferARB");
	glBufferDataARB = (PFNGLBUFFERDATAARBPROC)glGetProcAddress("glBufferDataARB");
	glBufferSubDataARB = (PFNGLBUFFERSUBDATAARBPROC)glGetProcAddress("glBufferSubDataARB");
	glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC)glGetProcAddress("glDeleteBuffersARB");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, getAspect(), 1, 35); // default perspective

	return true;
}

} // namespace nde

