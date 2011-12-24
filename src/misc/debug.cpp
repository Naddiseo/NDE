#include "debug.hpp"

#include "game/Game.hpp"

namespace nde {

#ifdef NDEBUG
void _ERROR(std::string file, size_t line,std::string msg) {
	std::cerr << "Error [" << file << ":" << line << "]: " << msg << std::endl;
	Game::getInstance().setError(msg);
}

void _ERROR(std::string file, size_t line,std::ostream msg) {
	std::cerr << "Error [" << file << ":" << line << "]: " << msg << std::endl;
	Game::getInstance().setError("");
}

#endif


void _FATAL_ERROR(std::string file, size_t line, std::ostream msg) {
	_ERROR(file, line, msg);
	exit(-1);
}


void _FATAL_ERROR(std::string file, size_t line, std::string msg) {
	_ERROR(file, line, msg);
	exit(-1);
}

}
