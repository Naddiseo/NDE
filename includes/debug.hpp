#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>

namespace nde {

#ifdef NDEBUG

#	define _PRINT(T, x) std::cerr << T << " [" << __FILE__ << ":" << __LINE__ << "] " << x << std::endl

#	define D(x) _PRINT("D", x)
#	define DIF(cond, x) do { if (cond) { _PRINT("D", x); } } while(0);
#	define NDE_LOG(x) _PRINT("LOG", x)
#	define NDE_WARN(x) _PRINT("Warning", x)

void _ERROR(std::string file, size_t line, std::string msg);
void _ERROR(std::string file, size_t line, const std::ostream& o);
#	define NDE_ERROR(x) _ERROR(__FILE__, __LINE__, x)
#	define NDE_ERROR_UNLESS(cond, msg) do { if (!(cond)) { NDE_ERROR(msg); } } while(0);
#else
#	define D(x)
#	define DIF(cond, x)
#	define NDE_LOG(x)
#	define NDE_WARN(x)
#	define _ERROR(x,y,z)
#	define NDE_ERROR(x)
#	define NDE_ERROR_UNLESS(cond, msg)
#endif


void _FATAL_ERROR(std::string file, size_t line, std::string msg);
void _FATAL_ERROR(std::string file, size_t line, const std::ostream& msg);
#define NDE_FATAL_ERROR(x) _FATAL_ERROR(__FILE__, __LINE__, x)
}
