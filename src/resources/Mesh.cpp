#include <GL/glew.h>
#include <GL/glext.h>
#include "resources/Mesh.hpp"


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

void Mesh::flush() {
	//glVertexPointer(3, GL_FLOAT, sizeof(float)*3, vertex_array);
	//glColorPointer(3, GL_UNSIGNED_BYTE, sizeof(char)*3, color_array);
	glDrawArrays(GL_TRIANGLES, 0, array_count);
}

GLuint Mesh::reserve(size_t elements) {
	array_count = elements;
	//vertex_array = new scalar[elements * 3];
	glGenBuffersARB(1, &vboId);
	glBindBufferARB(GL_ARRAY_BUFFER, vboId);

	return vboId;
}


/*char* Mesh::reserveColors(size_t elements) {
	color_count = elements;
	return NULL;
}*/

Vector3f*
Mesh::add(scalar x, scalar y, scalar z) {
	Vector3f* ret = new Vector3f(x, y, z);

	vertices.push_back(ret);
	return ret;
}

}
