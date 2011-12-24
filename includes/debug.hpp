#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>

namespace nde {

#ifdef NDEBUG

#	define _PRINT(T, x) std::cerr << T << " [" << __FILE__ << ":" << __LINE__ << "]" << x << std::endl

#	define D(x) _PRINT("D", x)

#	define NDE_LOG(x) _PRINT("LOG", x)
#	define NDE_WARN(x) _PRINT("Warning", x)

void _ERROR(std::string file, size_t line, std::string msg);
void _ERROR(std::string file, size_t line, const std::ostream& o);
#	define NDE_ERROR(x) _ERROR(__FILE__, __LINE__, x)
#else
#	define D(x)
#	define NDE_LOG(x)
#	define NDE_WARN(x)
#	define _ERROR(x,y,z)
#	define NDE_ERROR(x)
#endif


void _FATAL_ERROR(std::string file, size_t line, std::string msg);
void _FATAL_ERROR(std::string file, size_t line, const std::ostream& msg);
#define NDE_FATAL_ERROR(x) _FATAL_ERROR(__FILE__, __LINE__, x)
}
