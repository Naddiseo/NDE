/*
 * KeyboardMapImpl.cpp
 *
 *  Created on: 2011-12-20
 *      Author: richard
 */

#include "NDE.hpp"
#include "KeyboardMapSetup.hpp"

void KeyboardMapSetup::quit(size_t mods) {
	game->stopGame();
}

void KeyboardMapSetup::look_up(size_t mods) {}
void KeyboardMapSetup::look_down(size_t mods) {}
void KeyboardMapSetup::look_left(size_t mods) {}
void KeyboardMapSetup::look_right(size_t mods) {}

void KeyboardMapSetup::move_up(size_t mods) {}
void KeyboardMapSetup::move_down(size_t mods) {}
void KeyboardMapSetup::move_left(size_t mods) {}
void KeyboardMapSetup::move_right(size_t mods) {}

void KeyboardMapSetup::camera_reset(size_t mods) {}
void KeyboardMapSetup::screenshot(size_t mods) {}

KeyboardMapSetup::KeyboardMapSetup() {

}

KeyboardMapSetup::~KeyboardMapSetup() {}

bool KeyboardMapSetup::init() {
	nde::KeyboardMap& keymap = input->getKeyMap();
	
	#define INSTALL_CALLBACK(name) \
		keymap.installCallback(\
			(SDLKey)SGET_I("key_" #name),\
			std::bind<void>(&KeyboardMapSetup::name, this, std::placeholders::_1)\
		)
	
	INSTALL_CALLBACK(quit);
	INSTALL_CALLBACK(look_up);
	INSTALL_CALLBACK(look_down);
	INSTALL_CALLBACK(look_left);
	INSTALL_CALLBACK(look_right);
	INSTALL_CALLBACK(move_up);
	INSTALL_CALLBACK(move_down);
	INSTALL_CALLBACK(move_left);
	INSTALL_CALLBACK(move_right);
	INSTALL_CALLBACK(camera_reset);
	INSTALL_CALLBACK(screenshot);
	
	#undef INSTALL_CALLBACK
	
	return true;
}
