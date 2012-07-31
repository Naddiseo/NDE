#include "math/Utils.hpp"
#include <cmath>

namespace nde {

Utils::Utils() {}

Utils::~Utils() {}

void RotateAround(scalar theta, const Vector3f& axis, Vector3f& out) {
	// out -> a + b, b.axis = 0
	scalar r = out.dot(axis);
	Vector3f a = r * axis;
	Vector3f b = out - a;

	// l = b.length
	// b = b / l
	scalar l = b.normalise();

	// s = l * sin(theta)
	// c = l * cos(theta)
	scalar s = l * std::sin(theta);
	scalar c = l * std::cos(theta);

	// do in one step so no temp vector needed
	// out <- a + rotate b
	out.x = a.x + b.x * c + s * (b.z * axis.y - b.y * axis.z);
	out.y = a.y + b.y * c + s * (b.x * axis.z - b.z * axis.x);
	out.z = a.z + b.z * c + s * (b.y * axis.x - b.x * axis.y);
}

} // namespace nde

