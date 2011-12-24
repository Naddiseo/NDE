#include "debug.hpp"

#include "game/Game.hpp"

namespace nde {

void _ERROR(std::string file, size_t line,std::string msg) {
	std::cerr << "Error [" << file << ":" << line << "]: " << msg << std::endl;
	Game::getInstance().setError(msg);
}

void _ERROR(std::string file, size_t line, const std::ostream& msg) {
	std::cerr << "Error [" << file << ":" << line << "]: " << msg << std::endl;
	Game::getInstance().setError("");
}

void _FATAL_ERROR(std::string file, size_t line, const std::ostream& msg) {
	_ERROR(file, line, msg);
	exit(-1);
}


void _FATAL_ERROR(std::string file, size_t line, std::string msg) {
	_ERROR(file, line, msg);
	exit(-1);
}

}
