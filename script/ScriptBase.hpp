#pragma once
#include <string>
#include <sstream>

namespace nde {
#define THROW(msg,...) raiseError(msg, __FILE__, __LINE__, ##__VA_ARGS__);

template<class ErrorClass>
class ScriptBase {
protected:
	std::string errmsg;
	bool haserror;
public:
	ScriptBase() : haserror(false) {}
	virtual ~ScriptBase() {}

	bool hasError(const std::string* s) const { s = &errmsg; return haserror; }

protected:
	void setError(std::string s) {
		errmsg = s;
		haserror = true;
	}

	template <typename... Args>
	void raiseError(std::string s, std::string file, size_t line, Args... args) {
		std::stringstream ss;
		ss << "[" << file << ":" << line << "] " << s;
		throw ErrorClass(ss.str(), std::forward<Args>(args)...);
	}
};

} // namespace nde


