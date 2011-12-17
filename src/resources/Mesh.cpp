#include "resources/Mesh.hpp"
#include <GL/gl.h>

namespace nde {

Mesh::~Mesh() {
	for (Vector3f* v : vertices) {
		delete v;
	}

	for (Face* f : faces) {
		delete f;
	}
}

void Mesh::render(Vector3f& translate) {
	glPushMatrix();
		glTranslatef(translate.x, translate.y, translate.z);
		glTranslatef(origin.x, origin.y, origin.z);
		
		for (Face* face : faces) {
			face->draw();
		}


	glPopMatrix();
}

Vector3f*
Mesh::add(scalar x, scalar y, scalar z) {
	Vector3f* ret = new Vector3f(x, y, z);

	vertices.push_back(ret);
	return ret;
}

}
