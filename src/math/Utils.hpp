#pragma once

#include "math/Vector.hpp"

#define M_TAU (6.28318530717958647692)

#define DEG2RAD(x) ((x)*(M_TAU/360.0))
#define RAD2DEG(x) ((x)*(360.0/M_TAU))

namespace nde {

class Utils {
public:
	Utils();
	virtual ~Utils();
};


// axis must be normalized
// out doesn't have to
void RotateAround(scalar theta, const Vector3f& axis, Vector3f& out);

} // namespace nde


