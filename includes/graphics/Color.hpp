#pragma once
/*
 * Color.h
 *
 *  Created on: 2011-11-28
 *      Author: richard
 */
#include <string>
#include <GL/gl.h>

struct Color {
	std::string name; // If no English name, use HTML hex code.
	float r, g, b, a;
	Color() : name("black"), r(.7), g(.7), b(.7), a(1) {}
	Color(std::string _name) : name(_name), r(0), g(0), b(0), a(1) {}
	Color(std::string _name, float _r, float _g, float _b)
		: name(_name), r(_r), g(_g), b(_b), a(1) {}
	
	Color(std::string _name, float _r, float _g, float _b, float _a)
		: name(_name), r(_r), g(_g), b(_b), a(_a) {}

	void set() {
		glColor4f(r, g, b, a);
	}

	void reset() { glColor4f(1,1,1,1); }
};



