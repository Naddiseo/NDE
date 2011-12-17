#include "graphics/IsRendered.hpp"
#include "graphics/Face.hpp"


namespace nde {

IsRendered::IsRendered() {}

IsRendered::~IsRendered() {
	for (Face* f : faces) {
		if (f) {
			delete f;
		}
	}
}

} //namespace nde
