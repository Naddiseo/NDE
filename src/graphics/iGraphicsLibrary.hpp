#pragma once
/**
 * Abstraction layer for the graphics api.
 * Assumes that vertex buffer objects are mainly use.
 */
#include "math/Vector.hpp"

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

/**
 * 1. Base VBO that will get passed into the GPU
 * 2. Can be subclassed.
 * 3. Uses unmanaged arrays beacuse of 1.
 */
struct iBufferObject {
	VBOVertex* buffer;
	size_t* index_buffer;
	size_t vertex_count;
	size_t index_count;

	iBufferObject(size_t _vertex_count, size_t _index_count) {
		vertex_count = _vertex_count;
		index_count = _index_count;
		buffer = new VBOVertex[vertex_count];
		index_buffer = new size_t[index_count];
	}

	virtual ~iBufferObject() {
		if (buffer) {
			delete[] buffer;
		}
		if (index_buffer) {
			delete[] index_buffer;
		}
	}
};

/*
 * Iterface for the graphics library being used.
 */
class iGraphicsLibrary {
protected:
	char  vertexFlags;

	size_t height;
	size_t width;
public:
	iGraphicsLibrary() : vertexFlags(static_cast<char>(VertexFlags::NONE)), height(0), width(0) {}
	virtual ~iGraphicsLibrary() {}

	double inline getAspect() const { return static_cast<double>(width)/static_cast<double>(height); }

	virtual bool init() = 0;
	virtual void clearScreen() = 0;

	virtual void setIdentity() = 0;
	virtual void setMatrixMode(MatrixMode m) = 0;
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

	virtual void allocBuffer(iBufferObject* buffer) = 0;
	virtual void addToBuffer(iBufferObject* buffer) = 0;
	virtual void flushBuffer(iBufferObject* buffer) = 0;


	virtual void translate(Vector3f position) = 0;
	virtual void scale(Vector3f amount) = 0;
	virtual void rotate(scalar degrees, Vector3f axis) = 0;

	// Utilities
	virtual void takeScreenshot(std::string path) = 0;

	// Caller is responsible for freeing the memory
	virtual iBufferObject* createBuffer(size_t vertex_count, size_t index_count) = 0;
};


}


