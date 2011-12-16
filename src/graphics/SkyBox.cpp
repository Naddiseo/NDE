/*
 * SkyBox.cpp
 *
 *  Created on: 2011-12-11
 *      Author: richard
 */

#include "graphics/SkyBox.hpp"
#include "game/Game.hpp"
#include "resources/AssetsLoader.hpp"

namespace nde {

SkyBox::SkyBox() {
	// top face
	message_list_t message_list = LoadAssetsFromText("tests/skybox.txt", Game::getInstance().getAssets());

	for (Message message : message_list) {
		switch (message.type) {
		case MessageType::Mesh:
			mesh = Game::getInstance().getAssets().getMesh(message.id);
			break;
		case MessageType::Color:
		case MessageType::Material:
		default:
			break;
		}
	}

	mass = 0.f; // We're a static body

}

SkyBox::~SkyBox() {}

void SkyBox::predraw() {
	glPushMatrix();
	glScalef(50, 50, 50);
	glTranslated(0, 0, 0);
}
void SkyBox::postdraw() {
	glPopMatrix();
}

} /* namespace nde */
