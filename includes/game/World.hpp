#pragma once
#include "game/Scene.hpp"

namespace nde {

class World {
	Scene scene;
public:
	static World& getInstance() {
		static World instance;
		return instance;
	}
	virtual ~World();

	Scene& getScene() { return scene; }
private:
	World();
	World(World const&);
	void operator=(World const&);
};

} // namespace nde
