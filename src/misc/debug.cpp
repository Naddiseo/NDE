#include "debug.hpp"
#include "game/Game.hpp"
namespace nde {
#ifdef NDEBUG

void ERROR(std::string msg) { _PRINT("Error", msg);  Game::getInstance().setError(msg); }

#endif

void FATAL_ERROR(std::string msg) {
	ERROR(msg);
	exit(-1);
}
}
