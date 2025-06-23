#include <optional>
#include <iostream>

#include "Map.h"
#include "Game.h"
#include "Tile.h"
#include "Constants.h"

const std::vector<std::pair<int, int>> ghost_initial_positions = {
        {245, 444},   // Blinky
        {1333, 444},  // Pinky
        {245, 555},    // Inky
        {1333, 555}   // Clyde
};

Game::Game()
: window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "Pacman"),
pacman(pacman_diemensions, {800, 800}), train_button(font), play_button(font) {
    if(!font.openFromFile("../TicTacToe/fonts/arial.ttf"))
        std::cout << "Error loading font!" << std::endl;

    current_state = GameState::MainMenu;

    train_button.setFont(font);
    train_button.setString("Train AI");
    train_button.setCharacterSize(50);
    train_button.setPosition({SCREEN_WIDTH / 2.f - 150.f, SCREEN_HEIGHT / 2.f - 100.f});

    play_button.setFont(font);
    play_button.setString("Play Game");
    play_button.setCharacterSize(50);
    play_button.setPosition({SCREEN_WIDTH / 2.f - 150.f, SCREEN_HEIGHT / 2.f + 50.f});

    resetGame();
    window.setFramerateLimit(framePS);
    loadMap();
    ghosts.push_back(new Blinky(ghost_diemensions, {245, 444}, sf::Color::Red));
    ghosts.push_back(new Pinky(ghost_diemensions, {1333, 444}, sf::Color::Magenta));
    ghosts.push_back(new Inky(ghost_diemensions, {245, 555}, sf::Color::Cyan));
    ghosts.push_back(new Clyde(ghost_diemensions, {1333, 555}, sf::Color(255, 165, 0)));
}

Game::~Game() {
    if (training_session_ran) {
        std::cout << "Training session ended. Saving AI tables..." << std::endl;
        saveAITables();
    }
    map.clear();
}

void Game::run() {
    while (window.isOpen()) {
        switch(current_state) {
            case GameState::MainMenu:
                runMainMenu();
                break;
            case GameState::Training:
            case GameState::Play:
                runGameSession();
                break;
        }
    }
}

void Game::runGameSession() {
    while (window.isOpen()) {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                if (current_state == GameState::Training) {
                    saveAITables();
                }
                window.close();
                return; 
            }

            if (event->is<sf::Event::KeyPressed>()) {
                if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::F) {
                    fast_forward_mode = !fast_forward_mode;

                    if (fast_forward_mode) {
                        window.setFramerateLimit(0);
                        std::cout << "Fast-Forward Mode: ON" << std::endl;
                    } else {
                        window.setFramerateLimit(framePS);
                        std::cout << "Fast-Forward Mode: OFF" << std::endl;
                    }
                }
            }
        }

        // --- Update game logic here ---
        if(pacman.updatePacman(ghosts, &map))
            resetGame();

        Blinky* blinky_ptr = static_cast<Blinky*>(ghosts[0]);

        for (auto& ghost : ghosts)
            ghost->updateGhostState(pacman, blinky_ptr, &map);

        // --- Draw game elements here if not fast forward---
        if(!fast_forward_mode) {
            window.clear(sf::Color::Black);

            for (auto& row : map) {
                for (auto& tile : row)
                    tile.draw(window);
            }

            pacman.draw(window);
            for (auto& ghost : ghosts)
                ghost->draw(window);

            window.display();
        }
    }
}

void Game::runMainMenu()
{
    while (true)
    {
        auto optEvent = window.pollEvent();
        if (!optEvent) break;
        const auto &event = *optEvent;

        if (event.is<sf::Event::Closed>())
            window.close();

        else if (event.is<sf::Event::MouseButtonPressed>())
        {
            auto mb = event.getIf<sf::Event::MouseButtonPressed>();
            sf::Vector2f mousePos = window.mapPixelToCoords({ mb->position.x, mb->position.y });

            if (train_button.getGlobalBounds().contains(mousePos))
            {
                pacman.setTrainingMode(true);
                training_session_ran = true;
                loadAITables();
                current_state = GameState::Training;
                resetGame();
            }
            else if (play_button.getGlobalBounds().contains(mousePos))
            {
                pacman.setTrainingMode(false);
                training_session_ran = false;
                loadAITables();
                current_state = GameState::Play;
                resetGame();
            }
        }
    }

    window.clear(sf::Color::Black);
    window.draw(train_button);
    window.draw(play_button);
    window.display();
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
        }
    }
}

void Game::saveAITables() {
    pacman.getAI()->get()->saveQTable("weights/pacman_q_table.txt");
    ghosts[0]->getAI()->get()->saveQTable("weights/blinky_q_table.txt");
    ghosts[1]->getAI()->get()->saveQTable("weights/pinky_q_table.txt");
    ghosts[2]->getAI()->get()->saveQTable("weights/inky_q_table.txt");
    ghosts[3]->getAI()->get()->saveQTable("weights/clyde_q_table.txt");
}

void Game::loadAITables() {
    pacman.getAI()->get()->loadQTable("weights/pacman_q_table.txt");
    ghosts[0]->getAI()->get()->loadQTable("weights/blinky_q_table.txt");
    ghosts[1]->getAI()->get()->loadQTable("weights/pinky_q_table.txt");
    ghosts[2]->getAI()->get()->loadQTable("weights/inky_q_table.txt");
    ghosts[3]->getAI()->get()->loadQTable("weights/clyde_q_table.txt");
}

void Game::resetGame() {
    pacman.reset();

    for (size_t i = 0; i < ghosts.size(); ++i) {
        if (i < ghost_initial_positions.size()) {
            ghosts[i]->setPosition(sf::Vector2f(static_cast<float>(ghost_initial_positions[i].first),
                                                static_cast<float>(ghost_initial_positions[i].second)));
        }
    }

    loadMap();
}

void GameObject::reset() {}
