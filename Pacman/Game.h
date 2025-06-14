#ifndef GAME_H
#define GAME_H

#include <vector>
#include <optional>
#include <SFML/Graphics.hpp>

#include "Grid.h"
#include "Tile.h"
#include "Ghost.h"
#include "Pacman.h"

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    sf::RenderWindow window;
    Pacman pacman;
    Ghost redGhost;
    Ghost blueGhost;
    Ghost pinkGhost;
    Ghost orangeGhost;
    Grid grid;
    std::vector<std::vector<Tile>> map;
    void loadMap();
};

#endif // GAME_H