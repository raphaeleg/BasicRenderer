#pragma once
#include <glad/glad.h>

class EBO {
public:
	GLuint ID;

	EBO(GLuint* indices, GLsizeiptr size);

	void Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); }
	void Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); };
	void Delete() { glDeleteBuffers(1, &ID); };
};