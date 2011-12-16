#pragma once
#include <btBulletDynamicsCommon.h>
#include "common.hpp"
#include "resources/Mesh.hpp"

namespace nde {

class Entity {
protected:

	btRigidBody* body; // body in the physics engine
	btScalar mass;
	btTransform location;
	Mesh* mesh; // body in the 3d engine

	btAlignedObjectArray<btCollisionShape*> collisionShapes;
public:
	Entity();
	virtual ~Entity();

	void setMass(btScalar _mass) { mass = _mass; }
	void setMesh(Mesh* _mesh) { mesh = _mesh; }
	void setOrigin(Vector3f origin) { location.setOrigin(origin); }
	void setOrientation(Vector3f origin) { }

	void addCollisionShape(btCollisionShape* shape);

	void tick();

	virtual void predraw() {}
	virtual void postdraw() {}

};

} // namespace nde
