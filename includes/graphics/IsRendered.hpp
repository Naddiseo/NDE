#pragma once
#include "common.hpp"

namespace nde {

class IsRendered {
public:
	IsRendered();
	virtual ~IsRendered();

	faces_t faces;
};

} // namespace nde
