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

	scalar fov;

	bool haserror;
	bool shutdown;
	const char* errorstring;
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

	World& getWorld() { return world; }

	void setError(const char* errstr) { haserror = true; errorstring = errstr; }

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
