#include "game/Settings.hpp"
#include <sstream>

namespace nde {

Settings::Settings() {
	settings["HEIGHT"] = "600";
	settings["WIDTH"] = "800";

	settings["cam_pos"]   = "20 5 20";
	settings["cam_phi"]   = "45";
	settings["cam_theta"] = "0";
	settings["cam_rho"]   = "0";
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

Vector3f Settings::get_v3f(const std::string& key) {
	Vector3f ret;
	std::istringstream stream(settings[key]);
	stream >> ret.x >> ret.y >> ret.z;
	return ret;
}

} //namespace nde
