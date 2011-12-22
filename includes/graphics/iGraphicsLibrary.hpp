#pragma once
#include <string>

namespace nde {

class VBOVertex;

class iGraphicsLibrary {
public:
	iGraphicsLibrary();
	virtual ~iGraphicsLibrary();

	virtual void clearScreen() = 0;

	// Primatives
	virtual void drawCircle(VBOVertex center, scalar radius) = 0;
	virtual void drawLine(VBOVertex a, VBOVertex b) = 0;
	virtual void drawTriangle(VBOVertex a, VBOVertex b, VBOVertex c) = 0;
	virtual void drawQuad(VBOVertex a, VBOVertex b, VBOVertex c, VBOVertex d) = 0;

	// 3d primatives
	virtual void drawSphere(VBOVertex center, scalar radius) = 0;
	virtual void drawBox(VBOVertex min, VBOVertex max) = 0;

	virtual VBOVertex* allocBuffer(size_t element_count) = 0;
	virtual void addToBuffer(VBOVertex v) = 0;
	virtual void flushBuffer() = 0;

	// Utilities
	virtual void takeScreenshot(std::string path) = 0;
};


#pragma pack(push, 1)
class VBOVertex {
	Vector3f pos;
	Vector3f normal;
	Vector2f tex1;
	Vector2f tex2;
	Vector2f tex3;
	scalar r, g, b, a; // Color, if any
};
#pragma pack(pop)
}


