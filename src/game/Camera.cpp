#include "game/Camera.hpp"
#include "math/Utils.hpp"
#include "game/Settings.hpp"

namespace nde {

Camera::Camera()
	: position(0, 0, 0), forward0(0,0, -1),
	  forward(forward0), up0(0,1,0), up(up0),
	  right(up.cross(forward)),
	  phi(0), theta(0), rho(0) {}

Camera::~Camera() {}

void
Camera::updateVectors() {
	forward = forward0;
	up = up0;

	RotateAround(phi, up, forward);

	right = up.cross(forward);
	right.normalise();

	RotateAround(theta, right, up);
	RotateAround(theta, right, forward);

	up.normalise();
	forward.normalise();
}

void
Camera::moveForwards(scalar distance) {
	position += distance * forward;
}

void
Camera::strafeRight(scalar distance) {
	position += distance * right;
}

void
Camera::move(Vector3f dir) {
	position += dir;
}

void
Camera::setPosition(const Vector3f& position) {
	this->position = position;
}

void
Camera::rotate(scalar dphi, scalar dtheta) {
	phi   -= dphi;
	theta -= dtheta;

	this->updateVectors();
}

Vector3f
Camera::getRayTo(scalar x, scalar y) {

	return {0,0,0};
}

Vector3f
Camera::getRayToFromCenter() {
	static scalar width = SGET_F("WIDTH");
	static scalar height = SGET_F("HEIGHT");
	return getRayTo(width/2, height/2);
}

} // namespace nde

