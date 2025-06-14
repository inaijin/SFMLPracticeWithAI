#include "Grid.h"
#include "Constants.h"

Grid::Grid() {
    gridShape.setSize({SCREEN_WIDTH, SCREEN_HEIGHT});
    gridShape.setFillColor(sf::Color::Green);
    gridShape.setPosition({0, 0});
}

void Grid::draw(sf::RenderWindow& window) {
    window.draw(gridShape);
}
