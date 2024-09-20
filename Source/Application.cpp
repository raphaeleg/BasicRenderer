#include "Application.hpp"
#include "Helper.hpp"

Application::Application(sf::Vector2u _windowSize, std::string scene_fileName, std::string vertexFile, std::string fragmentFile) {
	glEnable(GL_DEPTH_TEST);

	windowSize = _windowSize;
	shader = Shader(ReadTextFile(vertexFile), ReadTextFile(fragmentFile));
	scene = Scene(scene_fileName);

	shader.Use();
	shader.SetValue("ambientStrength", 0.1f);
	shader.SetValue("lightColor", glm::vec3(1.0f));
}

void Application::Update(sf::Vector2i moveDirection, sf::Vector2i mousePosition) {
	float deltaTime = clock.restart().asSeconds();
	camera.Update(deltaTime, moveDirection, mousePosition);
}

void Application::Render() {
	shader.Use();
	shader.SetValue("view", camera.GetViewMatrix());
	shader.SetValue("projection", camera.GetProjectionMatrix(windowSize.x, windowSize.y));
	shader.SetValue("lightPos", camera.position);
	shader.SetValue("viewPos", camera.position);

	scene.Draw(shader);
}

void Application::ResizeViewport(sf::Vector2u _windowSize) {
	windowSize = _windowSize;
	glViewport(0, 0, windowSize.x, windowSize.y);
}