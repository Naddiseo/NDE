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
#if 0
	nde::KeyboardMap& keymap = input->getKeyMap();

	nde::keyboard_callback_t f = std::bind(&KeyboardMapSetup::quit, this, std::placeholders::_1);

	keymap.installCallback((SDLKey)SGET_I("key_quit"), f);

	keymap.installCallback((SDLKey)SGET_I("key_look_up"), &KeyboardMapSetup::look_up);
	keymap.installCallback((SDLKey)SGET_I("key_look_down"), &KeyboardMapSetup::look_down);
	keymap.installCallback((SDLKey)SGET_I("key_look_left"), &KeyboardMapSetup::look_left);
	keymap.installCallback((SDLKey)SGET_I("key_look_right"), &KeyboardMapSetup::look_right);

	keymap.installCallback((SDLKey)SGET_I("key_move_up"), &KeyboardMapSetup::move_up);
	keymap.installCallback((SDLKey)SGET_I("key_move_down"), &KeyboardMapSetup::move_down);
	keymap.installCallback((SDLKey)SGET_I("key_move_left"), &KeyboardMapSetup::move_left);
	keymap.installCallback((SDLKey)SGET_I("key_move_right"), &KeyboardMapSetup::move_right);

	keymap.installCallback((SDLKey)SGET_I("key_camera_reset"), &KeyboardMapSetup::reset_camera);
	keymap.installCallback((SDLKey)SGET_I("key_screenshot"), &KeyboardMapSetup::screenshot);
#endif
	return true;
}
