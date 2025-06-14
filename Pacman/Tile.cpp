#include "Tile.h"
#include "Constants.h"

Tile::Tile() : type(TileType::Empty) {
    tileShape.setSize({tile_diemensions[0], tile_diemensions[1]});
    tileShape.setPosition({0, 0});
    tileShape.setFillColor(sf::Color::Transparent);
}

Tile::Tile(TileType type, float x, float y) : type(type) {
    tileShape.setSize({tile_diemensions[0], tile_diemensions[1]});
    tileShape.setPosition({x, y});

    switch (type) {
        case TileType::Wall:
            tileShape.setFillColor(sf::Color(128, 128, 128));
            break;
        case TileType::Empty:
            tileShape.setFillColor(sf::Color::Transparent);
            break;
        case TileType::Pellet:
            tileShape.setFillColor(sf::Color::White);
            break;
        case TileType::PowerUp:
            tileShape.setFillColor(sf::Color::Red);
            break;
    }
}

TileType Tile::getType() const {
    return type;
}

void Tile::draw(sf::RenderWindow& window) {
    window.draw(tileShape);
}
