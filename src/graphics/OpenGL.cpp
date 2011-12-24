#include "graphics/OpenGL.hpp"
#include "debug.hpp"

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
#include <GL/glu.h>

#include "graphics/OpenGL.hpp"

/*
 * VBO from:
 * http://nehe.gamedev.net/tutorial/vertex_buffer_objects/22002/
 * http://stackoverflow.com/questions/4317062/opengl-how-to-check-if-the-user-supports-glgenbuffers
 */

PFNGLGENBUFFERSARBPROC glGenBuffersARB = NULL;                  // VBO Name Generation Procedure
PFNGLBINDBUFFERARBPROC glBindBufferARB = NULL;                  // VBO Bind Procedure
PFNGLBUFFERDATAARBPROC glBufferDataARB = NULL;                  // VBO Data Loading Procedure
PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB = NULL;            // VBO Deletion Procedure

namespace nde {

static bool isSupported(const char* extension) {
	/* TODO: use GLEW */
	
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

bool OpenGL::init() {
	if (!isSupported("GL_ARB_vertex_buffer_object")) {
		NDE_ERROR("Vertex Buffer Objects not supported");
		return false;
	}
	
	glGenBuffersARB = (PFNGLGENBUFFERSARBPROC)glGetProcAddress("glGenBuffersARB");
	glBindBufferARB = (PFNGLBINDBUFFERARBPROC)glGetProcAddress("glBindBufferARB");
	glBufferDataARB = (PFNGLBUFFERDATAARBPROC)glGetProcAddress("glBufferDataARB");
	glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC)glGetProcAddress("glDeleteBuffersARB");
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, width/height, 1, 35);
	
	return true;
}

void OpenGL::clearScreen() {}

// Primitives
void OpenGL::setLineWidth(scalar width) {
	glLineWidth(width);
}
void OpenGL::drawCircle(VBOVertex center, scalar radius) {}

void OpenGL::drawLine(VBOVertex a, VBOVertex b) {
	glBegin(GL_LINES);
		glColor4fv(&a.r);
		glVertex3fv(&a.pos.x);
		glColor4fv(&b.r);
		glVertex3fv(&b.pos.x);
	glEnd();
}

void OpenGL::drawTriangle(VBOVertex a, VBOVertex b, VBOVertex c) {
	glBegin(GL_TRIANGLES);
		glColor4fv(&a.r);
		glVertex3fv(&a.pos.x);
		glColor4fv(&b.r);
		glVertex3fv(&b.pos.x);
		glColor4fv(&c.r);
		glVertex3fv(&c.pos.x);
	glEnd();
}

void OpenGL::drawQuad(VBOVertex a, VBOVertex b, VBOVertex c, VBOVertex d) {
	glBegin(GL_QUADS);
		glColor4fv(&a.r);
		glVertex3fv(&a.pos.x);
		glColor4fv(&b.r);
		glVertex3fv(&b.pos.x);
		glColor4fv(&c.r);
		glVertex3fv(&c.pos.x);
		glColor4fv(&d.r);
		glVertex3fv(&d.pos.x);
	glEnd();
}

// 3D Primitives
void OpenGL::drawSphere(VBOVertex center, scalar radius){}
void OpenGL::drawBox(VBOVertex min, VBOVertex max){}

VBOVertex* OpenGL::allocBuffer(size_t element_count){ return NULL; }
void OpenGL::addToBuffer(VBOVertex v){}
void OpenGL::flushBuffer(){}

void OpenGL::translate(Vector3f position) {
	glTranslatef(position.x, position.y, position.z);
}

void OpenGL::scale(Vector3f amount) {
	glScalef(amount.x, amount.y, amount.z);
}

// Utilities
void OpenGL::takeScreenshot(std::string path){}

}
