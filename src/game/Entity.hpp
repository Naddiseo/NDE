#pragma once
#include "physics/Body.hpp"

namespace nde {

class Entity {
	Body body;
public:
	Entity();
	virtual ~Entity();
};

} // namespace nde


