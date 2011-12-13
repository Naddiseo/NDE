#pragma once

#include <vector>

#include "graphics/Face.hpp"
#include "math/vector.hpp"

namespace nde {

class Mesh {
public:
	uint32_t id;
	std::vector<Vector3f> vertices;
	std::vector<Face> faces;

	Mesh() : id(0), vertices(), faces() {}
	virtual ~Mesh();
};

}
