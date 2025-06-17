#include "Tile.h"
#include "Blinky.h"

Blinky::Blinky(std::vector<float> dimensions, std::vector<float> initPosition, sf::Color color)
    : Ghost(dimensions, initPosition, color) {
    objectShape.setFillColor(color);
    ai = std::make_unique<GhostAI>(0.1, 0.9, 0.1);
}

float distance(const sf::Vector2f& p1, const sf::Vector2f& p2) {
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}

double Blinky::calculateReward(const sf::Vector2f& old_position, const Pacman& pacman, const Blinky* blinky) {
    sf::Vector2f pacman_pos = pacman.getShape().getPosition();
    sf::Vector2f new_position = getShape().getPosition();

    float old_dist = distance(old_position, pacman_pos);
    float new_dist = distance(new_position, pacman_pos);

    if (new_dist < old_dist) {
        return 1.0;
    } else {
        return -1.0;
    }
}
