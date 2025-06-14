#include <SFML/Window/Keyboard.hpp>

#include "Pacman.h"

Pacman::Pacman(std::vector<float> dimensions, std::vector<float> initPosition)
    : GameObject(dimensions, initPosition, 2.0f) {
    objectShape.setFillColor(sf::Color::Yellow);
}

void Pacman::update(std::vector<std::vector<Tile>> map) {
    handleInput();
    handleColition(map);
}

void Pacman::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        direction = {0, -1};
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        direction = {0, 1};
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        direction = {-1, 0};
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        direction = {1, 0};
    }

    if (direction != sf::Vector2f(0, 0)) {
        lastDirection = direction;
    }
}
