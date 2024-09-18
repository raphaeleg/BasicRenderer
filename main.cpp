#include <SFML/Window.hpp>
#include <GL/glew.h>	// modern OpenGL aren't present by default
#include <iostream>

static constexpr auto WIDTH = 1200;
static constexpr auto HEIGHT = 900;
static const auto TITLE = "3D OpenGL";


int main() {
	const char* vertexShaderCode = "#version 330 core\n"
		"layout (location = 0) in vec3 pos;\n"
		"void main() { gl_Position = vec4(pos, 1.0); }";
	const char* fragmentShaderCode = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main() { FragColor = vec4(1.0,1.0,0.0,1.0); }";
		;
	
	sf::Window window(sf::VideoMode(WIDTH, HEIGHT), TITLE);

	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW\n";
		return -1;
	}
	
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
