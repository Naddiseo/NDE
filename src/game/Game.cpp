/*
 * Game.cpp
 *
 *  Created on: 2011-12-01
 *      Author: richard
 */
#include <SDL/SDL.h>
#include <IL/ilu.h>

#include "game/Game.hpp"
#include "game/Settings.hpp"
#include "game/Entity.hpp"
#include "graphics/IsRendered.hpp"
#include "graphics/Face.hpp"
#include "game/Entity.hpp"

#ifdef WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#define _WIN32_WINNT 0x0500
	#include <windows.h>
#endif

namespace nde {

void Game::setError(const std::string error) {
	errorstring = error;
	stopGame();
}

void Game::stopGame() {
	shutdown = true;
	haserror = true;
}

Game::Game()
	: haserror(false), shutdown(false)
{
	camera.setPosition(SGET_V("cam_pos"));
	camera.rotate(SGET_F("cam_phi"), SGET_F("cam_theta"));
	
#ifdef WINDOWS
	//HWND hWnd = GetConsoleWindow();
	//ShowWindow(hWnd, SW_HIDE);
#endif
}

Game::~Game() {}


void
Game::mainLoop() {
	static iGraphicsLibrary* graphics = NULL;
	GLibrary gl;

#ifdef USE_OPENGL
	gl = GLibrary::OPENGL;
#endif


	if (!renderer.init(gl)) {
		NDE_ERROR("Couldn't init renderer");
	}
	graphics = renderer.getGraphics();

	if (!assets.init()) {
		NDE_ERROR("Couldn't init assets");
	}
	


	camera.setGame(this);
	camera.setGraphics(graphics);
	camera.setInput(&input);
	camera.setWorld(&world);

	world.setGame(this);
	world.setGraphics(graphics);
	world.setInput(&input);
	world.setCamera(&camera);


	while (!(haserror || shutdown)) {
		graphics->startScene();

		input.pollEvents();

		graphics->clearScreen();
		graphics->setMatrixMode(MatrixMode::MODELVIEW);
		graphics->setIdentity();

		camera.render();
		world.step();

		for (Entity* r : world.getScene().getToRender()) {
			r->tick();
		}

		graphics->endScene();
	}

	if (haserror) {

		std::cerr << "Game Error: " << errorstring << std::endl;
	}
}

} /* namespace nde */
