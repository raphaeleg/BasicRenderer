#include "VAO.hpp"

VAO::VAO() {
	glGenVertexArrays(1, &ID);
	Bind();
}

void VAO::LinkVBO(VBO &VBO, GLuint layout) {
	VBO.Bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}
