#include "graphics/iGraphicsLibrary.hpp"
#include "game/Settings.hpp"

namespace nde {

iGraphicsLibrary::iGraphicsLibrary() {
	height = Settings::getInstance().get_int("HEIGHT");
	width = Settings::getInstance().get_int("WIDTH");

}

iGraphicsLibrary::~iGraphicsLibrary() {}

}

