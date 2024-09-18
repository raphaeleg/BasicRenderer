#include <SFML/Window.hpp>
#include <GL/glew.h>	// modern OpenGL aren't present by default
#include <glm/glm.hpp>
#include <iostream>

#include "Mesh.hpp"

static constexpr auto WIDTH = 800;
static constexpr auto HEIGHT = 800;
static const auto TITLE = "3D OpenGL";
constexpr auto vertexShaderCode = "#version 330 core\n"
"layout (location = 0) in vec3 pos;\n"
"void main() { gl_Position = vec4(pos, 1.0); }";
constexpr auto fragmentShaderCode = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main() { FragColor = vec4(0.0,1.0,0.0,1.0); }";

static void OutputError(size_t shader) {
	const auto infoBufferSize = 1024;
	char infoLog[infoBufferSize];

	glGetShaderInfoLog(shader, infoBufferSize, nullptr, infoLog);
	std::cerr << "Failed to compiler shader!\nInfoLog:\n" << infoLog;
}

static int CompileShader(const char* code, size_t shader) {
	glShaderSource(shader, 1, &code, nullptr);
	glCompileShader(shader);

	int success = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) { OutputError(shader); }
	return success;
}

static int LinkShaders(size_t shader, size_t vertexShader, size_t fragmentShader) {
	glAttachShader(shader, vertexShader);
	glAttachShader(shader, fragmentShader);
	glLinkProgram(shader);

	int success = 0;
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) { OutputError(shader); }
	return success;
}

static size_t CreateProgramShader() {
	auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
	auto success = CompileShader(vertexShaderCode, vertexShader);

	auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	success = CompileShader(fragmentShaderCode, fragmentShader);

	auto shader = glCreateProgram();
	success = LinkShaders(shader, vertexShader, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shader;
}

int main() {
	sf::Window window(sf::VideoMode(WIDTH, HEIGHT), TITLE);
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW\n";
		return -1;
	}
	
	const auto shader = CreateProgramShader();

	Mesh mesh({
		glm::vec3(0.8f, 0.8f, 0.0f),
		glm::vec3(0.8f, -0.8f, 0.0f),
		glm::vec3(-0.8f, -0.8f, 0.0f),
		glm::vec3(-0.8f, 0.8f, 0.0f),
	}, { 0, 1, 3, 1, 2, 3 });

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // to see the triangle mesh

	while (window.isOpen()) {
		sf::Event event{};
		while (window.pollEvent(event)) {
			// The only event to process
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		// 1. Clear screen
		glClear(GL_COLOR_BUFFER_BIT);

		// 2. Draw
		glUseProgram(shader);
		mesh.Draw();

		// 3. Display
		window.display();
	}
}