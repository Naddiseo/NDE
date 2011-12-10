#pragma once
/*
 * Game.h
 *
 *  Created on: 2011-12-01
 *      Author: richard
 */

#include "game/Assets.hpp"
#include "game/World.hpp"

namespace nde {

class Game {
	Assets assets;
public:
	static Game& getInstance() {
		static Game instance;
		return instance;
	}
	virtual ~Game();

	bool loadScene(const std::string& path) {
		return getWorld().getScene().loadScene(path);
	}

	World& getWorld() const {
		return World::getInstance();
	}
private:
	Game();
	Game(Game const&);
	void operator=(Game const&);
};

} /* namespace nde */
