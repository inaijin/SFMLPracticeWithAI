#include "Tile.h"
#include "Blinky.h"

Blinky::Blinky(std::vector<float> dimensions, std::vector<float> initPosition, sf::Color color)
    : Ghost(dimensions, initPosition, color) {
    objectShape.setFillColor(color);
}

void Blinky::update(std::vector<std::vector<Tile>> map) {
    move();
    handleColition(map);
}

void Blinky::move() {
    static sf::Clock clock;
    static float changeDirectionInterval = 0.5f;
    if (clock.getElapsedTime().asSeconds() > changeDirectionInterval) {
        direction = {0, 1};
    }
    if (direction != sf::Vector2f(0, 0)) {
        lastDirection = direction;
    }
}
