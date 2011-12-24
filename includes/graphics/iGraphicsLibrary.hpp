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
	VERTEX = 1,
	COLOR  = 2,
	TEX1   = 4,
	TEX2   = 8,
	TEX3   = 16,
	NORMAL = 32,
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

enum class MatrixMode : char {
	PROJECTION,
	MODELVIEW,
};

class iGraphicsLibrary {
protected:
	Color clearColor;
	char  vertexFlags;

	size_t height;
	size_t width;
public:
	iGraphicsLibrary();
	virtual ~iGraphicsLibrary();

	virtual bool init() = 0;
	virtual void clearScreen() = 0;

	virtual void setIdentity() = 0;
	virtual void setMatrixMode(MatrixMode m) = 0;
	virtual void setClearColor(Color c) { clearColor = c; }
	virtual void setVertexFlag(char mask) { vertexFlags |= mask; }


	virtual void startScene() = 0;
	virtual void endScene() = 0;

	// Primatives
	virtual void setLineWidth(scalar width) = 0;
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


	virtual void translate(Vector3f position) = 0;
	virtual void scale(Vector3f amount) = 0;
	virtual void rotate(scalar degrees, Vector3f axis) = 0;

	// Utilities
	virtual void takeScreenshot(std::string path) = 0;
};


}


