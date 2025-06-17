#include <cmath>

#include "Clyde.h"
#include "Pacman.h"
#include "Constants.h"

Clyde::Clyde(std::vector<float> dimensions, std::vector<float> initPosition, sf::Color color)
    : Ghost(dimensions, initPosition, color) {
    objectShape.setFillColor(color);
    ai = std::make_unique<GhostAI>(0.1, 0.9, 0.5);
}

double Clyde::calculateReward(const sf::Vector2f& old_position, const Pacman& pacman, const Blinky* blinky) {
    sf::Vector2f pacman_pos = pacman.getShape().getPosition();
    sf::Vector2f current_pos = getShape().getPosition();
    
    float dist_to_pacman = distance(current_pos, pacman_pos);

    sf::Vector2f target_pos;

    if (dist_to_pacman > 8.0f * TILE_SIZE) {
        target_pos = pacman_pos;
    } else {
        target_pos = scatter_target;
    }

    float old_dist_to_target = distance(old_position, target_pos);
    float new_dist_to_target = distance(current_pos, target_pos);

    if (new_dist_to_target < old_dist_to_target) {
        return 1.0;
    } else {
        return -1.0;
    }
}
