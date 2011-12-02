#pragma once
/*
 * Game.h
 *
 *  Created on: 2011-12-01
 *      Author: richard
 */

#include "game/Assets.hpp"

namespace nde {

class Game {
	Assets assets;
public:
	static Game& getInstance() {
		static Game instance;
		return instance;
	}
	virtual ~Game();
private:
	Game();
	Game(Game const&);
	void operator=(Game const&);
};

} /* namespace nde */
