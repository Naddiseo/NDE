#pragma once
/*
 * Game.h
 *
 *  Created on: 2011-12-01
 *      Author: richard
 */
#include <vector>

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

	scalar fov;

	bool haserror;
	bool shutdown;
	std::string errorstring;


	std::vector<EngineModule*> modules;
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
 	Camera& getCamera() { return camera; }

 	void addModule(EngineModule* module) { modules.push_back(module); }


	void setError(const std::string error);
	void stopGame(bool _error = false);

	void mainLoop();
private:
	Game();
	Game(Game const&);
	void operator=(Game const&);

};

} /* namespace nde */
