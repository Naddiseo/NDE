#include "game/Settings.hpp"

#include "math/vector.hpp"

#include <string>
#include <sstream>

namespace nde {

Settings::Settings() {
	set("HEIGHT", "600");
	set("WIDTH", "800");
	
	set("cam_pos", Vector3f { 20, 5, 20 });
	set("cam_phi", 45.f);
	set("cam_theta", 0.0f);
	set("cam_rho", 0.0f);

	set("key_quit", (int)SDLK_q);

	set("key_look_up", (int)SDLK_UP);
	set("key_look_down", (int)SDLK_DOWN);
	set("key_look_left", (int)SDLK_LEFT);
	set("key_look_right", (int)SDLK_RIGHT);

	set("key_move_up", (int)SDLK_w);
	set("key_move_down", (int)SDLK_s);
	set("key_move_left", (int)SDLK_a);
	set("key_move_right", (int)SDLK_d);

	set("key_camera_reset", (int)SDLK_KP0);
	set("key_screenshot", (int)SDLK_PRINT);
}

Settings::~Settings() {}

void Settings::set(const std::string& key, const SettingsValue& val) {
	settings_t::iterator iter = settings.find(key);
	
	if (iter != settings.end()) {
		iter->second = val;
	} else {
		settings_t::value_type setting(key, val);
		settings.insert(setting);
	}
}

int Settings::get_int(const std::string& key) {
	return settings[key];
}

scalar Settings::get_flt(const std::string& key) {
	return settings[key];
}

const std::string& Settings::get_str(const std::string& key) {
	return settings[key];
}

const Vector3f& Settings::get_v3f(const std::string& key) {
	return settings[key];
}

SettingsValue& Settings::operator[](const std::string& key) {
	return settings[key];
}

} //namespace nde
