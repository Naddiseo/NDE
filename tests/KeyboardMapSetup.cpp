/*
 * KeyboardMapImpl.cpp
 *
 *  Created on: 2011-12-20
 *      Author: richard
 */

#include "NDE.hpp"
#include "KeyboardMapSetup.hpp"



void quit(size_t mods) {}

void look_up(size_t mods) {}
void look_down(size_t mods) {}
void look_left(size_t mods) {}
void look_right(size_t mods) {}

void move_up(size_t mods) {}
void move_down(size_t mods) {}
void move_left(size_t mods) {}
void move_right(size_t mods) {}

void reset_camera(size_t mods) {}
void screenshot(size_t mods) {}

KeyboardMapSetup::KeyboardMapSetup() {
	nde::KeyboardMap& keymap = nde::Game::getInstance().getInput().getKeyMap();

	size_t k = SGET_I("key_quit");

	keymap.installCallback((SDLKey)k, &quit);

	keymap.installCallback((SDLKey)SGET_I("key_look_up"), &look_up);
	keymap.installCallback((SDLKey)SGET_I("key_look_down"), &look_down);
	keymap.installCallback((SDLKey)SGET_I("key_look_left"), &look_left);
	keymap.installCallback((SDLKey)SGET_I("key_look_right"), &look_right);

	keymap.installCallback((SDLKey)SGET_I("key_move_up"), &move_up);
	keymap.installCallback((SDLKey)SGET_I("key_move_down"), &move_down);
	keymap.installCallback((SDLKey)SGET_I("key_move_left"), &move_left);
	keymap.installCallback((SDLKey)SGET_I("key_move_right"), &move_right);

	keymap.installCallback((SDLKey)SGET_I("key_camera_reset"), &reset_camera);
	keymap.installCallback((SDLKey)SGET_I("key_screenshot"), &screenshot);
}

KeyboardMapSetup::~KeyboardMapSetup() {}
