#pragma once
/*
 * Game.h
 *
 *  Created on: 2011-12-01
 *      Author: richard
 */

#include "resources/Assets.hpp"
#include "game/World.hpp"
#include "graphics/Renderer.hpp"
#include "game/Camera.hpp"
#include "resources/Material.hpp"

namespace nde {

class Game {
	Assets assets;
	World world;
	Renderer renderer;
	Camera camera;


	SDL_Event event;

	float fov;
public:
	static Game& getInstance() {
		static Game instance;
		return instance;
	}
	virtual ~Game();

	bool loadScene(const std::string& path) {
		return getWorld().getScene().loadScene(path);
	}

	GLuint loadAsset(const std::string& path) {
		static int id = 0;
		id++;
		Material m(id, path);
		return m.image_id;

	}

	World& getWorld() {
		return world;
	}

	void mainLoop();
private:
	Game();
	Game(Game const&);
	void operator=(Game const&);

	void handleMouse();
	void handleEvents();

	void drawAxis();

};

} /* namespace nde */
