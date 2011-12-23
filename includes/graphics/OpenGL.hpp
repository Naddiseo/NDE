#pragma once

#include "graphics/iGraphicsLibrary.hpp"

namespace nde {

class OpenGL : public iGraphicsLibrary {
public:
	OpenGL();
	virtual ~OpenGL();

	bool init();

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


	void translate(Vector3f position);
	void scale(Vector3f amount);

	// Utilities
	void takeScreenshot(std::string path);
};

}


