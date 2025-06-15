#include "ai.h"
#include "game.h"

const float Game::LINE_THICKNESS = 3.0f;

sf::Font loadGameFont() {
    sf::Font font;
    if (!font.openFromFile("fonts/arial.ttf")) {
        std::cerr << "Fatal Error: Failed to load font arial.ttf!" << std::endl;
    }
    return font;
}

Game::Game() :
    window(sf::VideoMode({SCREENWIDTH, SCREENHEIGHT}), "Tic Tac Toe"),
    font(loadGameFont()),
    gameState(GameState::MainMenu),
    titleText(font, "Tic Tac Toe", 60),
    twoPlayerButton(font, "2 Players", 40),
    vsAiButton(font, "Play vs. AI", 40),
    easyButton(font, "Easy", 40),
    mediumButton(font, "Medium", 40),
    hardButton(font, "Hard", 40),
    winText(font, "", 50),
    instructionText(font, "Click to play again", 30)
{
    window.setFramerateLimit(60);

    instructionText.setFillColor(sf::Color::White);

    turn = 0;
    gameOver = false;
    initVectorStatus();

    sf::FloatRect titleRect = titleText.getLocalBounds();
    titleText.setOrigin({titleRect.position.x + titleRect.size.x / 2.0f, titleRect.position.y + titleRect.size.y / 2.0f});
    titleText.setPosition({SCREENWIDTH / 2.0f, SCREENHEIGHT / 4.0f});

    // Two Player Button
    sf::FloatRect twoPlayerRect = twoPlayerButton.getLocalBounds();
    twoPlayerButton.setOrigin({twoPlayerRect.position.x + twoPlayerRect.size.x / 2.0f, twoPlayerRect.position.y + twoPlayerRect.size.y / 2.0f});
    twoPlayerButton.setPosition({SCREENWIDTH / 2.0f, SCREENHEIGHT / 2.0f});

    // AI Button
    sf::FloatRect vsAiRect = vsAiButton.getLocalBounds();
    vsAiButton.setOrigin({vsAiRect.position.x + vsAiRect.size.x / 2.0f, vsAiRect.position.y + vsAiRect.size.y / 2.0f});
    vsAiButton.setPosition({SCREENWIDTH / 2.0f, SCREENHEIGHT / 2.0f + 60.f});

    sf::FloatRect easyRect = easyButton.getLocalBounds();
    easyButton.setOrigin({easyRect.position.x + easyRect.size.x / 2.0f, easyRect.position.y + easyRect.size.y / 2.0f});
    easyButton.setPosition({SCREENWIDTH / 2.0f, SCREENHEIGHT / 2.0f - 60.f});

    sf::FloatRect mediumRect = mediumButton.getLocalBounds();
    mediumButton.setOrigin({mediumRect.position.x + mediumRect.size.x / 2.0f, mediumRect.position.y + mediumRect.size.y / 2.0f});
    mediumButton.setPosition({SCREENWIDTH / 2.0f, SCREENHEIGHT / 2.0f});

    sf::FloatRect hardRect = hardButton.getLocalBounds();
    hardButton.setOrigin({hardRect.position.x + hardRect.size.x / 2.0f, hardRect.position.y + hardRect.size.y / 2.0f});
    hardButton.setPosition({SCREENWIDTH / 2.0f, SCREENHEIGHT / 2.0f + 60.f});

    gridLines.push_back(createVerticalLine(SCREENWIDTH / 3.0f));
    gridLines.push_back(createVerticalLine(2.0f * SCREENWIDTH / 3.0f));
    gridLines.push_back(createHorizontalLine(SCREENHEIGHT / 3.0f));
    gridLines.push_back(createHorizontalLine(2.0f * SCREENHEIGHT / 3.0f));
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::resetGame() {
    resetBoard();
    turn = 0;
    gameOver = false;
    winText.setString("");
    aiPlayer.reset();
    gameState = GameState::MainMenu;
}

void Game::processEvents() {
    while (auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window.close();
        switch (gameState) {
            case GameState::MainMenu:
                processMainMenuEvents(event);
                break;
            case GameState::DifficultyMenu:
                processDifficultyMenuEvents(event);
                break;
            case GameState::Playing:
                processPlayingEvents(event);
                break;
            case GameState::GameOver:
                if (event->is<sf::Event::MouseButtonPressed>())
                    resetGame();
                break;
        }
    }
}

void Game::update() {
    if (gameState == GameState::Playing && gameMode == GameMode::VsAI && !gameOver) {
        // Assuming Player is 0 ('X') and AI is 1 ('O'). The AI moves on odd turns.
        if (turn % 2 == 1) {
            std::pair<int, int> aiMove = aiPlayer->getMove(boardStatus);
            if (aiMove.first != -1) {
                placeXorO(aiMove.first, aiMove.second);
                checkAndSetWinText();
            }
        }
    }
}

void Game::render() {
    window.clear(sf::Color::Black);

    switch (gameState) {
        case GameState::MainMenu:
            renderMainMenu();
            break;
        case GameState::DifficultyMenu:
            renderDifficultyMenu();
            break;
        case GameState::Playing:
        case GameState::GameOver:
            renderPlaying();
            break;
    }

    window.display();
}

void Game::initVectorStatus() {
    boardStatus.clear();
    for (int i = 0; i < 3; i++) {
        std::vector<int> row(3, -1);
        boardStatus.push_back(row); 
    }
}

void Game::placeXorO(int row, int col) {
    boardStatus[row][col] = (turn % 2 == 0) ? 0 : 1;
    turn++;
}

void Game::drawBoardElements() {
    float cellWidth = SCREENWIDTH / 3.0f;
    float cellHeight = SCREENHEIGHT / 3.0f;
    float padding = 30.0f;

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            int value = boardStatus[row][col];
            float cellX = col * cellWidth;
            float cellY = row * cellHeight;
            sf::Vector2f cellCenter(cellX + cellWidth / 2.f, cellY + cellHeight / 2.f);

            if (value == 0) { // Draw X
                float xLineLength = std::min(cellWidth, cellHeight) - 2 * padding;
                sf::RectangleShape line1;
                line1.setSize(sf::Vector2f(xLineLength, LINE_THICKNESS));
                line1.setOrigin(line1.getSize() / 2.f);
                line1.setPosition(cellCenter);
                line1.setRotation(sf::degrees(45.f));
                line1.setFillColor(sf::Color::Cyan);
                window.draw(line1);

                sf::RectangleShape line2;
                line2.setSize(sf::Vector2f(xLineLength, LINE_THICKNESS));
                line2.setOrigin(line2.getSize() / 2.f);
                line2.setPosition(cellCenter);
                line2.setRotation(sf::degrees(-45.f));
                line2.setFillColor(sf::Color::Cyan);
                window.draw(line2);

            } else if (value == 1) { // Draw O
                sf::CircleShape circle;
                float radius = (std::min(cellWidth, cellHeight) - 2 * padding) / 2.0f;
                circle.setRadius(radius);
                circle.setOrigin(sf::Vector2f(radius, radius));
                circle.setPosition(cellCenter);
                circle.setFillColor(sf::Color::Transparent);
                circle.setOutlineThickness(LINE_THICKNESS + 1.0f);
                circle.setOutlineColor(sf::Color::Magenta);
                window.draw(circle);
            }
        }
    }
}

