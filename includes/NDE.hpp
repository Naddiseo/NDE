#pragma once
/*
 * NDE.hpp
 *
 *  Created on: 2011-12-01
 *      Author: richard
 */
#define __GXX_EXPERIMENTAL_CXX0X__ 1

#if WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#define _WIN32_WINNT 0x0500
	#include <windows.h>
#endif

#include "common.hpp"

#include "game/Game.hpp"
#include "graphics/Renderer.hpp"
#include "game/Scene.hpp"
#include "resources/Terrain.hpp"

