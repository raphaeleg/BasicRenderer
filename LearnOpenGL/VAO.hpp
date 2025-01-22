#pragma once
#include <glad/glad.h>
#include "VBO.hpp"

class VAO {
public:
	GLuint ID;
	VAO();

	void LinkVBO(VBO &VBO, GLuint layout);
	void Bind() { glBindVertexArray(ID); }
	void Unbind() { glBindVertexArray(0); };
	void Delete() { glDeleteVertexArrays(1, &ID); };
};