int Game::checkWin() {
    for (int i = 0; i < 3; ++i) {
        if (boardStatus[i][0] != -1 && boardStatus[i][0] == boardStatus[i][1] && boardStatus[i][0] == boardStatus[i][2]) {
            return boardStatus[i][0];
        }
        if (boardStatus[0][i] != -1 && boardStatus[0][i] == boardStatus[1][i] && boardStatus[0][i] == boardStatus[2][i]) {
            return boardStatus[0][i];
        }
    }

    if (boardStatus[0][0] != -1 && boardStatus[0][0] == boardStatus[1][1] && boardStatus[0][0] == boardStatus[2][2]) {
        return boardStatus[0][0];
    }
    if (boardStatus[0][2] != -1 && boardStatus[0][2] == boardStatus[1][1] && boardStatus[0][2] == boardStatus[2][0]) {
        return boardStatus[0][2];
    }

    bool isDraw = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (boardStatus[i][j] == -1) {
                isDraw = false;
                break;
            }
        }
        if (!isDraw) break;
    }
    if (isDraw) return 2;

    return -1;
}

void Game::resetBoard() {
    for (auto& row : boardStatus) {
        for (auto& cell : row) {
            cell = -1;
        }
    }
}

void Game::checkAndSetWinText() {
    if (gameOver) return;
    int whoWon = checkWin();
    if (whoWon != -1) {
        gameOver = true;
        gameState = GameState::GameOver;
        if (whoWon == 0) {
            winText.setString("X Won");
            winText.setFillColor(sf::Color::Cyan);
        } else if (whoWon == 1) {
            winText.setString("O Won");
            winText.setFillColor(sf::Color::Magenta);
        } else if (whoWon == 2) {
            winText.setString("Draw");
            winText.setFillColor(sf::Color(128, 128, 128));
        }
    }
}

