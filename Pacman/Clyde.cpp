#include "Tile.h"
#include "Clyde.h"

Clyde::Clyde(std::vector<float> dimensions, std::vector<float> initPosition, sf::Color color)
    : Ghost(dimensions, initPosition, color) {
    objectShape.setFillColor(color);
}

void Clyde::update(std::vector<std::vector<Tile>>* map) {
    move();
    handleColition(*(map));
}

void Clyde::move() {
    static sf::Clock clock;
    static float changeDirectionInterval = 0.5f;
    if (clock.getElapsedTime().asSeconds() > changeDirectionInterval) {
        direction = {0, -1};
    }
    if (direction != sf::Vector2f(0, 0)) {
        lastDirection = direction;
    }
}
