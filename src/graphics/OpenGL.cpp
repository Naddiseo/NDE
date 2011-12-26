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
#include <SDL/SDL.h>
#include <GL/glu.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include "debug.hpp"

#include "graphics/OpenGL.hpp"

/*
 * VBO from:
 * http://nehe.gamedev.net/tutorial/vertex_buffer_objects/22002/
 * http://stackoverflow.com/questions/4317062/opengl-how-to-check-if-the-user-supports-glgenbuffers
 */

PFNGLGENBUFFERSARBPROC glGenBuffersARB = NULL;                  // VBO Name Generation Procedure
PFNGLBINDBUFFERARBPROC glBindBufferARB = NULL;                  // VBO Bind Procedure
PFNGLBUFFERDATAARBPROC glBufferDataARB = NULL;                  // VBO Data Loading Procedure
PFNGLBUFFERSUBDATAARBPROC glBufferSubDataARB = NULL;            // VBO Sub Data Loading
PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB = NULL;            // VBO Deletion Procedure

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

bool OpenGL::init() {
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
	gluPerspective(70, width/height, 1, 35);
	
	return true;
}

void OpenGL::clearScreen() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGL::setIdentity() {
	glLoadIdentity();
}

void OpenGL::setMatrixMode(MatrixMode m) {
	switch (m) {
	case MatrixMode::MODELVIEW:
		glMatrixMode(GL_MODELVIEW);
		break;
	case MatrixMode::PROJECTION:
		glMatrixMode(GL_PROJECTION);
		break;
	}
}

void OpenGL::startScene() {
	setMatrixMode(MatrixMode::PROJECTION);
	setIdentity();


	gluPerspective(35, width/height, 1, 500);
	glViewport(0, 0, width, height);

}
void OpenGL::endScene() {
	glFlush();
	SDL_GL_SwapBuffers();
}

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
void OpenGL::drawSphere(VBOVertex center, scalar radius) { }
void OpenGL::drawBox(VBOVertex min, VBOVertex max) { }

void OpenGL::allocBuffer(iBufferObject* ibuffer) {
	BufferObject* buffer = (BufferObject*)ibuffer;
	glGenBuffersARB(1, &buffer->vboId);
	glBindBufferARB(GL_ARRAY_BUFFER, buffer->vboId);
	glBufferDataARB(GL_ARRAY_BUFFER, sizeof(VBOVertex) * buffer->element_count, NULL, GL_STATIC_DRAW);

	glGenBuffersARB(1, &buffer->indexId);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, buffer->indexId);
	glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER, sizeof(size_t) * buffer->element_count, NULL, GL_STATIC_DRAW);

}

void OpenGL::addToBuffer(iBufferObject* ibuffer) {
	BufferObject* buffer = (BufferObject*)ibuffer;
	glBufferSubDataARB(GL_ARRAY_BUFFER, 0, sizeof(VBOVertex) * buffer->element_count, buffer->buffer);
	glBufferSubDataARB(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(size_t) * buffer->element_count, buffer->index_buffer);
}

void OpenGL::flushBuffer(iBufferObject* ibuffer) {
	BufferObject* buffer = (BufferObject*)ibuffer;
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, buffer->vboId);
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
	glVertexPointer(3, GL_FLOAT, sizeof(VBOVertex), BUFFER_OFFSET(offsetof(VBOVertex, pos)));
	//glNormalPointer(GL_FLOAT, 64, BUFFER_OFFSET(12));
	//glClientActiveTexture(GL_TEXTURE0);
	//glTexCoordPointer(2, GL_FLOAT, 64, BUFFER_OFFSET(24));
	//glClientActiveTexture(GL_TEXTURE1);
	//glTexCoordPointer(2, GL_FLOAT, 64, BUFFER_OFFSET(32));
	//glClientActiveTexture(GL_TEXTURE2);
	//glTexCoordPointer(2, GL_FLOAT, 64, BUFFER_OFFSET(40));

	 glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, buffer->indexId);
	 glDrawArrays( GL_TRIANGLES, 0, buffer->element_count);
}

void OpenGL::translate(Vector3f position) {
	glTranslatef(position.x, position.y, position.z);
}

void OpenGL::scale(Vector3f amount) {
	glScalef(amount.x, amount.y, amount.z);
}

void OpenGL::rotate(scalar degrees, Vector3f axis) {
	glRotatef(degrees, axis.x, axis.y, axis.z);
}

// Utilities
void OpenGL::takeScreenshot(std::string path) {
	unsigned char* imageData = new unsigned char[width * height * 4];

	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	ilLoadDataL(imageData, width*height*4, width, height, 1, 4);
	iluFlipImage();
	ilEnable(IL_FILE_OVERWRITE);
	ilSave(IL_PNG, path.c_str());

	delete[] imageData;
}

iBufferObject* OpenGL::createBuffer(size_t element_count) {
	return new BufferObject(element_count);
}

}
