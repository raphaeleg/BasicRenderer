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
	void Activate() const { glUseProgram(ID); }

	void setBool(const std::string& name, bool value) const { glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); }
	void setInt(const std::string& name, int value) const { glUniform1i(glGetUniformLocation(ID, name.c_str()), value); }
	void setFloat(const std::string& name, float value) const { glUniform1f(glGetUniformLocation(ID, name.c_str()), value); }

	void CompileErrors(unsigned int shader, const char* type);
	void Delete() const { glDeleteProgram(ID); }
};