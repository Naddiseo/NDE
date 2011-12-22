/*
 * Camera.cpp
 *
 *  Created on: 2011-12-10
 *      Author: richard
 */

#include <cmath>
#include <GL/gl.h>
#include <SDL/SDL.h>

#include "game/Camera.hpp"
#include "game/Settings.hpp"
#include "game/Game.hpp"

#define PI 3.1415265359
#define PIdiv180 (PI/180.0)

namespace nde {
Camera::Camera() : position(0,0,0), forward(0,0,-1) {
	
	speed = 0.01;
	sensitivity = 0.2;
	
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

void Camera::print() {
	std::cout
		<< position << " "
		<< forward << " "
		<< direction << std::endl;
}

void Camera::render() {

	Vector3f s1, s2;

	s1.x = std::cos((direction.y + 90) * PIdiv180);
	s1.z = -std::sin((direction.y + 90) * PIdiv180);
	scalar cosX = std::cos(direction.x * PIdiv180);

	s2.x = s1.x * cosX;
	s2.z = s1.z * cosX;
	s2.y = sin(direction.x * PIdiv180);

	forward = s2;

	glRotatef(-direction.x, 1, 0, 0);
	glRotatef(-direction.y, 0, 1, 0);
	glRotatef(-direction.z, 0, 0, 1);
	glTranslatef(-position.x, -position.y, -position.z);
}

void Camera::moveForwards(scalar distance) {
	Vector3f move(forward.x * -distance, forward.y * -distance, forward.z * -distance);

	position += move;
}

void Camera::strafeRight(scalar distance) {
	Vector3f move(forward.z*distance, 0, forward.x * -distance);

	position += move;
}

void Camera::move(Vector3f dir) {
	position += dir;
}

void Camera::onMouseMotion(const SDL_MouseMotionEvent& event) {
	direction -= Vector3f(event.yrel, event.xrel, 0) * sensitivity;
}

void Camera::onMouseClick(const SDL_MouseButtonEvent& event) {
	switch (event.button) {
	case SDL_BUTTON_RIGHT:
		Game::getInstance().getWorld().shootBox(position, getRayToFromCenter());
		break;
	default:
		break;
	}
}

void Camera::setPosition(const Vector3f& position) {
	this->position = position;
}


void Camera::setDirection(const Vector3f& direction) {
	this->direction = direction;
}

void Camera::setUpwardDir(const Vector3f& upward) {
	this->up = upward;
}

void Camera::setForwardDir(const Vector3f& forward) {
	this->forward = forward;
}

void Camera::rotateX(scalar angle) {
	direction.x += angle;
}
void Camera::rotateY(scalar angle) {
	direction.y += angle;
}
void Camera::rotateZ(scalar angle) {
	direction.z += angle;
}

Vector3f Camera::getRayToFromCenter() {
	static size_t width = SGET_I("WIDTH");
	static size_t height = SGET_I("HEIGHT");
	return getRayTo(width/2, height/2);
}

Vector3f Camera::getRayTo(size_t x, size_t y) {
	GLfloat winX, winY, winZ;
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
}

} /* namespace nde */
