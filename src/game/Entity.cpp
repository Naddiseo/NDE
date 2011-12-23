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
	body->setAngularVelocity({25,15,10});
	body->setCcdMotionThreshold(0.3);
	body->setCcdSweptSphereRadius(0.9f);

	mesh = Game::getInstance().getAssets().allocMesh();
	scalar box_size = world->box_size;

	Vector3f* vertexes[] = {
		mesh->add(-box_size, box_size, -box_size),
		mesh->add(box_size, box_size, -box_size),
		mesh->add(-box_size, -box_size, -box_size),
		mesh->add(box_size, -box_size, -box_size),
		mesh->add(-box_size, box_size, box_size),
		mesh->add(box_size, box_size, box_size),
		mesh->add(-box_size, -box_size, box_size),
		mesh->add(box_size, -box_size, box_size),
	};

	short indices[][3] =
	{
	    {0, 1, 2},    // side 1
	    {2, 1, 3},
	    {4, 0, 6},    // side 2
	    {6, 0, 2},
	    {7, 5, 6},    // side 3
	    {6, 5, 4},
	    {3, 1, 7},    // side 4
	    {7, 1, 5},
	    {4, 5, 0},    // side 5
	    {0, 5, 1},
	    {3, 7, 2},    // side 6
	    {2, 7, 6},
	};

	for (short* v : indices) {
		face = mesh->allocFace();
		face->col = Color("a", ((float)rand()/(float)RAND_MAX), ((float)rand()/(float)RAND_MAX), ((float)rand()/(float)RAND_MAX));
		face->add(vertexes[v[0]]);
		face->add(vertexes[v[1]]);
		face->add(vertexes[v[2]]);
	}

}

void Entity::onDie() {
	world->getScene().removeRenderObject(this);
}

} //namespace nde
