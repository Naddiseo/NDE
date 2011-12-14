#pragma once
#include <btBulletDynamicsCommon.h>
#include "game/Scene.hpp"


namespace nde {

class World {
	Scene scene;
	btAlignedObjectArray<btCollisionShape*> collisionShapes;
	btDefaultCollisionConfiguration* collisionConfig;
	btCollisionDispatcher* dispatcher;
	btDbvtBroadphase* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;

public:
	World();
	virtual ~World();

	void addRigidBody(btRigidBody* body);

	void step();

	Scene& getScene() { return scene; }
private:

};

} // namespace nde
