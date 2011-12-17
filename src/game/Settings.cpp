#include "game/Settings.hpp"
#include <sstream>

namespace nde {

Settings::Settings() {
	settings["HEIGHT"] = "600";
	settings["WIDTH"] = "800";

	settings["cam_x"] = "20";
	settings["cam_y"] = "5";
	settings["cam_z"] = "20";

	settings["cam_rot_x"] = "45";
	settings["cam_rot_y"] = "0";
	settings["cam_rot_z"] = "0";


}

Settings::~Settings() {}

int Settings::get_int(const std::string& key) {
	int ret = 0;
	std::istringstream(settings[key]) >> ret;
	return ret;
}

scalar Settings::get_flt(const std::string& key) {
	scalar ret = 0;
	std::istringstream(settings[key]) >> ret;
	return ret;
}

std::string& Settings::get_str(const std::string& key) {
	return settings[key];
}



} //namespace nde
