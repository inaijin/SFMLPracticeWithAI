#include "Tile.h"
#include "Ghost.h"

Ghost::Ghost(std::vector<float> dimensions, std::vector<float> initPosition, sf::Color color)
    : GameObject(dimensions, initPosition, 1.5f) {
    objectShape.setFillColor(color);
}

void Ghost::update(std::vector<std::vector<Tile>> map) {
    randomMovement();
    handleColition(map);
}

void Ghost::randomMovement() {
    static sf::Clock clock;
    static float changeDirectionInterval = 0.5f;
    if (clock.getElapsedTime().asSeconds() > changeDirectionInterval) {
        int dir = rand() % 4;
        switch (dir) {
            case 0: direction = {0, -1}; break;
            case 1: direction = {0, 1}; break;
            case 2: direction = {-1, 0}; break;
            case 3: direction = {1, 0}; break;
        }
        clock.restart();
    }
    if (direction != sf::Vector2f(0, 0)) {
        lastDirection = direction;
    }
}
