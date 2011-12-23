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
	
	Vector3f forward0, forward;
	Vector3f up0, up;
	
	scalar phi, theta, rho;
	
	scalar speed, sensitivity;
	
	void updateVectors();
	
public:
	Camera();
	virtual ~Camera();

	void render();

	void moveForwards(scalar distance);
	void strafeRight(scalar distance);
	void move(Vector3f dir);

	void onMouseMotion(const SDL_MouseMotionEvent& event);
	void onMouseClick(const SDL_MouseButtonEvent& event);

	void rotate(scalar dphi, scalar dtheta);
	
	void print();
	
	float getPhi() const { return phi; }
	float getTheta() const { return theta; }
	float getRho() const { return rho; }
	
	void setPosition(const Vector3f& position);
	
	Vector3f getRayTo(size_t x, size_t y);
	Vector3f getRayToFromCenter();
	
	const Vector3f& getPos() const { return position; }
};

} /* namespace nde */
