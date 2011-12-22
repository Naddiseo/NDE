#pragma once
#include "graphics/GLAPI.hpp"

namespace nde {

class OpenGL : public GLAPI {
public:
	OpenGL();
	virtual ~OpenGL();

	void clearScreen();

	// Primatives
	void drawCircle(VBOVertex center, scalar radius);
	void drawLine(VBOVertex a, VBOVertex b);
	void drawTriangle(VBOVertex a, VBOVertex b, VBOVertex c);
	void drawQuad(VBOVertex a, VBOVertex b, VBOVertex c, VBOVertex d);

	// 3d primatives
	void drawSphere(VBOVertex center, scalar radius);
	void drawBox(VBOVertex min, VBOVertex max);

	VBOVertex* allocBuffer(size_t element_count);
	void addToBuffer(VBOVertex v);
	void flushBuffer();

	// Utilities
	void takeScreenshot(std::string path);
};

}


