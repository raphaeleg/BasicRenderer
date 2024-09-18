#include <SFML/Window.hpp>
#include <GL/glew.h>
#include <iostream>
#include "Shader.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "Object.hpp"

static constexpr auto WIDTH = 800;
static constexpr auto HEIGHT = 800;
static const auto TITLE = "3D OpenGL";
static const float speed = 6.0f;
const float mouseSensitivity = 25.0f;

static void Render(Shader shader, Object object, Camera camera, sf::Vector2u windowSize) {
	shader.Use();
	shader.SetValue("view", camera.GetViewMatrix());
	shader.SetValue("projection", camera.GetProjectionMatrix(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)));
	object.Draw(shader, glm::vec3(1.0f, 0.5f, 0.5f));
}

int main() {
	constexpr auto vertexShaderCode = "#version 330 core\n"
		"layout (location = 0) in vec3 pos;\n"
		"uniform mat4 projection;\n"
		"uniform mat4 view;\n"
		"uniform mat4 model;\n"
		"void main() { gl_Position = projection * view * model * vec4(pos, 1.0); }";
	constexpr auto fragmentShaderCode = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec3 color;\n"
		"void main() { FragColor = vec4(color,1.0); }";

	sf::Window window(sf::VideoMode(WIDTH, HEIGHT), TITLE);
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW\n";
		return -1;
	}
	
	Shader shader(vertexShaderCode, fragmentShaderCode);

	Mesh mesh({
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(0.5f, 0.5f, -0.5f),
		glm::vec3(-0.5f, 0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, 0.5f),
		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(-0.5f, 0.5f, 0.5f),
	}, { 
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4,
		1, 5, 6, 6, 2, 1,
		0, 4, 7, 7, 3, 0,
		3, 2, 6, 6, 7, 3,
		0, 1, 5, 5, 4, 0
	});

	Camera camera(glm::vec3(0.0f, 0.0f, 2.0f));

	Object object(&mesh, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(), glm::vec3(2.0f, 5.0f, 2.0f));

	bool isMouseHold = false;
	sf::Vector2i lastMousePos{};

	sf::Clock clock{};

	while (window.isOpen()) {
		float deltaTime = clock.restart().asSeconds();

		sf::Event event{};
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { window.close(); }
			else if (event.type == sf::Event::Resized) { 
				const auto windowSize = window.getSize();
				glViewport(0,0, windowSize.x, windowSize.y); 
			}
		}

		camera.UpdateDirectionVectors();
		const float speedMod = speed * deltaTime;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { camera.position += camera.Forward() * speedMod; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { camera.position -= camera.Forward() * speedMod; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { camera.position -= camera.Right() * speedMod; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))  { camera.position += camera.Right() * speedMod; }

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			if (isMouseHold = false) {
				lastMousePos = sf::Mouse::getPosition(window);
				isMouseHold = true;
				window.setMouseCursorVisible(false);
			}
			else {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				int xOffset = mousePos.x - lastMousePos.x;
				int yOffset = lastMousePos.y - mousePos.y;
				camera.yaw += xOffset * mouseSensitivity * deltaTime;
				camera.pitch += yOffset * mouseSensitivity * deltaTime;
				sf::Mouse::setPosition(lastMousePos, window);
			}
		}
		else {
			isMouseHold = false;
			window.setMouseCursorVisible(true);
		}

		glClear(GL_COLOR_BUFFER_BIT);

		Render(shader, object, camera, window.getSize());

		window.display();
	}
}