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
	float rot_x, rot_y, rot_z;
	float phi, theta;
	float speed, sensitivity;
public:
	Camera();
	virtual ~Camera();

	void render();

	void moveForwards(float distance);
	void strafeRight(float distance);
	void move(Vector3f dir);

	void onMouseMotion(const SDL_MouseMotionEvent& event);


	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);

	void print();

	float getRotX() const { return rot_x; }
	float getRotY() const { return rot_y; }
	float getRotZ() const { return rot_z; }

};

} /* namespace nde */
