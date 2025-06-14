#include <optional>

#include "Map.h"
#include "Game.h"
#include "Tile.h"
#include "Constants.h"

const float TILE_SIZE = 30.0f;

Game::Game()
: window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "Pacman"),
pacman(pacman_diemensions, {85, 100}),
redGhost(ghost_diemensions, {245, 195}, sf::Color::Red),
blueGhost(ghost_diemensions, {1333, 195}, sf::Color::Blue),
pinkGhost(ghost_diemensions, {85, 905}, sf::Color::Magenta),
orangeGhost(ghost_diemensions, {1500, 905}, sf::Color(255, 165, 0)) {
    window.setFramerateLimit(framePS);
    loadMap();
}

Game::~Game() {
    map.clear();
}

void Game::run() {
    while (window.isOpen()) {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // --- Update game logic here ---

        pacman.update(map);
        redGhost.update(map);
        blueGhost.update(map);
        pinkGhost.update(map);
        orangeGhost.update(map);

        // --- Draw game elements here ---
        window.clear(sf::Color::Black);

        for (auto& row : map) {
            for (auto& tile : row)
                tile.draw(window);
        }

        pacman.draw(window);
        redGhost.draw(window);
        blueGhost.draw(window);
        pinkGhost.draw(window);
        orangeGhost.draw(window);

        window.display();
    }
}

void Game::loadMap() {
    std::vector<std::vector<TileType>> tileTypeData = createTileMapFromStrings();

    map.resize(tileTypeData.size());

    for (std::size_t i = 0; i < tileTypeData.size(); ++i) {
        map[i].resize(tileTypeData[i].size());
        for (std::size_t j = 0; j < tileTypeData[i].size(); ++j) {
            TileType currentTileType = tileTypeData[i][j];

            // Corrected position calculations
            float xPos = static_cast<float>(j * TILE_SIZE);
            float yPos = static_cast<float>(i * TILE_SIZE);

            map[i][j] = Tile(currentTileType, xPos, yPos);

            // // Optional: Set initial positions for Pacman and Ghosts based on map
            // if (currentTileType == TileType::PacManSpawn) {
            //     pacman.setPosition({xPos + TILE_SIZE / 2.f, yPos + TILE_SIZE / 2.f});
            // } else if (currentTileType == TileType::GhostSpawn) {
            //     ghost.setPosition({xPos + TILE_SIZE / 2.f, yPos + TILE_SIZE / 2.f});
            // }
        }
    }
}
