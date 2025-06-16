#include "Tile.h"
#include "Pinky.h"

Pinky::Pinky(std::vector<float> dimensions, std::vector<float> initPosition, sf::Color color)
    : Ghost(dimensions, initPosition, color) {
    objectShape.setFillColor(color);
}

void Pinky::update(std::vector<std::vector<Tile>>* map) {
    move();
    handleColition(*(map));
}

void Pinky::move() {
    static sf::Clock clock;
    static float changeDirectionInterval = 0.5f;
    if (clock.getElapsedTime().asSeconds() > changeDirectionInterval) {
        direction = {-1, 0};
    }
    if (direction != sf::Vector2f(0, 0)) {
        lastDirection = direction;
    }
}
