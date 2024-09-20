#pragma once
#include "Shader.hpp"
#include "Camera.hpp"
#include "Scene.hpp"
#include <GL/glew.h>
#include <SFML/System/Clock.hpp>

class Application {
public:
	Application(sf::Vector2u _windowSize, std::string scene_fileName, std::string vertexFile, std::string fragmentFile);

	void Update(sf::Vector2i moveDirection, sf::Vector2i mousePosition);
	void Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
	void Render();
	void ResizeViewport(sf::Vector2u _windowSize);
	sf::Vector2i Rotation_ComparativeMousePosition() const { return camera.lastMousePos; }
private:
	sf::Clock clock{};
	sf::Vector2u windowSize;
	Shader shader{};
	Scene scene{};
	Camera camera{glm::vec3(-14.6f, 17.0f, 7.3f), -400.5f, -26.7f};
};