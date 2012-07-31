#pragma once
#include "physics/World.hpp"

namespace nde {

class Scene {
	World world;
public:
	Scene();
	virtual ~Scene();
};

}


