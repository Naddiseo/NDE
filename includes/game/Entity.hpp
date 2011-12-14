#pragma once
#include <btBulletDynamicsCommon.h>
#include "common.hpp"
#include "resources/Mesh.hpp"

namespace nde {

class Entity {
	btRigidBody* body; // body in the physics engine
	btScalar mass;
	Vector3f localIntertia;
	btTransform location;
	Mesh mesh; // body in the 3d engine
public:
	Entity();
	virtual ~Entity();

	void setMass(btScalar _mass) { mass = _mass; }
	void setOrigin(Vector3f origin) { location.setOrigin(origin); }

	void tick();

};

} // namespace nde
