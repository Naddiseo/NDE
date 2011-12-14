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
	scalar rot_x, rot_y, rot_z;
	scalar phi, theta;
	scalar speed, sensitivity;
public:
	Camera();
	virtual ~Camera();

	void render();

	void moveForwards(scalar distance);
	void strafeRight(scalar distance);
	void move(Vector3f dir);

	void onMouseMotion(const SDL_MouseMotionEvent& event);


	void rotateX(scalar angle);
	void rotateY(scalar angle);
	void rotateZ(scalar angle);

	void print();

	float getRotX() const { return rot_x; }
	float getRotY() const { return rot_y; }
	float getRotZ() const { return rot_z; }

	const Vector3f& getPos() const { return position; }

};

} /* namespace nde */
