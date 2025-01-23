#include "Shader.hpp"

std::string get_file_contents(const char* filename) {
	std::ifstream in(filename, std::ios::binary);
	if (!in) { throw (errno); }
	std::string contents;
	in.seekg(0, std::ios::end);
	contents.resize(in.tellg());
	in.seekg(0, std::ios::beg);
	in.read(&contents[0], contents.size());
	in.close();
	return contents;
}

Shader::Shader(const char* vertFile, const char* fragFile) {
	std::string vertCode = get_file_contents(vertFile);
	std::string fragCode = get_file_contents(fragFile);

	const char* vertexSource = vertCode.c_str();
	const char* fragmentSource = fragCode.c_str();

	// VERTEX SHADER
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	CompileErrors(vertexShader, "VERTEX");
	// FRAGMENT SHADER
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	CompileErrors(fragmentShader, "FRAGMENT");
	// SAHDER LINKING
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	CompileErrors(ID, "PROGRAM");
	// Delete shaders once used. No longer needed.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::CompileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}