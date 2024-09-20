#include "Inputs.hpp"
#include <SFML/Window.hpp>

sf::Vector2i Inputs::IsKeyPress() {
	sf::Vector2i v{ 0,0 };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { v.x++; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { v.x--; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { v.y--; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { v.y++; }
	return v;
}