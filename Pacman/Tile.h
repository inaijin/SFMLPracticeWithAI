#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

enum class TileType {
    Empty,
    Wall,
    PowerUp
};

class Tile {
public:
    Tile();
    Tile(TileType type, float x, float y);
    TileType getType() const;
    void removeTile();
    void draw(sf::RenderWindow& window);
    sf::RectangleShape getShape() const { return tileShape; }
private:
    TileType type;
    sf::RectangleShape tileShape;
};

#endif // TILE_H