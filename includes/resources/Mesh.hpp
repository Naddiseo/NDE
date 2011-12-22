#pragma once

#include <vector>

#include "HasId.hpp"
#include "graphics/Face.hpp"
#include "math/vector.hpp"

namespace nde {


class Mesh : public HasId {
protected:
	Vector3f origin;
	Vector3f orientation;

	size_t array_count;
	size_t color_count;
	GLuint vboId;

public:
	std::vector<Vector3f*> vertices;
	std::vector<Face*> faces;

	Mesh() : origin(), orientation(), vertices(), faces() {}
	virtual ~Mesh();

	virtual void render(Vector3f& translate);

	GLuint reserve(size_t elements);
	//char*   reserveColors(size_t elements);
	virtual void flush();

	virtual Vector3f* add(scalar x, scalar y, scalar z);

	void setOrigin(Vector3f _origin) { origin = _origin; }
	void setOrientation(Vector3f _orientation) { orientation = _orientation; }

	template<typename ...Args>
	Face* allocFace(Args&&... params);

	template<typename H = Face*>
	void addFaces(const H& f);

	template<typename H = Face*, typename... T>
	void addFaces(const H& f, const T&... tail);

	friend class Entity;
};

template<typename ...Args>
Face* Mesh::allocFace(Args&&... params) {
	Face* ret = new Face(std::forward<Args>(params)...);
	faces.push_back(ret);
	return ret;
}

template<typename H>
void Mesh::addFaces(const H& f) {
	faces.push_back(f);
}

template<typename H, typename... T>
void Mesh::addFaces(const H& f, const T&... tail) {
	addFaces(f);
	addFaces(tail...);
}
}
