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

enum class GameState {
    MainMenu,
    Training,
    Play
};

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    GameState current_state;
    sf::Font font;

    void runMainMenu();
    void runGameSession();

    void resetGame();
    void saveAITables();
    void loadAITables();

    sf::RenderWindow window;
    Pacman pacman;
    std::vector<Ghost*> ghosts;
    Grid grid;
    std::vector<std::vector<Tile>> map;
    void loadMap();

    sf::Text train_button;
    sf::Text play_button;
};

#endif // GAME_H