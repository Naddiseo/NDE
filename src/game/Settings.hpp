#pragma once

#include "common.hpp"
#include "math/Vector.hpp"

namespace nde {

class SettingsValue
{
	enum class Type : char {
		STRING = 'S',
		SCALAR = 'R',
		INT = 'I',
		VECTOR = 'V'
	} type;

	std::string str_val;
	union {
		scalar    flt_val;
		int       int_val;
	};
	Vector3f    v3f_val;

	void check(Type type) const {
		if (this->type != type) {
			D("cannot cast setting value of type " << (char)this->type << " to " << (char)type);
			NDE_ERROR("invalid cast of setting value");
		}
	}

public:
	SettingsValue(const std::string& value): type(Type::STRING), str_val(value) {}
	SettingsValue(scalar value): type(Type::SCALAR), flt_val(value) {}
	SettingsValue(int value): type(Type::INT), int_val(value) {}
	SettingsValue(const Vector3f& value): type(Type::VECTOR), v3f_val(value) {}
	SettingsValue(const char * value): type(Type::STRING), str_val(value) {}
	SettingsValue(): type(Type::INT), int_val(0) {}

	operator const std::string&() const { this->check(Type::STRING); return str_val; }
	operator scalar            () const { this->check(Type::SCALAR); return flt_val; }
	operator int               () const { this->check(Type::INT   ); return int_val; }
	operator const Vector3f&   () const { this->check(Type::VECTOR); return v3f_val; }
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

	void set(const std::string& key, const SettingsValue& val);

	int get_int(const std::string& key);
	scalar get_flt(const std::string& key);
	const std::string& get_str(const std::string& key);
	const Vector3f& get_v3f(const std::string& key);

	SettingsValue& operator[](const std::string& key);

private:
	Settings();
	Settings(Settings const&);
	void operator=(Settings const&);
};

#define SGET_I(key) Settings::getInstance().get_int(key)
#define SGET_F(key) Settings::getInstance().get_flt(key)
#define SGET_S(key) Settings::getInstance().get_str(key)
#define SGET_V(key) Settings::getInstance().get_v3f(key)

}
