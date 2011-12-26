#pragma once
/*
 * ShootBox.hpp
 *
 *  Created on: 2011-12-25
 *      Author: richard
 */

#include "game/EngineModule.hpp"

class ShootBox: public nde::EngineModule {
public:
	ShootBox();
	virtual ~ShootBox();

	bool init();
};

