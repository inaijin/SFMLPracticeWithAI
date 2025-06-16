#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>

#include "Tile.h"

class GameObject {
public:
    GameObject(std::vector<float> dimensions, std::vector<float> initPosition, float speed);
    void virtual update(std::vector<std::vector<Tile>>* map);
    void draw(sf::RenderWindow& window);
    void setPosition(const sf::Vector2f& newPosition);
    sf::Vector2f getNextPosition() const;
    const sf::RectangleShape& getShape() const;
    void die();

    sf::Vector2f getLastDirection() const { return lastDirection; }
    float getSpeed() { return speed; }

protected:
    sf::RectangleShape objectShape;
    sf::Vector2f direction;
    sf::Vector2f lastDirection;
    float speed;
    void handleColition(std::vector<std::vector<Tile>> map);
};

#endif // GAMEOBJECT_H