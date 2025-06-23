#include <SFML/Window/Keyboard.hpp>

#include "Pacman.h"
#include "Constants.h"

Pacman::Pacman(std::vector<float> dimensions, std::vector<float> initPosition)
    : GameObject(dimensions, initPosition, 2.0f), powerUpActive(false),
      powerUpDuration(sf::seconds(5.0f)) {
    objectShape.setFillColor(sf::Color::Yellow);
    ai = std::make_unique<GhostAI>(0.1, 0.9, 0.1);
}

bool Pacman::updatePacman(std::vector<Ghost*>& ghosts, std::vector<std::vector<Tile>>* map) {
    bool shouldReset = false;

    if (is_training) {
        shouldReset = updateAI(ghosts, map);
    } else {
        handleInput();
        handleColitionWithPowerUp(map);
        handleColition(*map);
        handleColitionWithGhosts(&ghosts);
    }

    if (powerUpActive && powerUpClock.getElapsedTime() >= powerUpDuration) {
        powerUpActive = false;
        objectShape.setFillColor(sf::Color::Yellow);
    }

    return shouldReset;
}

void Pacman::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        direction = {0, -1};
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        direction = {0, 1};
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        direction = {-1, 0};
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        direction = {1, 0};
    }

    if (direction != sf::Vector2f(0, 0)) {
        lastDirection = direction;
    }
}

void Pacman::handleColitionWithPowerUp(std::vector<std::vector<Tile>>* map) {
    sf::Vector2f nextPosition = getNextPosition();
    sf::Vector2f pacmanSize = getShape().getSize();
    sf::FloatRect nextBounds(nextPosition, pacmanSize);

    for (auto& row : *(map)) {
        for (auto& tile : row) {
            if (tile.getType() == TileType::PowerUp) {
                const auto tileBounds = tile.getShape().getGlobalBounds();
                if (nextBounds.findIntersection(tileBounds)) {
                    tile.removeTile();
                    objectShape.setFillColor(sf::Color::Blue);
                    powerUpActive = true;
                    powerUpClock.restart();
                }
            }
        }
    }
}

void Pacman::handleColitionWithGhosts(std::vector<Ghost*>* ghosts) {
    sf::FloatRect pacmanBounds = getShape().getGlobalBounds();

    for (auto& ghost : *ghosts) {
        sf::FloatRect ghostBounds = ghost->getShape().getGlobalBounds();

        if (pacmanBounds.findIntersection(ghostBounds)) {
            if (powerUpActive) {
                ghost->die();
            } else {
                die();
            }
        }
    }
}

float distance(const sf::Vector2f& p1, const sf::Vector2f& p2) {
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}

void Pacman::setTrainingMode(bool is_training) {
    this->is_training = is_training;
}

bool Pacman::updateAI(const std::vector<Ghost*>& ghosts, std::vector<std::vector<Tile>>* map) {
    sf::Vector2f old_pos = getShape().getPosition();
    std::string current_state = createAIState(ghosts, *map);

    Action chosen_action = ai->chooseAction(current_state);

    switch (chosen_action) {
        case Action::Up:    direction = {0, -1}; break;
        case Action::Down:  direction = {0, 1};  break;
        case Action::Left:  direction = {-1, 0}; break;
        case Action::Right: direction = {1, 0};  break;
        case Action::None:  direction = {0, 0};  break;
    }

    bool ate_power_up = handlePelletAndPowerUpCollisions(map);
    bool killedSingleGhost = false;
    bool ate_all_ghost = false;
    bool died = false;

    sf::FloatRect pacmanBounds = getShape().getGlobalBounds();
    for (auto& ghost : ghosts) {
        sf::FloatRect ghostBounds = ghost->getShape().getGlobalBounds();
        if (pacmanBounds.findIntersection(ghostBounds)) {
            if (powerUpActive) {
                ghost->die();
                killedSingleGhost = true;
                increamentGhostsKilled();
            } else {
                died = true;
            }
        }
    }

    if (howManyGhostsKilled == 4)
        ate_all_ghost = true;

    handleColition(*map);
    if (direction != sf::Vector2f(0, 0)) lastDirection = direction;

    std::string next_state = createAIState(ghosts, *map);
    double reward = calculateReward(old_pos, ghosts, ate_power_up, killedSingleGhost, died);
    ai->updateQValue(current_state, chosen_action, reward, next_state);

    return ate_all_ghost || died;
}

