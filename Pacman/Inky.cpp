#include "Tile.h"
#include "Inky.h"

Inky::Inky(std::vector<float> dimensions, std::vector<float> initPosition, sf::Color color)
    : Ghost(dimensions, initPosition, color) {
    objectShape.setFillColor(color);
}

void Inky::update(std::vector<std::vector<Tile>>* map) {
    move();
    handleColition(*(map));
}

void Inky::move() {
    static sf::Clock clock;
    static float changeDirectionInterval = 0.5f;
    if (clock.getElapsedTime().asSeconds() > changeDirectionInterval) {
        direction = {1, 0};
    }
    if (direction != sf::Vector2f(0, 0)) {
        lastDirection = direction;
    }
}
