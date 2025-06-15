#ifndef GAME_H
#define GAME_H

#include <vector>
#include <iostream>

// SFML 3
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class AI;

#include "ai.h"

class Game {
public:
    Game();
    void run();
    int checkWin();

private:
    // Game constants
    static const int SCREENWIDTH = 900;
    static const int SCREENHEIGHT = 600;
    static const float LINE_THICKNESS;

    // SFML and game state members
    sf::RenderWindow window;
    sf::Font font;
    std::vector<sf::RectangleShape> gridLines;
    std::vector<std::vector<int>> boardStatus;
    int turn;
    bool gameOver;

    enum class GameState { MainMenu, DifficultyMenu, Playing, GameOver };
    enum class GameMode { TwoPlayer, VsAI };

    GameState gameState;
    GameMode gameMode;
    std::unique_ptr<AI> aiPlayer;

    sf::Text titleText;
    sf::Text twoPlayerButton;
    sf::Text vsAiButton;
    sf::Text easyButton;
    sf::Text mediumButton;
    sf::Text hardButton;

    void processMainMenuEvents(const std::optional<sf::Event>& event);
    void processDifficultyMenuEvents(const std::optional<sf::Event>& event);
    void processPlayingEvents(const std::optional<sf::Event>& event);
    void renderMainMenu();
    void renderDifficultyMenu();
    void renderPlaying();

    sf::Text winText;
    sf::Text instructionText;

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
    void checkAndSetWinText();
    void resetGame();
};

#endif // GAME_H