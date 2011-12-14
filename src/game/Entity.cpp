#include "game/Entity.hpp"


namespace nde {

Entity::Entity() : mass(0.0), localIntertia(0, 0, 0) {

	location.setIdentity();
}

Entity::~Entity() {
}

void Entity::tick() {
	if (body && body->getMotionState()) {
		Vector3f newPos;
		btTransform trans;
		body->getMotionState()->getWorldTransform(trans);

		newPos.x = trans.getOrigin().getX();
		newPos.y = trans.getOrigin().getY();
		newPos.z = trans.getOrigin().getZ();

		mesh.render(newPos);
	}
}

} //namespace nde
