#pragma once
#include <SFML/Window.hpp>
class Inputs {
public:
    sf::Vector2i IsKeyPress();
    bool IsMouseHold() {
        return sf::Mouse::isButtonPressed(sf::Mouse::Right);
    }
};