#ifndef GAME_H
#define GAME_H

#include <vector>
#include <iostream>

// SFML 3
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    void run();

private:
    // Game constants
    static const int SCREENWIDTH = 900;
    static const int SCREENHEIGHT = 600;
    static const float LINE_THICKNESS;

    // SFML and game state members
    sf::RenderWindow window;
    sf::Font font;
    sf::Text winText;
    sf::Text instructionText;
    std::vector<sf::RectangleShape> gridLines;
    std::vector<std::vector<int>> boardStatus;
    int turn;
    bool gameOver;

    // Core methods
    void processEvents();
    void update();
    void render();

    // Helper methods from your original code
    void initVectorStatus();
    void resetBoard();
    sf::RectangleShape createVerticalLine(float xPosition);
    sf::RectangleShape createHorizontalLine(float yPosition);
    int detectZone(bool isWidth, int currentPos);
    void placeXorO(int row, int col);
    void drawBoardElements();
    int checkWin();
    void checkAndSetWinText();
};

#endif // GAME_H