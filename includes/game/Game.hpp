#pragma once
/*
 * Game.h
 *
 *  Created on: 2011-12-01
 *      Author: richard
 */

#include "game/Camera.hpp"
#include "game/Input.hpp"
#include "game/World.hpp"
#include "graphics/Renderer.hpp"
#include "resources/Assets.hpp"
#include "resources/Material.hpp"

namespace nde {

class Game {
	Assets assets;
	Camera camera;
	Input input;
	Renderer renderer;
	World world;


	SDL_Event event;

	scalar fov;

	bool haserror;
	bool shutdown;
	std::string errorstring;

public:
	static Game& getInstance() {
		static Game instance;
		return instance;
	}
	virtual ~Game();

	bool loadScene(const std::string& path) {
		return getWorld().getScene().loadScene(path);
	}

	Assets& getAssets() { return assets; }
	Input& getInput() { return input; }
 	World& getWorld() { return world; }



	void setError(const std::string error);
	void stopGame();

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
