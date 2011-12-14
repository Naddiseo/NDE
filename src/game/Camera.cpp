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

#define PI 3.1415265359
#define PIdiv180 3.1415265359/180.0

namespace nde {
Camera::Camera()
	:position(0,0,0), direction(0,0,-1),
	 rot_x(0), rot_y(0), rot_z(0),
	 phi(0), theta(0),
	 speed(0.01), sensitivity(0.2) {
	SDL_WM_GrabInput(SDL_GRAB_ON);
	//SDL_ShowCursor(SDL_DISABLE);

}

Camera::~Camera() {
	SDL_WM_GrabInput(SDL_GRAB_OFF);
	//SDL_ShowCursor(SDL_ENABLE);
}

void Camera::print() {
	std::cout
		<< position << " "
		<< direction << " "
		<< "(" << rot_x << "," << rot_y << "," << rot_z << ")" << std::endl;
}

void Camera::render() {

	Vector3f s1, s2;

	s1.x = cos((rot_y + 90) * PIdiv180);
	s1.z = -sin((rot_y + 90) * PIdiv180);
	double cosX = cos(rot_x * PIdiv180);

	s2.x = s1.x * cosX;
	s2.z = s1.z * cosX;
	s2.y = sin(rot_x * PIdiv180);

	direction = s2;

	glRotatef(-rot_x, 1, 0, 0);
	glRotatef(-rot_y, 0, 1, 0);
	glRotatef(-rot_z, 0, 0, 1);
	glTranslatef(-position.x, -position.y, -position.z);
}

void Camera::moveForwards(float distance) {
	Vector3f move(direction.x * -distance, direction.y * -distance, direction.z * -distance);

	position += move;
}

void Camera::strafeRight(float distance) {
	Vector3f move(direction.z*distance, 0, direction.x * -distance);

	position += move;
}

void Camera::move(Vector3f dir) {
	position += dir;
}

void Camera::onMouseMotion(const SDL_MouseMotionEvent& event) {
	rot_y -= event.xrel * sensitivity;
	rot_x -= event.yrel * sensitivity;
}

void Camera::rotateX(float angle) {
	rot_x += angle;
}
void Camera::rotateY(float angle) {
	rot_y += angle;
}
void Camera::rotateZ(float angle) {
	rot_z += angle;
}

} /* namespace nde */
