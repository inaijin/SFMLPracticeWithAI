#include "Tile.h"
#include "Ghost.h"
#include "Constants.h"

Ghost::Ghost(std::vector<float> dimensions, std::vector<float> initPosition, sf::Color color)
    : GameObject(dimensions, initPosition, 1.5f) {
    objectShape.setFillColor(color);
}

std::string Ghost::createAIState(const Pacman& pacman) const {
    // Convert pixel coordinates to tile coordinates
    int ghost_tile_x = static_cast<int>(objectShape.getPosition().x / TILE_SIZE);
    int ghost_tile_y = static_cast<int>(objectShape.getPosition().y / TILE_SIZE);
    int pacman_tile_x = static_cast<int>(pacman.getShape().getPosition().x / TILE_SIZE);
    int pacman_tile_y = static_cast<int>(pacman.getShape().getPosition().y / TILE_SIZE);

    // Serialize the state into a unique string key
    return std::to_string(ghost_tile_x) + "_" + std::to_string(ghost_tile_y) +
           "_" + std::to_string(pacman_tile_x) + "_" + std::to_string(pacman_tile_y);
}

void Ghost::update(const Pacman& pacman, const Blinky* blinky, std::vector<std::vector<Tile>>* map) {
    sf::Vector2f old_position = getShape().getPosition();
    std::string current_state = createAIState(pacman);

    Action chosen_action = ai->chooseAction(current_state);

    switch (chosen_action) {
        case Action::Up:    direction = {0, -1}; break;
        case Action::Down:  direction = {0, 1};  break;
        case Action::Left:  direction = {-1, 0}; break;
        case Action::Right: direction = {1, 0};  break;
        case Action::None:  direction = {0, 0};  break;
    }

    handleColition(*map);
    if (direction != sf::Vector2f(0, 0)) {
        lastDirection = direction;
    }

    std::string next_state = createAIState(pacman);

    double reward = calculateReward(old_position, pacman, blinky);

    ai->updateQValue(current_state, chosen_action, reward, next_state);
}

float distance(const sf::Vector2f& p1, const sf::Vector2f& p2) {
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}