std::string Pacman::createAIState(const std::vector<Ghost*>& ghosts, const std::vector<std::vector<Tile>>& map) const {
    std::string state = "";

    state += std::to_string(static_cast<int>(objectShape.getPosition().x / TILE_SIZE)) + "_";
    state += std::to_string(static_cast<int>(objectShape.getPosition().y / TILE_SIZE));

    for(const auto& ghost : ghosts) {
        state += "_" + std::to_string(static_cast<int>(ghost->getShape().getPosition().x / TILE_SIZE));
        state += "_" + std::to_string(static_cast<int>(ghost->getShape().getPosition().y / TILE_SIZE));
    }

    sf::Vector2f pellet_pos = findClosestPellet(map);
    state += "_" + std::to_string(static_cast<int>(pellet_pos.x / TILE_SIZE));
    state += "_" + std::to_string(static_cast<int>(pellet_pos.y / TILE_SIZE));

    return state;
}

sf::Vector2f Pacman::findClosestPellet(const std::vector<std::vector<Tile>>& map) const {
    sf::Vector2f pacman_pos = getShape().getPosition();
    sf::Vector2f closest_pellet_pos = {-1, -1};
    float min_dist = std::numeric_limits<float>::max();

    for (const auto& row : map) {
        for (const auto& tile : row) {
            if (tile.getType() == TileType::PowerUp) {
                float d = distance(pacman_pos, tile.getShape().getPosition());
                if (d < min_dist) {
                    min_dist = d;
                    closest_pellet_pos = tile.getShape().getPosition();
                }
            }
        }
    }
    return closest_pellet_pos;
}

double Pacman::calculateReward(const sf::Vector2f& old_position, const std::vector<Ghost*>& ghosts, bool ate_power_up, bool ate_ghost, bool died) const {
    if (died) return -100.0;
    if (ate_ghost) return 50.0;
    if (ate_power_up) return 25.0;

    double reward = 0.0;

    sf::Vector2f pacman_pos = getShape().getPosition();
    float min_dist_to_ghost = std::numeric_limits<float>::max();
    float old_min_dist_to_ghost = std::numeric_limits<float>::max();
    float old_dist_to_pallet = std::numeric_limits<float>::max();
    float dist_to_pallet = std::numeric_limits<float>::max();

    for (const auto& ghost : ghosts) {
        min_dist_to_ghost = std::min(min_dist_to_ghost, distance(pacman_pos, ghost->getShape().getPosition()));
        old_min_dist_to_ghost = std::min(old_min_dist_to_ghost, distance(old_position, ghost->getShape().getPosition()));
    }

    std::vector<sf::Vector2f> pallets;
    pallets.push_back({1180, 955});
    pallets.push_back({366, 955});

    for (int i = 0; i < 2; i++) {
        dist_to_pallet = std::min(dist_to_pallet, distance(pacman_pos, pallets[i]));
        old_dist_to_pallet = std::min(old_dist_to_pallet, distance(old_position, pallets[i]));
    }

    if (min_dist_to_ghost > old_min_dist_to_ghost) reward += 1.0;
    else reward -= 1.5;

    if (dist_to_pallet > old_dist_to_pallet) reward += 0.5;
    else reward -= 0.75;

    reward -= 0.1;

    return reward;
}

bool Pacman::handlePelletAndPowerUpCollisions(std::vector<std::vector<Tile>>* map) {
    sf::FloatRect nextBounds(getNextPosition(), getShape().getSize());

    for (auto& row : *map) {
        for (auto& tile : row) {
            if (tile.getType() == TileType::PowerUp) {
                if (nextBounds.findIntersection(tile.getShape().getGlobalBounds())) {
                    tile.removeTile();
                    powerUpActive = true;
                    powerUpClock.restart();
                    objectShape.setFillColor(sf::Color::Blue);
                    return true;
                }
            }
        }
    }
    return false;
}

void Pacman::reset() {
    this->powerUpActive = false;
    this->objectShape.setFillColor(sf::Color::Yellow);
    this->objectShape.setPosition({800, 800});
}
