#include <SFML/Window.hpp>
#include <string>
// at different OSes, OpenGL is located at different places. Use the correct OpenGL header.
#include <SFML/OpenGL.hpp>

static constexpr int WIDTH = 1200;
static constexpr int HEIGHT = 900;
static std::string TITLE = "3D OpenGL";


int main() {
	sf::Window window(sf::VideoMode(WIDTH, HEIGHT), TITLE);

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