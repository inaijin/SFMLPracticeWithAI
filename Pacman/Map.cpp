#include <iostream>

#include "Map.h"

std::vector<std::vector<TileType>> createTileMapFromStrings() {
    std::vector<std::vector<TileType>> tileMap;

    for (const std::string& rowString : MAP_LAYOUT_STRINGS) {
        std::vector<TileType> rowTiles;
        for (char tileChar : rowString) {
            switch (tileChar) {
                case WALL_CHAR:
                    rowTiles.push_back(TileType::Wall);
                    break;
                case EMPTY_CHAR:
                    rowTiles.push_back(TileType::Empty);
                    break;
                // Add more cases for other tile types if you introduce them
                // case FOOD_CHAR:
                //     rowTiles.push_back(TileType::Food); // Assuming TileType::Food exists
                //     break;
                // case POWER_PELLET_CHAR:
                //     rowTiles.push_back(TileType::PowerPellet); // Assuming TileType::PowerPellet exists
                //     break;
                // case GHOST_SPAWN_CHAR:
                //     rowTiles.push_back(TileType::GhostSpawn); // Assuming TileType::GhostSpawn exists
                //     break;
                // case PACMAN_SPAWN_CHAR:
                //     rowTiles.push_back(TileType::PacManSpawn); // Assuming TileType::PacManSpawn exists
                //     break;
                default:
                    std::cerr << "Warning: Unknown tile character '" << tileChar << "' in map. Defaulting to Wall.\n";
                    rowTiles.push_back(TileType::Wall);
                    break;
            }
        }
        tileMap.push_back(rowTiles);
    }

    return tileMap;
}
