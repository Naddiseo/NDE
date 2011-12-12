#include "game/Settings.hpp"
#include <sstream>

namespace nde {

Settings::Settings() : settings() {
	settings["HEIGHT"] = "480";
	settings["WIDTH"] = "640";
}

Settings::~Settings() {}

int Settings::get_int(const std::string& key) {
	int ret = 0;
	std::istringstream(settings[key]) >> ret;
	return ret;
}

std::string& Settings::get_str(const std::string& key) {
	return settings[key];
}

} //namespace nde
