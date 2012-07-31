#pragma once
/*
 * NDE.hpp
 *
 *  Created on: 2012-07-29
 *     
 */

#if WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#define _WIN32_WINNT 0x0500
	#include <windows.h>
#endif

#include "common.hpp"

#include "game/Game.hpp"



#undef SGET_I
#undef SGET_F
#undef SGET_S
#undef SGET_V

#define SGET_I(key) nde::Settings::getInstance().get_int(key)
#define SGET_F(key) nde::Settings::getInstance().get_flt(key)
#define SGET_S(key) nde::Settings::getInstance().get_str(key)
#define SGET_V(key) nde::Settings::getInstance().get_v3f(key)
