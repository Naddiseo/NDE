#pragma once
namespace nde {
#ifdef NDEBUG
#	include <iostream>
#	include <cstdlib>
#	include <cassert>
#	include "game/Game.hpp"

#	define _PRINT(T, x) std::cerr << T " [" << __FILE__ << ":" << __LINE__ << "]" << x << std::endl

#	define D(x) _PRINT("D", x)

#	define LOG(x) _PRINT("LOG", x)
#	define WARN(x) _PRINT("Warning", x)
#	define ERROR(x) { _PRINT("Error", x); Game::getInstance().setError(msg); }

#else
#	define D(x)
#	define LOG(x)
#	define WARN(x)
#	define ERROR(x)

#endif

void FATAL_ERROR(std::string msg);

}
