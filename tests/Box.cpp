/*
 * Box.cpp
 *
 *  Created on: 2011-12-25
 *      Author: richard
 */
#include <btBulletDynamicsCommon.h>

#include "Box.hpp"

Box::Box(scalar _mass, scalar dimension) : mass(_mass) {
	btBoxShape* shape = new btBoxShape({dimension, dimension, dimension});


	shape->initializePolyhedralFeatures();

	location.setIdentity();
	location.setRotation({0, 0, 0, 1});

	// Creates body using mass
	addCollisionShape(shape);
}

Box::~Box() {}

void Box::init(Vector3f from, Vector3f dir, scalar speed) {
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



}

void Box::tick() {}

void Box::predraw() {}
void Box::postdraw() {}


void Box::onDie() {}
