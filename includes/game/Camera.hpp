#pragma once
/*
 * Camera.hpp
 *
 *  Created on: 2011-12-10
 *      Author: richard
 */

#include <SDL/SDL.h>
#include "math/vector.hpp"

namespace nde {

class Camera {
	Vector3f position;
	Vector3f direction;
	Vector3f forward;
	Vector3f up;
	
	scalar speed, sensitivity;
public:
	Camera();
	virtual ~Camera();

	void render();

	void moveForwards(scalar distance);
	void strafeRight(scalar distance);
	void move(Vector3f dir);

	void onMouseMotion(const SDL_MouseMotionEvent& event);
	void onMouseClick(const SDL_MouseButtonEvent& event);

	void rotateX(scalar angle);
	void rotateY(scalar angle);
	void rotateZ(scalar angle);

	void print();

	float getRotX() const { return direction.x; }
	float getRotY() const { return direction.y; }
	float getRotZ() const { return direction.z; }

	Vector3f getRayTo(size_t x, size_t y);
	Vector3f getRayToFromCenter();
	
	void setPosition(const Vector3f& position);
	void setDirection(const Vector3f& direction);
	void setForwardDir(const Vector3f& forward);
	void setUpwardDir(const Vector3f& upward);
	
	const Vector3f& getPos() const { return position; }
};

} /* namespace nde */
