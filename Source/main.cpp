#include "Application.hpp"
#include "Inputs.hpp"
#include <SFML/Window.hpp>
#include <stdio.h>

int main(int argc, char** argv) {
	sf::ContextSettings settings;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	settings.depthBits = 24;

	sf::Window window(sf::VideoMode(800, 800), "3D OpenGL", sf::Style::Default, settings);
	if (glewInit() != GLEW_OK) {
		perror("Failed to initialize GLEW");
		return -1;
	}
	window.setMouseCursorVisible(true);

	const auto vertexCodeFile = "Source/vertex.glsl";
	const auto fragmentCodeFile = "Source/frag.glsl";
	const auto scene_fileName = argc > 1 ? argv[1] : "Models/source/Robin_Bird_M.fbx";
	Application app{ window.getSize(), scene_fileName, vertexCodeFile, fragmentCodeFile };
	Inputs input{};

	while (window.isOpen()) {
		sf::Event event{};
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { window.close(); }
			else if (event.type == sf::Event::Resized) {
				app.ResizeViewport(window.getSize());
			}
		}

		app.Clear();

		window.setMouseCursorVisible(!input.IsMouseHold());
		auto mouseRotation = input.IsMouseHold() ? sf::Mouse::getPosition(window) : sf::Vector2i{0, 0};
		app.Update(input.IsKeyPress(), mouseRotation);
		if (input.IsMouseHold()) {
			sf::Mouse::setPosition(app.Rotation_ComparativeMousePosition(), window);
		}

		app.Render();

		window.display();
	}
	return 0;
}