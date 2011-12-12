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
	unsigned char r, g, b, a;
	Color() : r(0), g(0), b(0), a(255) {}
	Color(unsigned char _r, unsigned char _g, unsigned char _b)
		: r(_r), g(_g), b(_b), a(255) {}
	
	Color(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
		: r(_r), g(_g), b(_b), a(_a) {}

	void set() {
		glColor3ub(r, g, b);
	}
};

void add_color(std::string, unsigned char r, unsigned char g, unsigned char b);
Color& get_color(std::string);


