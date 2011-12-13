#pragma once

#include <vector>

#include "math/vector.hpp"

namespace nde
{

class Mesh;

class Model
{
public:
	uint32_t id;
	Vector3f position;
	Vector3f direction;
	Mesh* mesh;
};

}
