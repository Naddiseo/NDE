#pragma once
#include <map>
#include <string>
#include <sstream>
#include "common.hpp"

namespace nde {

class SettingsValue
{
	enum class Type : char {
		STRING,
		SCALAR,
		INT,
		VECTOR
	} type;

	std::string str_val;
	union {
		scalar    flt_val;
		int       int_val;
	};
	Vector3f    v3f_val;

public:
	SettingsValue(const std::string& value): type(Type::STRING), str_val(value) {}
	SettingsValue(scalar value): type(Type::SCALAR), flt_val(value) {}
	SettingsValue(int value): type(Type::INT), int_val(value) {}
	SettingsValue(const Vector3f& value): type(Type::VECTOR), v3f_val(value) {}
	SettingsValue(): type(Type::INT), int_val(0) {}
	
	operator const std::string&() const { return str_val; }
	operator scalar() const { return flt_val; }
	operator int() const { return int_val; }
	operator const Vector3f&() const { return v3f_val; }
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

	void set(const std::string& key, const std::string& val);
	void set(const std::string& key, scalar val);
	void set(const std::string& key, int val);
	void set(const std::string& key, const Vector3f& val);

	int get_int(const std::string& key);
	scalar get_flt(const std::string& key);
	const std::string& get_str(const std::string& key);
	const Vector3f& get_v3f(const std::string& key);
	
	SettingsValue& operator[](const std::string& key);
	const SettingsValue& operator[](const std::string& key) const;
	
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
