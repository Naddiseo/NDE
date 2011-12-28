/*
 * Camera.cpp
 *
 *  Created on: 2011-12-10
 *      Author: richard
 */

#include <cmath>
#include <iostream>
#include <GL/gl.h>
#include <SDL/SDL.h>

#include "game/Camera.hpp"
#include "game/Settings.hpp"
#include "game/Game.hpp"
#include "math/util.hpp"

namespace nde {

Camera::Camera()
	: position(0,0,0),
		forward0(0,0,-1), forward(forward0),
		up0(0,1,0), up(up0),
		right(up.cross(forward))
{
	phi = 0.f;
	theta = 0.f;
	rho = 0.f;
	
	speed = 0.01;
	sensitivity = 0.004;
	
	#ifdef WINDOWS
		SDL_ShowCursor(SDL_DISABLE);
	#endif
	
	//SDL_WM_GrabInput(SDL_GrabMode::SDL_GRAB_ON);
}

Camera::~Camera() {
	#ifdef WINDOWS
		SDL_ShowCursor(SDL_ENABLE);
	#endif
	
	//SDL_WM_GrabInput(SDL_GrabMode::SDL_GRAB_OFF);
}

bool Camera::init() { return true; }

void Camera::updateVectors() {
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

void Camera::print() {
	std::cout
		<< position << " "
		<< forward << " " << up << " " << right
		<< std::endl;
}

void Camera::render() {
	// TODO: Figure out why this doesn't look like (phi, theta, rho)
	
	glRotatef(RAD2DEG(theta), 1, 0, 0);
	glRotatef(RAD2DEG(-phi ), 0, 1, 0);
	glRotatef(RAD2DEG(rho  ), 0, 0, 1);
	
	glTranslatef(-position.x, -position.y, -position.z);
}

void Camera::moveForwards(scalar distance) {
	position += distance * forward;
}

void Camera::strafeRight(scalar distance) {
	position += distance * right;
}

void Camera::move(Vector3f dir) {
	position += dir;
}

void Camera::onMouseMotion(const SDL_MouseMotionEvent& event) {
	scalar dphi = event.xrel * sensitivity;
	
	// Negative because downward mouse mosition is
	// positive, upward negative
	scalar dtheta = -event.yrel * sensitivity;
	
	this->rotate(dphi, dtheta);
}

void Camera::onMouseClick(const SDL_MouseButtonEvent& event) {
	switch (event.button) {
	case SDL_BUTTON_RIGHT:
		Game::getInstance().getWorld().shootBox(position, forward);
		break;
	default:
		break;
	}
}

void Camera::setPosition(const Vector3f& position) {
	this->position = position;
}

void Camera::rotate(scalar dphi, scalar dtheta) {
	phi   -= dphi;
	theta -= dtheta;
	
	this->updateVectors();
}

Vector3f Camera::getRayToFromCenter() {
	static size_t width = SGET_I("WIDTH");
	static size_t height = SGET_I("HEIGHT");
	return getRayTo(width/2, height/2);
}

Vector3f Camera::getRayTo(size_t x, size_t y) {
/*	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];

	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

	return Vector3f(posX, posY, posZ);
*/
}

} /* namespace nde */
