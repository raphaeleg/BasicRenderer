#pragma once
#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>	// modern OpenGL aren't present by default

class Shader {
public:
	Shader(const std::string vertexCode, const std::string fragmentCode);
	void Use() { glUseProgram(programID); };
	void SetValue(const std::string name, glm::vec3 value) {
		glUniform3f(glGetUniformLocation(programID, name.c_str()), value.x, value.y, value.z);
	};
private:
	uint32_t programID;

	void OutputError(size_t shader);
	int CompileShader(const char* code, size_t shader);
	int LinkShaders(size_t shader, size_t vertexShader, size_t fragmentShader);
};

