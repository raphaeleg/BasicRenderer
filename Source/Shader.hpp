#pragma once
#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	Shader() {};
	Shader(const std::string vertexCode, const std::string fragmentCode);

	void Use() { glUseProgram(programID); }

	void SetValue(const std::string name, float value) {
		glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
	};
	void SetValue(const std::string name, glm::mat4 value) {
		glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	};
	void SetValue(const std::string name, glm::vec3 value) {
		glUniform3f(glGetUniformLocation(programID, name.c_str()), value.x, value.y, value.z);
	};
private:
	uint32_t programID = 0;
	int CompileShader(const char* code, size_t shader);
	int LinkShaders(size_t shader, size_t vertexShader, size_t fragmentShader);
};