#include <cmath>

#include "Pinky.h"
#include "Pacman.h"
#include "Constants.h"

Pinky::Pinky(std::vector<float> dimensions, std::vector<float> initPosition, sf::Color color)
    : Ghost(dimensions, initPosition, color) {
    objectShape.setFillColor(color);
    ai = std::make_unique<GhostAI>(0.1, 0.9, 0.05);
}

double Pinky::calculateReward(const sf::Vector2f& old_position, const Pacman& pacman, const Blinky* blinky) {
    sf::Vector2f pacman_pos = pacman.getShape().getPosition();
    sf::Vector2f pacman_dir = pacman.getLastDirection();
    float offset = 4.0f * TILE_SIZE;
    sf::Vector2f target_pos = pacman_pos + (pacman_dir * offset);

    float old_dist_to_target = distance(old_position, target_pos);
    float new_dist_to_target = distance(getShape().getPosition(), target_pos);

    if (new_dist_to_target < old_dist_to_target) {
        return 1.5;
    } else {
        return -1.0;
    }
}
