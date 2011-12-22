#include "game/Settings.hpp"
#include <sstream>

namespace nde {

Settings::Settings() {
	set("HEIGHT", "600");
	set("WIDTH", "800");

	set("cam_pos", {20, 5, 20});
	set("cam_dir", {0, -45, 0});
	set("cam_forward", {1, 0, 1});
	set("cam_upward", {0, 1, 0});

	set("key_quit", SDLK_q);

	set("key_look_up", SDLK_UP);
	set("key_look_down", SDLK_DOWN);
	set("key_look_left", SDLK_LEFT);
	set("key_look_right", SDLK_RIGHT);

	set("key_move_up", SDLK_w);
	set("key_move_down", SDLK_s);
	set("key_move_left", SDLK_a);
	set("key_move_right", SDLK_d);

	set("key_camera_reset", SDLK_KP0);
	set("key_screenshot", SDLK_PRINT);
}

Settings::~Settings() {}

void Settings::set(const std::string key, std::string val) {
	SettingsValue value;
	value.type = SettingsValue::_type::STRING;
	value.str_val = val;

	settings[key] = value;
}
void Settings::set(const std::string key, scalar val) {
	SettingsValue value;
	value.type = SettingsValue::_type::FLOAT;
	value.flt_val = val;

	settings[key] = value;
}
void Settings::set(const std::string key, int val) {
	SettingsValue value;
	value.type = SettingsValue::_type::INT;
	value.int_val = val;

	settings[key] = value;
}
void Settings::set(const std::string key, Vector3f& val) {
	SettingsValue value;
	value.type = SettingsValue::_type::VECTOR;
	value.v3f_val = val;

	settings[key] = value;
}

int Settings::get_int(const std::string& key) {
	return settings[key].int_val;
}

scalar Settings::get_flt(const std::string& key) {
	return settings[key].flt_val;
}

std::string& Settings::get_str(const std::string& key) {
	return settings[key].str_val;
}

Vector3f Settings::get_v3f(const std::string& key) {
	return settings[key].v3f_val;
}

} //namespace nde
