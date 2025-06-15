#ifndef GAME_H
#define GAME_H

#include <vector>
#include <optional>
#include <SFML/Graphics.hpp>

#include "Grid.h"
#include "Tile.h"
#include "Ghost.h"
#include "Blinky.h"
#include "Pinky.h"
#include "Inky.h"
#include "Clyde.h"
#include "Pacman.h"

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    sf::RenderWindow window;
    Pacman pacman;
    std::vector<Ghost*> ghosts;
    Grid grid;
    std::vector<std::vector<Tile>> map;
    void loadMap();
};

#endif // GAME_H