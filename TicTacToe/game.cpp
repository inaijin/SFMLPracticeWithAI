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
    winText(font, "", 50),
    instructionText(font, "Click to play again", 30)
{
    window.setFramerateLimit(60);

    instructionText.setFillColor(sf::Color::White);

    turn = 0;
    gameOver = false;
    initVectorStatus();

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

void Game::processEvents() {
    while (auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        } else if (event->is<sf::Event::MouseButtonPressed>()) {
            if (gameOver) {
                resetBoard();
                turn = 0;
                gameOver = false;
                winText.setString("");
            } else {
                auto mouseClick = event->getIf<sf::Event::MouseButtonPressed>();
                if (mouseClick) {
                    int col = detectZone(true, mouseClick->position.x);
                    int row = detectZone(false, mouseClick->position.y);

                    if (row >= 0 && row < 3 && col >= 0 && col < 3 && boardStatus[row][col] == -1) {
                        placeXorO(row, col);
                        checkAndSetWinText();
                    }
                }
            }
        }
    }
}

void Game::update() {
    // Game logic updates used for ai later
}

void Game::render() {
    window.clear(sf::Color::Black);

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
    if (whoWon == 0) {
        winText.setString("X Won");
        winText.setFillColor(sf::Color::Cyan);
        gameOver = true;
    } else if (whoWon == 1) {
        winText.setString("O Won");
        winText.setFillColor(sf::Color::Magenta);
        gameOver = true;
    } else if (whoWon == 2) {
        winText.setString("Draw");
        winText.setFillColor(sf::Color(128, 128, 128));
        gameOver = true;
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
