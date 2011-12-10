/*
 * test01.cpp
 *
 *  Created on: 2011-12-01
 *      Author: richard
 */
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <assimp/assimp.h>

#include "NDE.hpp"

const int HEIGHT = 480;
const int WIDTH = 640;

bool has_shift(SDL_Event& event) {
	return (event.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT;
}

void renderNode(const aiScene* scene, const aiNode* nd) {
	aiMatrix4x4 m = nd->mTransformation;

	aiTransposeMatrix4(&m);
	glPushMatrix();
	glMultMatrixf((float*)&m);

	assert(nd->mMeshes != NULL);

	for (size_t n = 0;  n < nd->mNumMeshes; ++n) {
		const aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];

		if (mesh->mNormals == NULL) {
			glDisable(GL_LIGHTING);
		}
		else {
			glEnable(GL_LIGHTING);
		}

		for (size_t t = 0; t < mesh->mNumFaces; ++t) {
			const aiFace* face = &mesh->mFaces[t];
			GLenum face_mode;

			switch (face->mNumIndices) {
			case 1: face_mode = GL_POINTS; break;
			case 2: face_mode = GL_LINES; break;
			case 3: face_mode = GL_TRIANGLES; break;
			case 4: face_mode = GL_QUADS; break;
			default: face_mode = GL_POLYGON; break;
			}

			glBegin(face_mode);
			for (size_t i = 0; i < face->mNumIndices; i++) {
				size_t index = face->mIndices[i];

				if (mesh->mColors[0] != NULL) {
					glColor4fv((GLfloat*)&mesh->mColors[0][index]);
				}
				if (mesh->mNormals != NULL) {
					glNormal3fv((GLfloat*)&mesh->mNormals[index].x);
				}
				glVertex3fv(&mesh->mVertices[index].x);
			}
			glEnd();
		}
	}
}

int main() {
	std::string path = "/home/richard/Projects/NDE/assets/model.blend";
	if (!nde::Game::getInstance().loadScene(path)) {
		std::cerr << "Couldn't load model" << std::endl;
	}

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface* screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_OPENGL);
	SDL_Flip(screen);
	glEnable(GL_DEPTH_TEST | GL_LIGHTING |GL_LIGHT0 | GL_NORMALIZE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(70, WIDTH/HEIGHT, 1, 1000);
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	SDL_EnableKeyRepeat(10,10);

	SDL_Event event;
	nde::Scene& scene = nde::Game::getInstance().getWorld().getScene();

	for (;;) {
		while (SDL_PollEvent(&event)) {
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
				}
			}
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// do stuff
		float tmp = scene.getMax().x - scene.getMin().x;
		tmp = std::max((scene.getMax().y - scene.getMin().y), tmp);
		tmp = std::max((scene.getMax().z - scene.getMin().z), tmp);
		tmp = 1.0f / tmp;
		glScalef(tmp, tmp, tmp);
		glTranslatef(-scene.getCenter().x, -scene.getCenter().y, -scene.getCenter().z);

		renderNode(scene.getScene(), scene.getScene()->mRootNode);

		glFlush();
		SDL_GL_SwapBuffers();
	}


	SDL_Quit();
	return 0;
}
