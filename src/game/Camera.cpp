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
#define PIdiv180 3.1415265359/180.0

namespace nde {
Camera::Camera() : position(0,0,0), direction(0,0,-1) {
	rot_x = 0.f;
	rot_y = 0.f;
	rot_z = 0.f;
	phi = 0.f;
	theta = 0.f;
	speed = 0.01;
	sensitivity = 0.2;
	//SDL_WM_GrabInput(SDL_GrabMode::SDL_GRAB_ON);
	//SDL_ShowCursor(SDL_DISABLE);

}

Camera::~Camera() {
	//SDL_WM_GrabInput(SDL_GrabMode::SDL_GRAB_OFF);
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

	s1.x = std::cos((rot_y + 90) * PIdiv180);
	s1.z = -std::sin((rot_y + 90) * PIdiv180);
	scalar cosX = std::cos(rot_x * PIdiv180);

	s2.x = s1.x * cosX;
	s2.z = s1.z * cosX;
	s2.y = sin(rot_x * PIdiv180);

	direction = s2;

	glRotatef(-rot_x, 1, 0, 0);
	glRotatef(-rot_y, 0, 1, 0);
	glRotatef(-rot_z, 0, 0, 1);
	glTranslatef(-position.x, -position.y, -position.z);
}

void Camera::moveForwards(scalar distance) {
	Vector3f move(direction.x * -distance, direction.y * -distance, direction.z * -distance);

	position += move;
}

void Camera::strafeRight(scalar distance) {
	Vector3f move(direction.z*distance, 0, direction.x * -distance);

	position += move;
}

void Camera::move(Vector3f dir) {
	position += dir;
}

void Camera::onMouseMotion(const SDL_MouseMotionEvent& event) {
	scalar dx = event.x - x;
	scalar dy = event.y - y;
	
	dx = event.xrel;
	dy = event.yrel;
	
	rot_y -= event.xrel * sensitivity;
	rot_x -= event.yrel * sensitivity;

	Vector3f hor = getRayTo(0, 0) - getRayTo(1, 0);
	Vector3f ver = getRayTo(0, 0) - getRayTo(0, 1);
	target += hor * dx * 0.001;
	target += ver * dy * 0.001;

	x = event.x;
	y = event.y;
}


void Camera::onMouseClick(const SDL_MouseButtonEvent& event) {
	switch (event.button) {
	case SDL_BUTTON_RIGHT:
		Game::getInstance().getWorld().shootBox(position, getRayTo(event.x, event.y));
		break;
	default:break;
	}
}

void Camera::rotateX(scalar angle) {
	rot_x += angle;
}
void Camera::rotateY(scalar angle) {
	rot_y += angle;
}
void Camera::rotateZ(scalar angle) {
	rot_z += angle;
}

Vector3f Camera::getRayTo(size_t x, size_t y) {
	static int width = SGET_I("WIDTH");
	static int height = SGET_I("HEIGHT");
	scalar top = 1.f;
	scalar bottom = -1.f;
	scalar near = 1.f;
	scalar tanFov = (top - bottom)* 0.5f / near;
	scalar fov = 2.0f * std::atan(tanFov);

	Vector3f rayFrom = position;
	Vector3f rayForward  = target - position;
	rayForward.normalise();

	float farPlane = 10000.f;
	rayForward *= farPlane;

	Vector3f rightOffset;
	Vector3f vertical(0, 1, 0);

	Vector3f horizontal = rayForward.cross(vertical);
	horizontal.normalise();

	vertical = horizontal.cross(rayForward);
	vertical.normalise();

	float tanfov = std::tan(0.5f * fov);

	horizontal *= 2.f * farPlane * tanfov;
	vertical *= 2.f * farPlane * tanfov;

	scalar aspect = width / (scalar)height;

	horizontal *= aspect;

	Vector3f rayToCenter = rayFrom + rayForward;
	Vector3f dHorizontal = horizontal /(scalar)width;
	Vector3f dVertical   = vertical / (scalar)height;

	Vector3f rayTo = rayToCenter;
	rayTo += (-0.5f * horizontal);// + (0.5f *vertical);
	rayTo += dHorizontal * (scalar)x;
	rayTo += dVertical * (scalar)y;

	return rayTo;
}

} /* namespace nde */
