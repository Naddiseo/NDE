#pragma once

#include "graphics/iGraphicsLibrary.hpp"

namespace nde {

struct BufferObject : public iBufferObject {
	unsigned int vboId;
	unsigned int indexId;
	VBOVertex* buffer;
	size_t* index_buffer;
	size_t element_count;
};

class OpenGL : public iGraphicsLibrary {
public:
	OpenGL();
	virtual ~OpenGL();

	bool init();
	void clearScreen();

	void setIdentity();
	void setMatrixMode(MatrixMode m);


	void startScene();
	void endScene();

	// Primatives
	void setLineWidth(scalar width);
	void drawCircle(VBOVertex center, scalar radius);
	void drawLine(VBOVertex a, VBOVertex b);
	void drawTriangle(VBOVertex a, VBOVertex b, VBOVertex c);
	void drawQuad(VBOVertex a, VBOVertex b, VBOVertex c, VBOVertex d);

	// 3d primatives
	void drawSphere(VBOVertex center, scalar radius);
	void drawBox(VBOVertex min, VBOVertex max);

	void allocBuffer(iBufferObject* buffer);
	void addToBuffer(iBufferObject* buffer);
	void flushBuffer(iBufferObject* buffer);


	void translate(Vector3f position);
	void scale(Vector3f amount);
	void rotate(scalar degrees, Vector3f axis);

	// Utilities
	void takeScreenshot(std::string path);
};

}


