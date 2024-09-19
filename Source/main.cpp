#include <SFML/Window.hpp>
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Shader.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "Scene.hpp"

static constexpr auto WIDTH = 800;
static constexpr auto HEIGHT = 800;
static const auto WINDOW_TITLE = "3D OpenGL";
const auto VERTEX_FILENAME = "Source/vertex.glsl";
const auto FRAGMENT_FILENAME = "Source/frag.glsl";
constexpr glm::vec3 CAM_POSITION = glm::vec3(-14.6f, 17.0f, 7.3f);
constexpr float CAM_PITCH = -400.5f;
constexpr float CAM_YAW = -26.7f;
constexpr float CAM_SPEED = 6.0f;
constexpr float MOUSE_SENSITIVITY = 25.0f;

static std::string ReadTextFile(const std::string fileName) {
	std::ifstream file(fileName);
	if (!file.is_open()) { 
		std::cerr << "ERROR: Failed to open "+fileName+"\n";
		return "";
	}
	std::stringstream ss{};
	ss << file.rdbuf();
	file.close();
	return ss.str();
}

static void Render(Shader shader, Scene scene, Camera camera, sf::Vector2u windowSize) {
	shader.Use();
	shader.SetValue("view", camera.GetViewMatrix());
	shader.SetValue("projection", camera.GetProjectionMatrix(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)));
	shader.SetValue("lightPos", camera.position);
	shader.SetValue("viewPos", camera.position);

	scene.Draw(shader);
}

int main(int argc, char** argv) {
	sf::ContextSettings settings;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	settings.depthBits = 24;

	sf::Window window(sf::VideoMode(WIDTH, HEIGHT), WINDOW_TITLE, sf::Style::Default, settings);
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW\n";
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	
	Shader shader(ReadTextFile(VERTEX_FILENAME), ReadTextFile(FRAGMENT_FILENAME));

	auto scene_fileName = "Models/source/Robin_Bird_M.fbx";
	if (argc > 1) {
		scene_fileName = argv[1];
	}
	Scene scene(scene_fileName);

	Camera camera(CAM_POSITION, CAM_PITCH, CAM_YAW);

	shader.Use();
	shader.SetValue("ambientStrength", 0.1f);
	shader.SetValue("lightColor", glm::vec3(1.0f));

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
		const float speedMod = CAM_SPEED * deltaTime;
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
				camera.yaw += xOffset * MOUSE_SENSITIVITY * deltaTime;
				camera.pitch += yOffset * MOUSE_SENSITIVITY * deltaTime;
				sf::Mouse::setPosition(lastMousePos, window);
			}
		}
		else {
			isMouseHold = false;
			window.setMouseCursorVisible(true);
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Render(shader, scene, camera, window.getSize());

		window.display();
	}
}

