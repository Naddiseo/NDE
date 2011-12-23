#include "game/Settings.hpp"
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

void Settings::set(const std::string& key, const std::string& val) {
	settings[key] = val;
}
void Settings::set(const std::string& key, scalar val) {
	settings[key] = val;
}
void Settings::set(const std::string& key, int val) {
	settings[key] = val;
}
void Settings::set(const std::string& key, const Vector3f& val) {
	settings[key] = val;
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

} //namespace nde
