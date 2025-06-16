#include <SFML/Window/Keyboard.hpp>

#include "Pacman.h"

Pacman::Pacman(std::vector<float> dimensions, std::vector<float> initPosition)
    : GameObject(dimensions, initPosition, 2.0f), powerUpActive(false),
      powerUpDuration(sf::seconds(5.0f)) {
    objectShape.setFillColor(sf::Color::Yellow);
}

void Pacman::update(std::vector<std::vector<Tile>>* map) {
    handleInput();
    handleColitionWithPowerUp(map);
    handleColition(*(map));

    if (powerUpActive) {
        if (powerUpClock.getElapsedTime() >= powerUpDuration) {
            powerUpActive = false;
            objectShape.setFillColor(sf::Color::Yellow);
        }
    }
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
