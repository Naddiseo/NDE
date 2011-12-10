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
float radian(float deg) {
	return deg * PI/180;
}

struct RotationMatrix {
	float a, b, c, d;

	RotationMatrix(float theta) : a(0), b(0), c(0), d(0) {
		rotate(theta);
	}

	void rotate(float theta) {
		float radians = radian(theta);
		float _cos = std::cos(radians);
		float _sin = std::sin(radians);
		a = _cos;
		b = -_sin;
		c = _sin;
		d = _cos;
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
			(rot.a * x) + (rot.b * y),
			(rot.c * x) + (rot.d * y),
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





