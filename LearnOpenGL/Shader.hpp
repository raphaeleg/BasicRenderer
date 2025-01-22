#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader {
public:
	GLuint ID = 0;
	Shader(const char* vertFile, const char* fragFile);
	void Activate() { glUseProgram(ID); };
	void Delete() { glDeleteProgram(ID); };
};