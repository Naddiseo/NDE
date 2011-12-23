#include "game/World.hpp"

#include <btBulletDynamicsCommon.h>

#include "game/Entity.hpp"
#include "game/Scene.hpp"

namespace nde {

World::World() {

	collisionConfig = new btDefaultCollisionConfiguration();
	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	dispatcher = new	btCollisionDispatcher(collisionConfig);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,overlappingPairCache,solver,collisionConfig);

	dynamicsWorld->setGravity(btVector3(0, -9.81, 0));

	box_size = 1;
	box_speed = 25;

}

World::~World() {
	//cleanup in the reverse order of creation/initialization

	//remove the rigidbodies from the dynamics world and delete them
	for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--) {
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState()) {
			delete body->getMotionState();
		}
		dynamicsWorld->removeCollisionObject( obj );
		delete obj;
	}

	//delete collision shapes
	for (int j = 0; j < collisionShapes.size(); j++) {
		btCollisionShape* shape = collisionShapes[j];
		collisionShapes[j] = 0;
		delete shape;
	}

	for (Entity* e : entities) {
		delete e;
	}

	delete dynamicsWorld;
	delete solver;
	delete overlappingPairCache;
	delete dispatcher;
	delete collisionConfig;
}

void World::addRigidBody(btRigidBody* body) {
	dynamicsWorld->addRigidBody(body);
}

void World::addCollisionShape(btCollisionShape* shape) {
	collisionShapes.push_back(shape);
}

void World::removeRidigBody(btRigidBody* body) {
	dynamicsWorld->removeRigidBody(body);
}

void World::step() {
	dynamicsWorld->stepSimulation(1.f/60.f,10);
}

void
World::shootBox(Vector3f from, Vector3f to) {
	float actual_box_size = box_size * 2.f;
	btBoxShape* shape = new btBoxShape(btVector3(actual_box_size,actual_box_size,actual_box_size));
	scalar mass = actual_box_size*actual_box_size*actual_box_size;
	btTransform startTransform;
	Vector3f linVel(to.x-from.x, to.y-from.y, to.z-from.z);
	linVel.normalise();

	// move the box infront of the camera
	from += linVel * box_size *2;

	shape->initializePolyhedralFeatures();

	//std::cout << "From " << from << " to " << to <<std::endl;

	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0, 1, 0, 1));

	Entity* box = new Entity(this);
	box->setMass(mass);
	box->setTransform(startTransform);
	box->addCollisionShape(shape);
	box->getWorldTransform().setOrigin(from);
	box->getWorldTransform().setRotation(btQuaternion(0, 2, 0, 1));

	linVel *= box_speed;
	box->createBox(linVel);

	getScene().addRenderObjects(box);




}

} //namespace nde
