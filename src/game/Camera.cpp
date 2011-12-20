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

#define PI 3.1415265359
#define PIdiv180 (PI/180.0)

namespace nde {
Camera::Camera() : position(0,0,0), forward(0,0,1), up(0,1,0) {
	rot_x = 0.f;
	rot_y = 0.f;
	
	speed = 0.01;
	sensitivity = 0.2;
	
	#ifdef WINDOWS
		SDL_ShowCursor(SDL_DISABLE);
	#endif
	
	SDL_WM_GrabInput(SDL_GrabMode::SDL_GRAB_ON);
}

Camera::~Camera() {
	#ifdef WINDOWS
		SDL_ShowCursor(SDL_ENABLE);
	#endif
	
	SDL_WM_GrabInput(SDL_GrabMode::SDL_GRAB_OFF);
}

void Camera::print() {
	std::cout
		<< position << " "
		<< forward << " "
		<< "(" << rot_x << "," << rot_y << ")" << std::endl;
}

void Camera::render() {
	glRotatef(-rot_x, 1, 0, 0);
	glRotatef(-rot_y, 0, 1, 0);
	
	glTranslatef(-position.x, -position.y, -position.z);
}

void Camera::moveForwards(scalar distance) {
	position -= distance * forward;
}

void Camera::strafeRight(scalar distance) {
	position += distance * forward.cross(up);
}

void Camera::move(Vector3f dir) {
	position += dir;
}

void Camera::onMouseMotion(const SDL_MouseMotionEvent& event) {
	scalar phi = event.xrel * sensitivity;
	scalar theta = event.yrel * sensitivity;
	this->rotate(phi, theta);
}

void Camera::onMouseClick(const SDL_MouseButtonEvent& event) {
	switch (event.button) {
	case SDL_BUTTON_RIGHT:
		Game::getInstance().getWorld().shootBox(position, getRayTo(event.x, event.y));
		break;
	default:
		break;
	}
}

void Camera::setPosition(const Vector3f& position) {
	this->position = position;
}

void Camera::setUpwardDir(const Vector3f& upward) {
	this->up = upward;
}

void Camera::setForwardDir(const Vector3f& forward) {
	this->forward = forward;
}

void Camera::rotate(scalar phi, scalar theta) {
	Vector3f cross = forward.cross(up);
	
	// TODO: Rotate FORWARD around UP by phi
	
	
	// TODO: Rotate UP, FORWARD around CROSS by theta
}

Vector3f Camera::getRayTo(size_t x, size_t y) {
	return forward;
	
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
