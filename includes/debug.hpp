#pragma once
#include <iostream>
#include <cstdlib>
#include <cassert>

namespace nde {
#ifdef NDEBUG

#	define _PRINT(T, x) std::cerr << T " [" << __FILE__ << ":" << __LINE__ << "]" << x << std::endl

#	define D(x) _PRINT("D", x)

#	define LOG(x) _PRINT("LOG", x)
#	define WARN(x) _PRINT("Warning", x)

void _ERROR(std::string file, size_t line, std::string msg);
#	define ERROR(x) _ERROR(__FILE__, __LINE__, x)

#else
#	define D(x)
#	define LOG(x)
#	define WARN(x)
#	define _ERROR(x,y,z)
#	define ERROR(x)

#endif

void _FATAL_ERROR(std::string file, size_t line, std::string msg);
#define FATAL_ERROR(x) _FATAL_ERROR(__FILE__, __LINE__, x)
}
