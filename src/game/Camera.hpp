#pragma once
#include "math/Vector.hpp"
namespace nde {

class Camera {
	Vector3f position;
	Vector3f forward0, forward;
	Vector3f up0, up;
	Vector3f right;

	scalar phi, theta, rho;

	void updateVectors();
public:
	Camera();
	virtual ~Camera();

	void moveForwards(scalar distance);
	void strafeRight(scalar distance);
	void move(Vector3f direction);

	void rotate(scalar dphi, scalar dtheta);

	inline scalar getPhi() const { return phi; }
	inline scalar getTheta() const { return theta; }
	inline scalar getRho() const { return rho; }

	void setPosition(const Vector3f& position);

	Vector3f getRayTo(scalar x, scalar y);
	Vector3f getRayToFromCenter();

	inline const Vector3f& getPosition() const { return position; }
	inline const Vector3f& getForward() const { return forward; }
};

} // namespace nde


