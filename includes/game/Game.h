#pragma once
/*
 * Game.h
 *
 *  Created on: 2011-12-01
 *      Author: richard
 */

namespace nde {

class Game {
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
