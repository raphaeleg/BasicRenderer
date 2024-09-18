#include <SFML/Window.hpp>
#include <GL/glew.h>	// modern OpenGL aren't present by default
#include <iostream>

static constexpr auto WIDTH = 1200;
static constexpr auto HEIGHT = 900;
static const auto TITLE = "3D OpenGL";


int main() {
	const auto vertexShaderCode = "#version 330 core\n"
		"layout (location = 0) in vec3 pos;\n"
		"void main() { gl_Position = vec4(pos, 1.0); }";
	const auto fragmentShaderCode = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main() { FragColor = vec4(1.0,1.0,0.0,1.0); }";
	
	sf::Window window(sf::VideoMode(WIDTH, HEIGHT), TITLE);

	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW\n";
		return -1;
	}
	
	auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
	auto success = CompileShader(vertexShaderCode, vertexShader);

	auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	success = CompileShader(fragmentShaderCode, fragmentShader);

	auto shader = glCreateProgram();
	success = LinkShaders(shader, vertexShader, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

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

		// 3. Display
		window.display();
	}
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

static void OutputError(size_t shader) {
	const auto infoBufferSize = 1024;
	char infoLog[infoBufferSize];

	glGetShaderInfoLog(shader, infoBufferSize, nullptr, infoLog);
	std::cerr << "Failed to compiler shader!\nInfoLog:\n" << infoLog;
}