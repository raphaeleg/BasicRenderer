#pragma once

#include<glad/glad.h>
#include<stb/stb_image.h>
#include<string>

#include "Shader.hpp"

class Texture
{
public:
	GLuint ID;
	GLenum type;
	GLenum slot;
	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind() const { glActiveTexture(slot); glBindTexture(type, ID); }
	void Unbind() const { glBindTexture(type, 0); }
	void Delete() const { glDeleteTextures(1, &ID); }
};