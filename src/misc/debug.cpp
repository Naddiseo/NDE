#include "debug.hpp"
namespace nde {
#ifdef NDEBUG


#endif

void FATAL_ERROR(std::string msg) {
	ERROR(msg);
	exit(-1);
}
}
