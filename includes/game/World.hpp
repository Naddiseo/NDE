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



	std::vector<Entity*> entities;
public:
	World();
	virtual ~World();

	void addRigidBody(btRigidBody* body);
	void addCollisionShape(btCollisionShape* shape);

	void step();

	template<typename ...Args>
	Entity* allocEntity(Args&&... params);

	void shootBox(Vector3f from, Vector3f to);


	Scene& getScene() { return scene; }
private:

};

template<typename ...Args>
Entity* World::allocEntity(Args&&... params) {
	Entity* ret = new Entity(std::forward<Args>(params)...);
	entities.push_back(ret);
	return ret;
}

} // namespace nde
