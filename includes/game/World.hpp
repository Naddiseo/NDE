#pragma once
#include <btBulletDynamicsCommon.h>
#include "common.hpp"
#include "game/Scene.hpp"


namespace nde {

class World : public EngineModule {
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

	bool init();

	void addRigidBody(btRigidBody* body);
	void addCollisionShape(btCollisionShape* shape);

	void removeRidigBody(btRigidBody* body);

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
