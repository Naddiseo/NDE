#pragma once
/*
 * common.hpp
 *
 *  Created on: 2012-07-29
 *     
 */


#define __GXX_EXPERIMENTAL_CXX0X__ 1

#include <string>
#include <vector>
#include <map>
#include <utility> // for std::forward
#include <cstddef> // for size_t
#include <cstdint>
#include <memory> // for shared_ptr, make_shared

#include <SDL/SDL.h>
#ifdef USE_OPENGL
#	include <GL/gl.h>
#	include <GL/glu.h>
#endif
#include "debug.hpp"

typedef float scalar;

#if WINDOWS
#	define BEGIN_MAIN \
	int APIENTRY WinMain(\
		HINSTANCE hInstance,\
		HINSTANCE hPrevInstance,\
		LPSTR     lpCmdLine,\
		int       nCmdShow\
	)
#else
#	define BEGIN_MAIN int main(int argc, char* argv[])
#endif
