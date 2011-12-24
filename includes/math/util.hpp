#pragma once
#include <cmath>
#include "math/vector.hpp"
#define DEG2RAD(x) ((x)*(M_PI/180.0))
#define RAD2DEG(x) ((x)*(180.0/M_PI))

namespace nde
{

// axis must be normalized
// out doesn't have to
void RotateAround(scalar theta, const Vector3f& axis, Vector3f& out);

}
