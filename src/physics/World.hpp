#pragma once

#include <btBulletDynamicsCommon.h>

#ifndef NDE_WORLD_GRAVITY
#	define NDE_WORLD_GRAVITY -9.81
#endif
#ifndef NDE_WORLD_FPS
#	define NDE_WORLD_FPS 60.0
#endif

namespace nde {
class Scene;

class World {
	Scene& owner;

	btAlignedObjectArray<btCollisionShape*> collisionShapes;
	btDefaultCollisionConfiguration* collisionConfig;
	btCollisionDispatcher* dispatcher;
	btDbvtBroadphase* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;


public:
	World(Scene& _owner);
	virtual ~World();

	// Advance the world physics
	void step();
};

} // namespace nde


