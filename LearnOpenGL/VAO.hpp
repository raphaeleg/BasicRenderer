#pragma once
#include <glad/glad.h>
#include "VBO.hpp"

class VAO {
public:
	GLuint ID;
	VAO();

	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void Bind() { glBindVertexArray(ID); }
	void Unbind() { glBindVertexArray(0); };
	void Delete() { glDeleteVertexArrays(1, &ID); };
};