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

void KeyboardMapSetup::reset_camera(size_t mods) {}
void KeyboardMapSetup::screenshot(size_t mods) {}

KeyboardMapSetup::KeyboardMapSetup() {

}

KeyboardMapSetup::~KeyboardMapSetup() {}

bool KeyboardMapSetup::init() {
	// TODO:
#if 0
	nde::KeyboardMap& keymap = input->getKeyMap();

	keymap.installCallback((SDLKey)SGET_I("key_quit"), std::bind<void>(&KeyboardMapSetup::quit, this, std::placeholders::_2));

	keymap.installCallback((SDLKey)SGET_I("key_look_up"), std::bind<void>(&KeyboardMapSetup::look_up, this, std::placeholders::_2));
	keymap.installCallback((SDLKey)SGET_I("key_look_down"), std::bind<void>(&KeyboardMapSetup::look_down, this, std::placeholders::_2));
	keymap.installCallback((SDLKey)SGET_I("key_look_left"), std::bind<void>(&KeyboardMapSetup::look_left, this, std::placeholders::_2));
	keymap.installCallback((SDLKey)SGET_I("key_look_right"), std::bind<void>(&KeyboardMapSetup::look_right, this, std::placeholders::_2));

	keymap.installCallback((SDLKey)SGET_I("key_move_up"), std::bind<void>(&KeyboardMapSetup::move_up, this, std::placeholders::_2));
	keymap.installCallback((SDLKey)SGET_I("key_move_down"), std::bind<void>(&KeyboardMapSetup::move_down, this, std::placeholders::_2));
	keymap.installCallback((SDLKey)SGET_I("key_move_left"), std::bind<void>(&KeyboardMapSetup::move_left, this, std::placeholders::_2));
	keymap.installCallback((SDLKey)SGET_I("key_move_right"), std::bind<void>(&KeyboardMapSetup::move_right, this, std::placeholders::_2));

	keymap.installCallback((SDLKey)SGET_I("key_camera_reset"), std::bind<void>(&KeyboardMapSetup::reset_camera, this, std::placeholders::_2));
	keymap.installCallback((SDLKey)SGET_I("key_screenshot"), std::bind<void>(&KeyboardMapSetup::screenshot, this, std::placeholders::_2));
#endif
	return true;
}
