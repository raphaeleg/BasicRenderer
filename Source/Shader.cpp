#include "Shader.hpp"
#include "Helper.hpp"
#include <iostream>

Shader::Shader(const std::string vertexCode, const std::string fragmentCode) {
	const char* vertexShaderCode = vertexCode.c_str();
	const char* fragmentShaderCode = fragmentCode.c_str();

	auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
	auto success = CompileShader(vertexShaderCode, vertexShader);

	auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	success = CompileShader(fragmentShaderCode, fragmentShader);

	programID = glCreateProgram();
	success = LinkShaders(programID, vertexShader, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

int Shader::CompileShader(const char* code, size_t shader) {
	glShaderSource(shader, 1, &code, nullptr);
	glCompileShader(shader);

	int success = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) { OutputShaderError(shader); }
	return success;
}

 int Shader::LinkShaders(size_t shader, size_t vertexShader, size_t fragmentShader) {
	glAttachShader(shader, vertexShader);
	glAttachShader(shader, fragmentShader);
	glLinkProgram(shader);

	int success = 0;
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) { OutputShaderError(shader); }
	return success;
}