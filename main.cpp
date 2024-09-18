#include <SFML/Window.hpp>
#include <GL/glew.h>	// modern OpenGL aren't present by default
#include <glm/glm.hpp>
#include <iostream>

#include "Mesh.hpp"
#include "Shader.hpp"

static constexpr auto WIDTH = 800;
static constexpr auto HEIGHT = 800;
static const auto TITLE = "3D OpenGL";
constexpr auto vertexShaderCode = "#version 330 core\n"
"layout (location = 0) in vec3 pos;\n"
"void main() { gl_Position = vec4(pos, 1.0); }";
constexpr auto fragmentShaderCode = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec3 color;\n"
"void main() { FragColor = vec4(color,1.0); }";

int main() {
	sf::Window window(sf::VideoMode(WIDTH, HEIGHT), TITLE);
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW\n";
		return -1;
	}
	
	Shader shader(vertexShaderCode, fragmentShaderCode);

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
		shader.Use();
		shader.SetValue("color", glm::vec3(1.0f, 0.5f, 0.5f));
		mesh.Draw();

		// 3. Display
		window.display();
	}
}