#pragma once
#include "game/Scene.hpp"

namespace nde {

class World {
	Scene scene;
public:
	World();
	virtual ~World();

	Scene& getScene() { return scene; }
};

} // namespace nde