sf::RectangleShape Game::createVerticalLine(float xPosition) {
    sf::RectangleShape line;
    line.setSize(sf::Vector2f(LINE_THICKNESS, static_cast<float>(SCREENHEIGHT)));
    line.setPosition(sf::Vector2f(xPosition - LINE_THICKNESS / 2.f, 0.f));
    line.setFillColor(sf::Color::White);
    return line;
}

sf::RectangleShape Game::createHorizontalLine(float yPosition) {
    sf::RectangleShape line;
    line.setSize(sf::Vector2f(static_cast<float>(SCREENWIDTH), LINE_THICKNESS));
    line.setPosition(sf::Vector2f(0.f, yPosition - LINE_THICKNESS / 2.f));
    line.setFillColor(sf::Color::White);
    return line;
}

int Game::detectZone(bool isWidth, int currentPos) {
    int zone = -1;
    if(isWidth) {
        if (currentPos < SCREENWIDTH / 3.0f) zone = 0;
        else if (currentPos < 2.0f * SCREENWIDTH / 3.0f) zone = 1;
        else zone = 2;
    } else {
        if (currentPos < SCREENHEIGHT / 3.0f) zone = 0;
        else if (currentPos < 2.0f * SCREENHEIGHT / 3.0f) zone = 1;
        else zone = 2;
    }
    return zone;
}

void Game::processMainMenuEvents(const std::optional<sf::Event>& event) {
    if (!event) return;

    if (event->is<sf::Event::MouseButtonPressed>()) {
        if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>()) {
            sf::Vector2f mousePos(static_cast<float>(mouseClick->position.x), static_cast<float>(mouseClick->position.y));
            if (twoPlayerButton.getGlobalBounds().contains(mousePos)) {
                gameMode = GameMode::TwoPlayer;
                gameState = GameState::Playing;
            } else if (vsAiButton.getGlobalBounds().contains(mousePos)) {
                gameState = GameState::DifficultyMenu;
            }
        }
    }
}

void Game::processDifficultyMenuEvents(const std::optional<sf::Event>& event) {
    if (!event) return;

    if (event->is<sf::Event::MouseButtonPressed>()) {
        if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>()) {
            sf::Vector2f mousePos(static_cast<float>(mouseClick->position.x), static_cast<float>(mouseClick->position.y));
            std::string difficulty = "";

            if (easyButton.getGlobalBounds().contains(mousePos)) {
                difficulty = "easy";
            } else if (mediumButton.getGlobalBounds().contains(mousePos)) {
                difficulty = "medium";
            } else if (hardButton.getGlobalBounds().contains(mousePos)) {
                difficulty = "hard";
            }

            if (!difficulty.empty()) {
                gameMode = GameMode::VsAI;
                aiPlayer = std::make_unique<AI>(1, 0, difficulty, this);
                gameState = GameState::Playing;
            }
        }
    }
}

void Game::processPlayingEvents(const std::optional<sf::Event>& event) {
    if (gameOver || !event) return;

    bool isPlayerTurn = (gameMode == GameMode::TwoPlayer) || (gameMode == GameMode::VsAI && turn % 2 == 0);

    if (isPlayerTurn && event->is<sf::Event::MouseButtonPressed>()) {
        if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>()) {
            int col = detectZone(true, mouseClick->position.x);
            int row = detectZone(false, mouseClick->position.y);

            if (row >= 0 && row < 3 && col >= 0 && col < 3 && boardStatus[row][col] == -1) {
                placeXorO(row, col);
                checkAndSetWinText();
            }
        }
    }
}

void Game::renderMainMenu() {
    window.draw(titleText);
    window.draw(twoPlayerButton);
    window.draw(vsAiButton);
}

void Game::renderDifficultyMenu() {
    window.draw(easyButton);
    window.draw(mediumButton);
    window.draw(hardButton);
}

void Game::renderPlaying() {
    for (const auto& line : gridLines) {
        window.draw(line);
    }
    drawBoardElements();
    if (gameOver) {
        sf::FloatRect textRect = winText.getLocalBounds();
        winText.setOrigin(textRect.position + textRect.size / 2.f);
        winText.setPosition(static_cast<sf::Vector2f>(window.getSize()) / 2.f);

        sf::FloatRect instRect = instructionText.getLocalBounds();
        instructionText.setOrigin(instRect.position + instRect.size / 2.f);
        instructionText.setPosition(winText.getPosition() + sf::Vector2f(0.f, 60.f));

        window.draw(winText);
        window.draw(instructionText);
    }
}
