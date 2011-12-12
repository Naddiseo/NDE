#pragma once
#include <map>
#include <string>
#include <sstream>

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
	std::string& get_str(const std::string& key);



private:
	Settings();
	Settings(Settings const&);
	void operator=(Settings const&);
};

} // namespace nde
