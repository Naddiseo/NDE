#define __GXX_EXPERIMENTAL_CXX0X__  1
#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <map>
#include <cassert>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "matrix.hpp"

struct Bone;
struct Joint;

typedef std::vector<Joint*> joints_t;
typedef std::vector<Bone*> bones_t;
typedef std::map<int, Joint*> joint_map_t;
typedef std::map<int, Bone*> bone_map_t;

const int HEIGHT = 480;
const int WIDTH = 640;

joint_map_t all_joints;
bone_map_t all_bones;

bool has_shift(SDL_Event& event) {
	return (event.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT;
}

struct Color {
	unsigned char r, g, b;
	Color(unsigned char _r, unsigned char _g, unsigned char _b)
		: r(_r), g(_g), b(_b) {}

	void set() {
		glColor3ub(r, g, b);
	}
};

void drawv(Vector2f v) {
	glVertex2f(v.x, v.y);
}

Color yellow(200, 200, 0);
Color green(0, 255, 0);
Color red(255, 0, 0);
Color purple(0xee, 0x82, 0xee);
Color white(0xff, 0xff, 0xff);

struct Joint;

struct  Bone {
	static int _id;
	int id;
	Vector2f pos, far;
	Joint *joint_a, *joint_b;
	long len;

	Bone(Vector2f _p, long _len)
		: id(++_id), pos(_p), far({0,0}), joint_a(__null), joint_b(__null), len(_len) { all_bones[id] = this; }

	Bone(Vector2f _p, Joint* j1, Joint* j2, long _len)
		: id(++_id), pos(_p), far({0,0}), joint_a(j1), joint_b(j2), len(_len) {  all_bones[id] = this;  }

	Bone(const Bone& other)
		: id(++_id), pos(other.pos), far({0,0}), joint_a(other.joint_a), joint_b(other.joint_b), len(other.len) {  all_bones[id] = this;  }

	void set_joint_a(Joint* j) { joint_a = j; }
	void set_joint_b(Joint* j) { joint_b = j; }

	Bone& operator=(const Bone& other) {
		pos = other.pos;
		joint_a = other.joint_a;
		joint_b = other.joint_b;
		len = other.len;
		return *this;
	}

	void draw() {
		glPushMatrix();
		glScalef(20, 20, 20);
		glBegin(GL_LINE);
		red.set();
		//std::cout << "Drawing "<< id << " " << pos << ", " << far << std::endl;
		drawv({pos.x, pos.y});
		drawv({far.x, far.y});
		glEnd();
		glPopMatrix();
	}

	void calc_far(float angle) {
		Vector2f o({pos.x + len, pos.y});
		//RotatePoint.X = pOrigin.X + ( [Cos((Degrees)) * (pPoint.X - pOrigin.X)] - [Sin((Degrees)) * (pPoint.Y - pOrigin.Y)] )
		//RotatePoint.Y = pOrigin.Y + ( [Sin((Degrees)) * (pPoint.X - pOrigin.X)] + [Cos((Degrees)) * (pPoint.Y - pOrigin.Y)] )

		far = pos + ((o - pos) * RotationMatrix(angle));
	}
};

struct Joint {
	static int _id;
	int id;
	Bone &a, &b;
	float angle, min_angle, max_angle;


	Joint(Bone& _a, Bone& _b, float _angle, float _min, float _max)
		: id(++_id), a(_a), b(_b), angle(_angle), min_angle(_min), max_angle(_max) {  all_joints[id] = this; }

	Joint(Bone& _a, Bone& _b, float _angle)
		: id(++_id), a(_a), b(_b), angle(_angle), min_angle(0), max_angle(90) { all_joints[id] = this;}


	void set_angle(float new_angle) {
		angle = new_angle;
		angle = std::max(min_angle, angle);
		angle = std::min(max_angle, angle);
	}

	Joint& operator=(const Joint& j) {
		a = j.a;
		b = j.b;
		angle = j.angle;
		min_angle = j.min_angle;
		max_angle = j.max_angle;
		return *this;
	}

	Joint operator++(int) {
		set_angle(angle+1);
		update();
		return *this;
	}

	Joint operator--(int) {
		set_angle(angle-1);
		update();
		return *this;
	}

	void update() {
		// tell the rhs (bone 'b') to update itself
		//std::cout << "a: " << a.pos << ", " << a.far << std::endl;
		if (a.joint_a) {
			a.calc_far(a.joint_a->angle);
		}
		else {
			a.calc_far(0);
		}
		b.pos = a.far;
		b.calc_far(angle);
		//std::cout << "b: " << b.pos << ", " << b.far << std::endl;
	}

};

int Joint::_id = 0;
int Bone::_id = 0;

int main() {


	Bone base({3, 3}, 2);
	Bone arm1({3, 4}, 8);
	Bone arm2({5, 6}, 4);

	Joint joint1(base, arm1, 45, 10, 90);
	Joint joint2(arm1, arm2, -25, -90, 0);

	joints_t joints = {&joint1, &joint2};
	bones_t bones = {&base, &arm1, &arm2};


	base.set_joint_b(&joint1);
	arm1.set_joint_a(&joint1);
	arm1.set_joint_b(&joint2);
	arm2.set_joint_a(&joint2);

	//joints.push_back(&joint1);
	//joints.push_back(&joint2);

	//bones.push_back(&base);
	//bones.push_back(&arm1);
	//bones.push_back(&arm2);


	for (Joint* j : joints) {
		j->update();
	}

	std::cout << "all joints:\n";
	for (joint_map_t::value_type v : all_joints) {
		Joint* j = v.second;
		std::cout << j->id << "(" << j <<"): " << j->a.id << ", " << j->b.id << " " << j->angle << std::endl;
	}
	std::cout << "all bones:\n";
	for (bone_map_t::value_type v : all_bones) {
		Bone* b = v.second;
		std::cout << b->id << "(" << b <<"): " << b->pos << ", " << b->far << std::endl;
	}

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface* screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_OPENGL);

	SDL_Flip(screen);

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, 0, HEIGHT);

	SDL_EnableKeyRepeat(10,10);

	SDL_Event event;

	while (SDL_WaitEvent(&event)) {

		switch (event.type) {
		case SDL_QUIT:
			exit(0);
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
			case SDLK_q:
				exit(0);
				break;
			case SDLK_UP:
				//l--;
				break;
			case SDLK_DOWN:
				//l++;
				break;
			case SDLK_LEFT:
				if (has_shift(event)) {
					joint2++;
				}
				else {
					joint1++;
				}
				break;
			case SDLK_RIGHT:
				if (has_shift(event)) {
					joint2--;
				}
				else {
					joint1--;
				}
				break;
			}
		}
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();

		for (Joint* j : joints) {
			j->update();
		}

		for (Bone* b : bones) {
			b->draw();
		}

		glFlush();
		SDL_GL_SwapBuffers();

	}

	SDL_Quit();

	return 0;
}
