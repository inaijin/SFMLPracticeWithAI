#include "Tile.h"
#include "Constants.h"
#include "GameObject.h"

GameObject::GameObject(std::vector<float> dimentions, std::vector<float> initPosition, float speed)
    : lastDirection(1, 0) {
    this->speed = speed;
    objectShape.setSize({dimentions[0], dimentions[1]});
    objectShape.setFillColor(sf::Color::Yellow);
    objectShape.setPosition({initPosition[0], initPosition[1]});
}

void GameObject::update(std::vector<std::vector<Tile>>* map) {}

sf::Vector2f GameObject::getNextPosition() const {
    return objectShape.getPosition() + direction * speed;
}

void GameObject::setPosition(const sf::Vector2f& newPosition) {
    objectShape.setPosition(newPosition);
}

const sf::RectangleShape& GameObject::getShape() const {
    return objectShape;
}

void GameObject::draw(sf::RenderWindow& window) {
    window.draw(objectShape);
}

void GameObject::handleColition(std::vector<std::vector<Tile>> map) {
    sf::Vector2f nextPosition = getNextPosition();
    sf::Vector2f pacmanSize = getShape().getSize();
    sf::FloatRect nextBounds(nextPosition, pacmanSize);

    bool collisionFound = false;
    for (const auto& row : map) {
        for (const auto& tile : row) {
            if (tile.getType() == TileType::Wall) {
                const auto tileBounds = tile.getShape().getGlobalBounds();
                if (nextBounds.findIntersection(tileBounds)) {
                    collisionFound = true;
                    break;
                }
            }
        }
        if (collisionFound) {
            break;
        }
    }

    if (!collisionFound) {
        setPosition(nextPosition);
    }
}
