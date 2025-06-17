#include <cmath>

#include "Inky.h"
#include "Pacman.h"
#include "Blinky.h"
#include "Constants.h"

float distance(const sf::Vector2f& p1, const sf::Vector2f& p2);

Inky::Inky(std::vector<float> dimensions, std::vector<float> initPosition, sf::Color color)
    : Ghost(dimensions, initPosition, color) {
    objectShape.setFillColor(color);
    ai = std::make_unique<GhostAI>(0.1, 0.9, 0.2);
}

double Inky::calculateReward(const sf::Vector2f& old_position, const Pacman& pacman, const Blinky* blinky) {
    if (!blinky) {
        float old_dist = distance(old_position, pacman.getShape().getPosition());
        float new_dist = distance(getShape().getPosition(), pacman.getShape().getPosition());
        return (new_dist < old_dist) ? 1.0 : -1.0;
    }

    sf::Vector2f pacman_pos = pacman.getShape().getPosition();
    sf::Vector2f pacman_dir = pacman.getLastDirection();
    float offset = 2.0f * TILE_SIZE;
    sf::Vector2f pivot_pos = pacman_pos + (pacman_dir * offset);

    sf::Vector2f blinky_pos = blinky->getShape().getPosition();
    sf::Vector2f vector_from_blinky = pivot_pos - blinky_pos;

    sf::Vector2f target_pos = blinky_pos + (vector_from_blinky * 2.f);

    float old_dist_to_target = distance(old_position, target_pos);
    float new_dist_to_target = distance(getShape().getPosition(), target_pos);

    if (new_dist_to_target < old_dist_to_target) {
        return 1.0;
    } else {
        return -1.0;
    }
}
