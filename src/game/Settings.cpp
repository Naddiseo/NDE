#include "game/Settings.hpp"
#include <sstream>

namespace nde {

Settings::Settings() : settings() {
	settings["HEIGHT"] = "480";
	settings["WIDTH"] = "640";

	settings["cam_x"] = "20";
	settings["cam_y"] = "8";
	settings["cam_z"] = "20";

	settings["cam_rot_x"] = "-16";
	settings["cam_rot_y"] = "-90";
	settings["cam_rot_z"] = "0";


}

Settings::~Settings() {}

int Settings::get_int(const std::string& key) {
	int ret = 0;
	std::istringstream(settings[key]) >> ret;
	return ret;
}

float Settings::get_flt(const std::string& key) {
	float ret = 0;
	std::istringstream(settings[key]) >> ret;
	return ret;
}

std::string& Settings::get_str(const std::string& key) {
	return settings[key];
}



} //namespace nde
