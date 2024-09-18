#include <SFML/Window.hpp>
#include <GL/glew.h>
#include <iostream>
#include "Shader.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"

static constexpr auto WIDTH = 800;
static constexpr auto HEIGHT = 800;
static const auto TITLE = "3D OpenGL";
constexpr auto vertexShaderCode = "#version 330 core\n"
"layout (location = 0) in vec3 pos;\n"
"uniform mat4 projection;\n"
"uniform mat4 view;\n"
"void main() { gl_Position = projection * view * vec4(pos, 1.0); }";
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

	Camera camera(glm::vec3(0.0f, 2.0f, 2.0f), -45.0f);

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // to see the triangle mesh

	while (window.isOpen()) {
		sf::Event event{};
		while (window.pollEvent(event)) {
			// The only event to process
			if (event.type == sf::Event::Closed) { window.close(); }
			else if (event.type == sf::Event::Resized) { 
				const auto windowSize = window.getSize();
				glViewport(0,0, windowSize.x, windowSize.y); 
			}
		}
		// 1. Clear screen
		glClear(GL_COLOR_BUFFER_BIT);

		// 2. Draw
		shader.Use();
		shader.SetValue("view", camera.GetViewMatrix());
		const auto windowSize = window.getSize();
		shader.SetValue("projection", camera.GetProjectionMatrix(windowSize.x, windowSize.y));
		shader.SetValue("color", glm::vec3(1.0f, 0.5f, 0.5f));
		mesh.Draw();

		// 3. Display
		window.display();
	}
}