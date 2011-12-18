#include "game/Entity.hpp"
#include "game/Game.hpp"

namespace nde {

Entity::Entity() {
	body = NULL;
	mass = 0.0;

	location.setIdentity();
}

Entity::~Entity() {
	// mesh will be deleted in assets.cpp

	for (int j = 0; j < collisionShapes.size(); j++) {
		btCollisionShape* shape = collisionShapes[j];
		collisionShapes[j] = 0;
		delete shape;
	}
}

void Entity::addCollisionShape(btCollisionShape* shape) {
	collisionShapes.push_back(shape);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(location);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, {0,0,0});
	body = new btRigidBody(rbInfo);

	Game::getInstance().getWorld().addRigidBody(body);

}

void Entity::tick() {
	Vector3f newPos(0, 0, 0);
	if (body && body->getMotionState()) {
		btTransform trans;
		body->getMotionState()->getWorldTransform(trans);
		newPos = trans.getOrigin();
	}
	predraw();
	mesh->render(newPos);
	postdraw();

}

} //namespace nde
