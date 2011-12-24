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
#include "game/Entity.hpp"
#include "game/KeyboardMap.hpp"
#include "graphics/Renderer.hpp"
#include "game/Scene.hpp"
#include "game/Settings.hpp"
#include "resources/Terrain.hpp"
#include "graphics/SkyBox.hpp"
#include "game/EngineModule.hpp"

#undef SGET_I
#undef SGET_F
#undef SGET_S
#undef SGET_V

#define SGET_I(key) nde::Settings::getInstance().get_int(key)
#define SGET_F(key) nde::Settings::getInstance().get_flt(key)
#define SGET_S(key) nde::Settings::getInstance().get_str(key)
#define SGET_V(key) nde::Settings::getInstance().get_v3f(key)
