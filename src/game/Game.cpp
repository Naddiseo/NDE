#include "game/Game.hpp"

namespace nde {

Game::Game()
	: haserror(false), shutdown(false){}

Game::~Game() {}


void Game::setError(const std::string error) {
	errorstring = error;
	stopGame();
}

void Game::stopGame(bool _error) {
	shutdown = true;
	haserror = _error;
}



} // namespace nde
