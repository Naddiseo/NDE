#pragma once
#include <map>
#include <string>
#include <sstream>
#include "common.hpp"

namespace nde {

class Settings {
	typedef std::map<std::string, std::string> settings_t;


	settings_t settings;
public:
	static Settings& getInstance() {
		static Settings instance;
		return instance;
	}
	virtual ~Settings();

	int get_int(const std::string& key);
	scalar get_flt(const std::string& key);
	std::string& get_str(const std::string& key);
	Vector3f get_v3f(const std::string& key);

private:
	Settings();
	Settings(Settings const&);
	void operator=(Settings const&);
};


#define SGET_I(key) Settings::getInstance().get_int(key)
#define SGET_F(key) Settings::getInstance().get_flt(key)
#define SGET_S(key) Settings::getInstance().get_str(key)
#define SGET_V(key) Settings::getInstance().get_v3f(key)

} // namespace nde
