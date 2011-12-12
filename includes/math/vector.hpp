#pragma once
#include <iostream>
#include <string>

#include <cmath>
/*
 * matrix.hpp
 *
 *  Created on: 2011-11-25
 *      Author: richard
 */
const float PI = 3.14159265;
static float radian(float deg) {
	return deg * PI/180;
}

struct RotationMatrix {
	// [row][col]
	float data[3][3];

	RotationMatrix(float theta, float phi = 0, float psi = 0) : data({{0,0,0}, {0,0,0}, {0,0,0}}) {
		rotate(theta, phi, psi);
	}

	void rotate(float theta, float phi = 0, float psi = 0) {
		theta = radian(theta);
		phi = radian(phi);
		psi = radian(psi);

		float cos_theta = std::cos(theta);
		float sin_theta = std::sin(theta);
		float cos_phi = std::cos(phi);
		float sin_phi = std::sin(phi);
		float cos_psi = std::cos(psi);
		float sin_psi = std::sin(psi);

		float cos_phi_sin_theta = cos_phi * sin_theta;
		float sin_phi_sin_theta = sin_phi * sin_theta;

		data[0][0] = cos_theta * cos_psi;
		data[0][1] = (cos_phi * sin_psi) + (sin_phi_sin_theta * cos_psi);
		data[0][2] = (sin_theta * sin_psi) - (cos_phi_sin_theta * cos_psi);
		data[1][0] = -cos_theta * sin_psi;
		data[1][1] = (cos_phi * cos_psi) - (sin_phi_sin_theta * sin_psi);
		data[1][2] = (sin_phi * cos_psi) + (cos_phi_sin_theta * sin_psi);
		data[2][0] = sin_theta;
		data[2][1] = -sin_phi * cos_theta;
		data[2][2] = cos_phi * cos_theta;
	}

	float* operator[](int row) {
		return data[row];
	}

};

template<class T>
class Vector2 {
public:
	T x, y;
	std::string name;

	Vector2() : x(0), y(0), name("<anon>") {}

	Vector2(T _x, T _y) : x(_x), y(_y), name("<anon>") {}
	Vector2(T _x, T _y, std::string _name) : x(_x), y(_y), name(_name) {}

	Vector2(const Vector2& other) : x(other.x), y(other.y), name(other.name) {}

	Vector2& operator=(const Vector2& other) {
		x = other.x;
		y = other.y;
		return *this;
	}

	Vector2 operator+(const Vector2& other) const {
		return {x + other.x, y + other.y, name};
	}

	Vector2 operator-(const Vector2& other) const {
		return {x - other.x, y - other.y, name};
	}

	Vector2 operator-() const {
		return {-x, -y, name};
	}

	Vector2 operator*(const Vector2& other) const {
		return {x * other.x, y * other.y, name};
	}


	Vector2 operator/(const Vector2& other) const {
		return {x / other.x, y / other.y, name};
	}

	Vector2 operator*(const T& other) const {
		return {x * other, y * other, name};
	}

	Vector2 operator/(const T& other) const {
		return {x / other, y / other, name};
	}

	Vector2& operator+=(const Vector2 other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2& operator-=(const Vector2 other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vector2& operator*=(const Vector2 other) {
		x *= other.x;
		y *= other.y;
		return *this;
	}

	Vector2 operator*(const RotationMatrix& rot) const {
		return {
			(rot[0][0] * x) + (rot[0][1] * y),
			(rot[1][0] * x) + (rot[1][1] * y),
			name
		};
	}

	Vector2& operator/=(const Vector2 other) {
		x /= other.x;
		y /= other.y;
		return *this;
	}

	Vector2& operator*=(const T other) {
		x *= other;
		y *= other;
		return *this;
	}

	Vector2& operator/=(const T other) {
		x /= other;
		y /= other;
		return *this;
	}

	bool operator==(const Vector2& other) {
		return (x == other.x) && (y == other.y);
	}

	bool operator!=(const Vector2& other) {
		return !operator==(other);
	}

	bool operator<(const Vector2& other) {
		return (x < other.x) || (y < other.y);
	}

	bool operator>(const Vector2& other) {
		return !(operator<(other) || operator==(other));
	}

	bool operator>=(const Vector2& other) {
		return !(operator<(other));
	}

	bool operator<=(const Vector2& other) {
		return operator<(other) || operator==(other);
	}
};

typedef Vector2<float> Vector2f;

template<class T>
std::ostream& operator<<(std::ostream& os, const Vector2<T>& v) {
	os << v.name << "(" << v.x << ", " << v.y << ")";
	return os;
}



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
		return {x * other.x, y * other.y, z * other.z, name};
	}


	Vector3 operator/(const Vector3& other) const {
		return {x / other.x, y / other.y, z / other.z, name};
	}

	Vector3 operator*(const T& other) const {
		return {x * other, y * other, z * other, name};
	}

	Vector3 operator/(const T& other) const {
		return {x / other, y / other, z / other, name};
	}

	Vector3& operator+=(const Vector3 other) {
		x += other.x;
		y += other.y;
		z += other.z;
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

	Vector3 operator*(const RotationMatrix& rot) const {
		return {
			(rot[0][0] * x) + (rot[0][1] * y) + (rot[0][2] * z),
			(rot[1][0] * x) + (rot[1][1] * y) + (rot[1][2] * z),
			(rot[2][0] * x) + (rot[2][1] * y) + (rot[2][2] * z),
			name
		};
	}

	Vector3& operator/=(const Vector3 other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}

	Vector3& operator*=(const T other) {
		x *= other;
		y *= other;
		z *= other;
		return *this;
	}

	Vector3& operator/=(const T other) {
		x /= other;
		y /= other;
		z /= other;
		return *this;
	}

	bool operator==(const Vector3& other) {
		return (x == other.x) && (y == other.y) && (z == other.z);
	}

	bool operator!=(const Vector3& other) {
		return !operator==(other);
	}

	bool operator<(const Vector3 other) {
		return (x < other.x) || (y < other.y) || (z < other.z);
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

template<class T>
std::ostream& operator<<(std::ostream& os, const Vector3<T>& v) {
	os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
	return os;
}



