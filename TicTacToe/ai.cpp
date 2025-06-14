#include <limits>
#include <cstdlib>
#include <algorithm>

#include "ai.h"

AI::AI(int aiSymbol, int playerSymbol, std::string difficulty, Game* gameInstance)
    : aiSymbol(aiSymbol), playerSymbol(playerSymbol), difficulty(difficulty), gameInstance(gameInstance) {}

void AI::setDifficulty(std::string newDifficulty) {
    difficulty = newDifficulty;
}

std::pair<int, int> AI::getMove(Board board) {
    if (difficulty == "easy") {
        return getRandomMove(board);
    } else if (difficulty == "medium") {
        return getMediumMove(board);
    } else if (difficulty == "hard") {
        return getBestMove(board);
    }
    return {-1, -1};
}

std::pair<int, int> AI::getRandomMove(Board board) {
    std::vector<std::pair<int, int>> availableMoves;
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            if (board[i][j] == -1) {
                availableMoves.push_back({i, j});
            }
        }
    }

    if (!availableMoves.empty()) {
        return availableMoves[rand() % availableMoves.size()];
    }

    return {-1, -1};
}

std::pair<int, int> AI::getMediumMove(Board board) {
    if (rand() % 2 == 0) {
        return getRandomMove(board);
    } else {
        return getBestMove(board, 2);
    }
}

std::pair<int, int> AI::getBestMove(Board board, int depth) {
    int bestScore = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            if (board[i][j] == -1) {
                board[i][j] = aiSymbol;
                int score = minimax(board, depth, false);
                board[i][j] = -1;

                if (score > bestScore) {
                    bestScore = score;
                    bestMove = {i, j};
                }
            }
        }
    }
    return bestMove;
}

int AI::minimax(Board board, int depth, bool isMaximizing) {
    int result = gameInstance->checkWin();
    if (result == aiSymbol) return 10;
    if (result == playerSymbol) return -10;
    if (result == 2) return 0;

    if (depth == 0) return 0;

    int bestScore = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();

    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            if (board[i][j] == -1) {
                board[i][j] = isMaximizing ? aiSymbol : playerSymbol;
                int score = minimax(board, depth - 1, !isMaximizing);
                board[i][j] = -1;

                bestScore = isMaximizing ? std::max(bestScore, score) : std::min(bestScore, score);
            }
        }
    }
    return bestScore;
}

bool AI::isBoardFull(Board board) {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            if (cell == -1) return false;
        }
    }
    return true;
}
