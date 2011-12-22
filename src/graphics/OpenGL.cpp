#include <GL/gl.h>
#include "graphics/OpenGL.hpp"


namespace nde {

OpenGL::OpenGL() {}

OpenGL::~OpenGL() {}

// Primatives
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

// 3d primatives
void OpenGL::drawSphere(VBOVertex center, scalar radius){}
void OpenGL::drawBox(VBOVertex min, VBOVertex max){}

VBOVertex* OpenGL::allocBuffer(size_t element_count){ return NULL; }
void OpenGL::addToBuffer(VBOVertex v){}
void OpenGL::flushBuffer(){}

// Utilities
void OpenGL::takeScreenshot(std::string path){}

}

