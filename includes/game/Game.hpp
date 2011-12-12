#pragma once
/*
 * Game.h
 *
 *  Created on: 2011-12-01
 *      Author: richard
 */

#include "resources/Assets.hpp"
#include "game/World.hpp"
#include "graphics/Renderer.hpp"

namespace nde {

class Game {
	Assets assets;
	World world;
	Renderer renderer;
public:
	static Game& getInstance() {
		static Game instance;
		return instance;
	}
	virtual ~Game();

	bool loadScene(const std::string& path) {
		return getWorld().getScene().loadScene(path);
	}

	World& getWorld() {
		return world;
	}
private:
	Game();
	Game(Game const&);
	void operator=(Game const&);
};

} /* namespace nde */
