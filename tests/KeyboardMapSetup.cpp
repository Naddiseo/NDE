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

void KeyboardMapSetup::look_up(size_t mods) {
	camera->rotate(0, 0.015625);
}

void KeyboardMapSetup::look_down(size_t mods) {
	camera->rotate(0, -0.015625);
}

void KeyboardMapSetup::look_left(size_t mods) {
	camera->rotate(-0.015625, 0);
}
void KeyboardMapSetup::look_right(size_t mods) {
	camera->rotate(0.015625, 0);
}

void KeyboardMapSetup::move_up(size_t mods) {
	if ((mods & KMOD_LCTRL) == KMOD_LCTRL) {
		Vector3f tmp(0, 0.375 * 1, 0);
		camera->move(tmp);
	}
	else {
		camera->moveForwards(0.375 * 1);
	}
}

void KeyboardMapSetup::move_down(size_t mods) {
	if ((mods& KMOD_LCTRL) == KMOD_LCTRL) {
		Vector3f tmp(0, -0.375 * 1, 0);
		camera->move(tmp);
	}
	else {
		camera->moveForwards(-0.375 * 1);
	}
}

void KeyboardMapSetup::move_left(size_t mods) {
	camera->strafeRight(0.125 * 1);
}
void KeyboardMapSetup::move_right(size_t mods) {
	camera->strafeRight(-0.125 * 1);
}

void KeyboardMapSetup::camera_reset(size_t mods) {
	if ((mods & KMOD_LCTRL) == KMOD_LCTRL) {
		Vector3f tmp = -camera->getPosition();
		camera->move(tmp);
	}
	else {
		camera->rotate(-camera->getPhi(), -camera->getTheta());
	}
}
void KeyboardMapSetup::screenshot(size_t mods) {
	graphics->takeScreenshot("Screenshot.png");
}

KeyboardMapSetup::KeyboardMapSetup() {}

KeyboardMapSetup::~KeyboardMapSetup() {}

bool KeyboardMapSetup::init() {
	nde::KeyboardMap& keymap = input->getKeyMap();
	
	#define INSTALL_CALLBACK(name) { \
		keymap.installCallback(\
			(SDLKey)SGET_I("key_" #name), \
			std::bind(&KeyboardMapSetup::name, this, std::placeholders::_1) \
		); \
	}
	
	INSTALL_CALLBACK(quit);
	keymap.installCallback(SDLKey::SDLK_ESCAPE, std::bind(&KeyboardMapSetup::quit, this, std::placeholders::_1));
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
