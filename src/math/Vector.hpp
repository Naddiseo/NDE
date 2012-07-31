#pragma once
/*
 * Vector.hpp
 *
 *  Created on: 2012-07-29
 *     
 */
#include <cmath> // for std::sqrt

#ifdef USE_BULLET
#	include <LinearMath/btVector3.h>
#endif

#include "common.hpp"

#pragma pack(push, 1)
template<typename T>
struct Vector2 {
	T x, y;

	Vector2() : x(0), y(0) {}
	Vector2(T _x, T _y) : x(_x), y(_y) {}
	Vector2(const Vector2& other) : x(other.x), y(other.y) {}

	Vector2& operator=(const Vector2& other) {
		x = other.x;
		y = other.y;
		return *this;
	}

	Vector2 operator+(const Vector2& other) const {
		return {x + other.x, y + other.y};
	}

	Vector2 operator-(const Vector2& other) const {
		return {x - other.x, y - other.y};
	}

	Vector2 operator-() const {
		return {-x, -y};
	}

	Vector2 operator*(const Vector2& other) const {
		return {x * other.x, y * other.y};
	}


	Vector2 operator/(const Vector2& other) const {
		return {x / other.x, y / other.y};
	}

	Vector2 operator*(const T& other) const {
		return {x * other, y * other};
	}

	Vector2 operator/(const T& other) const {
		return {x / other, y / other};
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

	bool operator==(const Vector2& other) const {
		return (x == other.x) && (y == other.y);
	}

	bool operator!=(const Vector2& other) const {
		return !operator==(other);
	}

	bool operator<(const Vector2& other) const {
		return (x < other.x) || (y < other.y);
	}

	bool operator>(const Vector2& other) const {
		return !(operator<(other) || operator==(other));
	}

	bool operator>=(const Vector2& other) const {
		return !(operator<(other));
	}

	bool operator<=(const Vector2& other) const {
		return operator<(other) || operator==(other);
	}
};


template<typename T>
struct Vector3 {
	T x, y, z;

	Vector3() : x(0), y(0), z(0) {}

	Vector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}

	Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z) {}

#ifdef USE_BULLET
	Vector3(const btVector3& other) : x(other.getX()), y(other.getY()), z(other.getZ()) {}

	operator btVector3 () const {
		return btVector3(x, y, z);
	}
#endif

	Vector3& operator=(const Vector3& other) {
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	Vector3 operator+(const Vector3& other) const {
		return {x + other.x, y + other.y, z + other.z};
	}

	Vector3 operator-(const Vector3& other) const {
		return {x - other.x, y - other.y, z - other.z};
	}

	Vector3 operator-() const {
		return {-x, -y, -z};
	}

	Vector3 operator*(const Vector3& other) const {
		return {x * other.x, y * other.y, z * other.z};
	}

	Vector3 operator/(const Vector3& other) const {
		return {x / other.x, y / other.y, z / other.z};
	}

	Vector3 operator*(const T& other) const {
		return {x * other, y * other, z * other};
	}

	Vector3 operator/(const T& other) const {
		return {x / other, y / other, z / other};
	}

	scalar dot(const Vector3& other) const {
		return x * other.x + y * other.y + z * other.z;
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

	Vector3& operator/=(const Vector3 other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}

	Vector3& operator*=(T other) {
		x *= other;
		y *= other;
		z *= other;
		return *this;
	}

	Vector3& operator/=(T other) {
		x /= other;
		y /= other;
		z /= other;
		return *this;
	}

	bool operator==(const Vector3& other) const {
		return (x == other.x) && (y == other.y) && (z == other.z);
	}

	bool operator!=(const Vector3& other) const {
		return !operator==(other);
	}

	bool operator<(const Vector3 other) const {
		return (x < other.x) || (y < other.y) || (z < other.z);
	}

	bool operator>(const Vector3& other) const {
		return !(operator<(other) || operator==(other));
	}

	bool operator>=(const Vector3& other) const {
		return !(operator<(other));
	}

	bool operator<=(const Vector3& other) const {
		return operator<(other) || operator==(other);
	}

	T length() const {
		return std::sqrt(x*x + y*y + z*z);
	}

	T normalise() {
		T len = length();
		if (len > 1e-08) {
			T inverse_len = static_cast<T>(1) / static_cast<T>(len);
			*this *= inverse_len;
		}
		return len;
	}

	Vector3 cross(const Vector3& other) const {
		return {
			((y * other.z) - (z * other.y)),
			((z * other.x) - (x * other.z)),
			((x * other.y) - (y * other.x))
		};
	}
};

#pragma pack(pop)

typedef Vector2<scalar> Vector2f;
typedef Vector3<scalar> Vector3f;
