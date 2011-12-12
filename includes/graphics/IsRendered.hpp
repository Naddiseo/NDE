#pragma once
#include "common.hpp"

namespace nde {

class IsRendered {
public:
	IsRendered();
	virtual ~IsRendered();

	virtual void predraw() {}
	virtual void postdraw() {}

	faces_t faces;

	virtual std::string id() { return "IsRendered"; }
};

} // namespace nde
