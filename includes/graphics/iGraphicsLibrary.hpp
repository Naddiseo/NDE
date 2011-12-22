#pragma once
#include <string>
#include "math/vector.hpp"
#include "resources/Color.hpp"

namespace nde {

#pragma pack(push, 1)
struct VBOVertex {
	Vector3f pos;
	Vector3f normal;
	Vector2f tex1;
	Vector2f tex2;
	Vector2f tex3;
	scalar r, g, b, a; // Color, if any
};
#pragma pack(pop)

enum class VertexFlags : char {
	NONE   = 0,
	COLOR  = 1,
	TEX1   = 2,
	TEX2   = 4,
	TEX3   = 8,
	NORMAL = 16,
};

enum class DrawMode : char {
	TRIANGLES = 0, // default
	LINES,
	QUADS,
	TRIANGLE_STRIP,
	TRIANGLE_FAN
};

enum class VBOHint : char {
	SYSTEM_MEM, // stored in the computer's ram. opengl = Dynamic, directx = D3DPOOL_SCRATCH
	VRAM,       // store in video card ram. opengl = Static, directx = D3DPOOL_MANAGED

	GUESS,      // Let the driver decide. opengl = dynamic?, directx = D3DPOOL_DEFAULT
};

class iGraphicsLibrary {
	Color clearColor;
public:
	iGraphicsLibrary();
	virtual ~iGraphicsLibrary();

	virtual void init() = 0;
	virtual void clearScreen() = 0;

	virtual void setClearColor(Color c) { clearColor = c; }

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


}


