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

void ERROR(std::string msg);


#else
#	define D(x)
#	define LOG(x)
#	define WARN(x)
#	define ERROR(x)

#endif

void FATAL_ERROR(std::ostream msg);

}
