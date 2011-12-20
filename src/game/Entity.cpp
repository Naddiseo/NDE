#include "game/Entity.hpp"

#include "game/World.hpp"
#include "game/Game.hpp"
#include "resources/AssetsLoader.hpp"

namespace nde {

Entity::Entity(World* _world) {
	world = _world;
	body = NULL;
	mass = 0.0;

	location.setIdentity();
}

Entity::~Entity() {
	// mesh will be deleted in assets.cpp
}

void Entity::addCollisionShape(btCollisionShape* shape) {
	world->addCollisionShape(shape);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(location);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, {0,0,0});
	body = new btRigidBody(rbInfo);
	body->setContactProcessingThreshold(BT_LARGE_FLOAT);

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

	if (newPos.y < -100.f) {
		onDie(); // TODO: send a message that we died
	}

}

void Entity::createBox(Vector3f linVel) {
	Face* face;
	body->setLinearFactor({1, 1, 1});

	body->setLinearVelocity(linVel);
	body->setAngularVelocity({0,0,0});
	body->setCcdMotionThreshold(0.5);
	body->setCcdSweptSphereRadius(0.9f);

	mesh = Game::getInstance().getAssets().allocMesh();

	face = mesh->allocFace();
	face->col = Color("a", ((float)rand()/(float)RAND_MAX), ((float)rand()/(float)RAND_MAX), ((float)rand()/(float)RAND_MAX));
	face->add(mesh->add(0, 0, 0));
	face->add(mesh->add(0, 0, 5));
	face->add(mesh->add(5, 0, 0));

	face = mesh->allocFace();
	face->col = Color("a", ((float)rand()/(float)RAND_MAX), ((float)rand()/(float)RAND_MAX), ((float)rand()/(float)RAND_MAX));
	face->add(mesh->add(0, 0, 5));
	face->add(mesh->add(.33*5, 1*5, .33*5));
	face->add(mesh->add(5, 0, 0));

	face = mesh->allocFace();
	face->col = Color("a", ((float)rand()/(float)RAND_MAX), ((float)rand()/(float)RAND_MAX), ((float)rand()/(float)RAND_MAX));
	face->add(mesh->add(1*5, 0, 0));
	face->add(mesh->add(.33*5, 1*5, .33*5));
	face->add(mesh->add(0, 0, 0));

	face = mesh->allocFace();
	face->col = Color("a", ((float)rand()/(float)RAND_MAX), ((float)rand()/(float)RAND_MAX), ((float)rand()/(float)RAND_MAX));
	face->add(mesh->add(0, 0, 0));
	face->add(mesh->add(.33*5, 1*5, .33*5));
	face->add(mesh->add(1*5, 0, 0));
}

void Entity::onDie() {
	world->getScene().removeRenderObject(this);
}

} //namespace nde
