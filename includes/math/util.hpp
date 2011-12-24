#pragma once

#include "math/vector.hpp"

#define PI 3.14159265358979
#define DEG2RAD(x) ((x)*(PI/360.0))
#define RAD2DEG(x) ((x)*(360.0/PI))

namespace nde
{

// axis must be normalized
// out doesn't have to
void RotateAround(scalar theta, const Vector3f& axis, Vector3f& out);

}
