#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>

class Grid {
public:
    Grid();
    void draw(sf::RenderWindow& window);
private:
    sf::RectangleShape gridShape;
};

#endif // GRID_H