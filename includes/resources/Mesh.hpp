#pragma once

#include <vector>

#include "graphics/Face.hpp"
#include "math/vector.hpp"

namespace nde {

class Mesh {
public:
	uint32_t id;
	std::vector<Vector3f*> vertices;
	std::vector<Face*> faces;

	Mesh() : id(0), vertices(), faces() {}
	virtual ~Mesh();

	virtual void render(Vector3f& translate);

	virtual Vector3f* add(scalar x, scalar y, scalar z);

	template<typename H = Face*>
	void addFaces(const H& f) {
		faces.push_back(f);
	}

	template<typename H = Face*, typename... T>
	void addFaces(const H& f, const T&... tail) {
		addFaces(f);
		addFaces(tail...);
	}
};

}
