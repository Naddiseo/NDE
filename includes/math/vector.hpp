#pragma once
/*
 * vector.hpp
 *
 *  Created on: 2011-12-04
 *      Author: richard
 */
#include <string>
#include <cmath>

template<class T>
class Vector3 {
public:
	T x, y, z;
	std::string name;

	Vector3() : x(0), y(0), z(0), name("<anon>") {}

	Vector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z), name("<anon>") {}
	Vector3(T _x, T _y, T _z, std::string _name) : x(_x), y(_y), z(_z), name(_name) {}

	Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z), name(other.name) {}

	Vector3& operator=(const Vector3& other) {
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	Vector3 operator+(const Vector3& other) const {
		return {x + other.x, y + other.y, z + other.z, name};
	}

	Vector3 operator-(const Vector3& other) const {
		return {x - other.x, y - other.y, z - other.z, name};
	}

	Vector3 operator-() const {
		return {-x, -y, -z, name};
	}

	Vector3 operator*(const Vector3& other) const {
		return {x * other.x, y * other.y, z*other.z, name};
	}


	Vector3 operator/(const Vector3& other) const {
		return {x / other.x, y / other.y, z / other.z, name};
	}

	Vector3 operator*(const T& other) const {
		return {x * other, y * other, y * other, name};
	}

	Vector3 operator/(const T& other) const {
		return {x / other, y / other, y / other, name};
	}

	Vector3& operator+=(const Vector3 other) {
		x += other.x;
		y += other.y;
		z +=  other.z;
		return *this;
	}

	Vector3& operator-=(const Vector3 other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vector3& operator*=(const Vector3 other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}
/*
	Vector3 operator*(const RotationMatrix& rot) const {
		return {
			(rot[0][0] * x) + (rot[0][1] * y) + (rot[0][2] * z),
			(rot[1][0] * x) + (rot[1][1] * y) + (rot[1][2] * z),
			(rot[2][0] * x) + (rot[2][1] * y) + (rot[2][2] * z),
			name
		};
	}
*/
	Vector3& operator/=(const Vector3 other) {
		x /= other.x;
		y /= other.y;
		return *this;
	}

	Vector3& operator*=(const T other) {
		x *= other;
		y *= other;
		return *this;
	}

	Vector3& operator/=(const T other) {
		x /= other;
		y /= other;
		return *this;
	}

	bool operator==(const Vector3& other) {
		return (x == other.x) && (y == other.y);
	}

	bool operator!=(const Vector3& other) {
		return !operator==(other);
	}

	bool operator<(const Vector3 other) {
		return (x < other.x) || (y < other.y);
	}

	bool operator>(const Vector3& other) {
		return !(operator<(other) || operator==(other));
	}

	bool operator>=(const Vector3& other) {
		return !(operator<(other));
	}

	bool operator<=(const Vector3& other) {
		return operator<(other) || operator==(other);
	}

	T length() {
		return std::sqrt(x*x + y*y + z*z);
	}

	T normalise() {
		T len = length();
		if (len > 1e-08) {
			T inverse_len = 1 / length;
			this *= inverse_len;
		}
		return len;
	}
};

typedef Vector3<float> Vector3f;



