#pragma once
#include <map>
#include <string>
#include <sstream>
#include "common.hpp"

namespace nde {

struct SettingsValue {
	enum class _type : char {
		STRING,
		FLOAT,
		INT,
		VECTOR
	} type;

	std::string str_val;
	union {
		scalar      flt_val;
		int         int_val;
	};
	Vector3f    v3f_val;

	SettingsValue() {}
};

class Settings {
	typedef std::map<std::string, SettingsValue> settings_t;


	settings_t settings;
public:
	static Settings& getInstance() {
		static Settings instance;
		return instance;
	}
	virtual ~Settings();

	void set(const std::string key, std::string val);
	void set(const std::string key, scalar val);
	void set(const std::string key, int val);
	void set(const std::string key, Vector3f& val);

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
