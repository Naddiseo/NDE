/*
 * Box.cpp
 *
 *  Created on: 2011-12-25
 *      Author: richard
 */
#include <btBulletDynamicsCommon.h>

#include "Box.hpp"

Box::Box(nde::World* _world, scalar _mass, scalar _dimension) : Entity(_world) {
	btBoxShape* shape = new btBoxShape({_dimension, _dimension, _dimension});

	mass = _mass;
	dimension = _dimension;

	shape->initializePolyhedralFeatures();

	location.setIdentity();
	location.setRotation({0, 0, 0, 1});

	// Creates body using mass
	addCollisionShape(shape);
}

Box::~Box() {}

void Box::init(Vector3f from, Vector3f dir, scalar speed, nde::iBufferObject* buffer) {
	getWorldTransform().setOrigin(from);
	getWorldTransform().setRotation({0, 0, 0, 1});

	Vector3f linearVelocity(dir);
	linearVelocity.normalise();
	linearVelocity *= speed;

	body->setLinearFactor({1, 1, 1});
	body->setLinearVelocity(linearVelocity);
	body->setAngularVelocity({0, 0, 0});
	body->setCcdMotionThreshold(0.5f);
	body->setCcdSweptSphereRadius(0.9f);

	size_t indices[][3] = {
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

	memcpy(buffer->index_buffer, indices, 12*3*sizeof(size_t));

	buffer->buffer[0].pos = {-dimension, dimension, -dimension};
	buffer->buffer[1].pos = {dimension, dimension, -dimension};
	buffer->buffer[2].pos = {-dimension, -dimension, -dimension};
	buffer->buffer[3].pos = {dimension, -dimension, -dimension};
	buffer->buffer[4].pos = {-dimension, dimension, dimension};
	buffer->buffer[5].pos = {dimension, dimension, dimension};
	buffer->buffer[6].pos = {-dimension, -dimension, dimension};
	buffer->buffer[7].pos = {dimension, -dimension, dimension};

	mesh->setBuffer(buffer);

}

void Box::tick() {}

void Box::predraw() {}
void Box::postdraw() {}


void Box::onDie() {}
