#pragma once
/*
 * KeyboardMapImpl.hpp
 *
 *  Created on: 2011-12-20
 *      Author: richard
 */

#include "NDE.hpp"

class KeyboardMapSetup : public nde::EngineModule  {

	void quit(size_t mods);

	void look_up(size_t mods);
	void look_down(size_t mods);
	void look_left(size_t mods);
	void look_right(size_t mods);

	void move_up(size_t mods);
	void move_down(size_t mods);
	void move_left(size_t mods);
	void move_right(size_t mods);

	void reset_camera(size_t mods);
	void screenshot(size_t mods);

public:
	KeyboardMapSetup();
	virtual ~KeyboardMapSetup();

	bool init();

};

