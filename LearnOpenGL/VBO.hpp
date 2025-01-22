#pragma once
#include <glad/glad.h>

class VBO {
public:
	GLuint ID;

	VBO(GLfloat* vertices, GLsizeiptr size);

	void Bind() { glBindBuffer(GL_ARRAY_BUFFER, ID); }
	void Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); };
	void Delete() { glDeleteBuffers(1, &ID); };
};