#pragma once
#include <btBulletDynamicsCommon.h>
#include "common.hpp"
#include "resources/Mesh.hpp"

namespace nde {

class World;

class Entity {
protected:
	World* world;

	btRigidBody* body; // body in the physics engine
	btScalar mass;
	btTransform location;
	Mesh* mesh; // body in the 3d engine

public:
	Entity(World* _world);
	virtual ~Entity();


	void setWorld(World* _world) { world = _world; }
	void setMass(btScalar _mass) { mass = _mass; }
	void setMesh(Mesh* _mesh) { mesh = _mesh; }
	void setOrigin(Vector3f origin) { location.setOrigin(origin); }
	void setRotation(btQuaternion _q) { location.setRotation(_q); }
	void setOrientation(Vector3f origin) { }
	void setTransform(btTransform _t) { location = _t; }

	void addCollisionShape(btCollisionShape* shape);

	btTransform& getWorldTransform() { return body->getWorldTransform(); }

	virtual void tick();

	virtual void predraw() {}
	virtual void postdraw() {}


	virtual void onDie();


	void createBox(Vector3f linvel);

};

} // namespace nde
