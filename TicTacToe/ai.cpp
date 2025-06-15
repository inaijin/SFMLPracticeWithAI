#include <limits>
#include <vector>
#include <cstdlib>
#include <algorithm>

#include "ai.h"
#include "game.h"

using Board = std::vector<std::vector<int>>;

AI::AI(int aiSymbol, int playerSymbol, std::string difficulty, Game* gameInstance)
    : aiSymbol(aiSymbol), playerSymbol(playerSymbol), difficulty(difficulty), gameInstance(gameInstance) {}

void AI::setDifficulty(const std::string newDifficulty) {
    difficulty = newDifficulty;
}

std::pair<int, int> AI::getMove(Board& board) {
    if (difficulty == "easy") {
        return getRandomMove(board);
    } else if (difficulty == "medium") {
        if (rand() % 2 == 0) {
            return getRandomMove(board);
        } else {
            return getBestMove(board, 5);
        }
    } else if (difficulty == "hard") {
        return getBestMove(board, 10);
    }
    return {-1, -1};
}

std::pair<int, int> AI::getRandomMove(Board& board) {
    std::vector<std::pair<int, int>> availableMoves;
    for (size_t i = 0; i < board.size(); ++i) {
        for (size_t j = 0; j < board[i].size(); ++j) {
            if (board[i][j] == -1) {
                availableMoves.push_back({static_cast<int>(i), static_cast<int>(j)});
            }
        }
    }

    if (!availableMoves.empty()) {
        return availableMoves[rand() % availableMoves.size()];
    }

    return {-1, -1};
}

std::pair<int, int> AI::getBestMove(Board& board, int depth) {
    int bestScore = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = {-1, -1};

    for (size_t i = 0; i < board.size(); ++i) {
        for (size_t j = 0; j < board[i].size(); ++j) {
            if (board[i][j] == -1) {
                board[i][j] = aiSymbol;
                int score = minimax(board, depth - 1, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), false);
                board[i][j] = -1;

                if (score > bestScore) {
                    bestScore = score;
                    bestMove = {static_cast<int>(i), static_cast<int>(j)};
                }
            }
        }
    }
    if (bestMove.first == -1) {
        return getRandomMove(board);
    }
    return bestMove;
}

int AI::minimax(Board& board, int depth, int alpha, int beta, bool isMaximizing) {
    int result = gameInstance->checkWin();
    if (result != -1) {
        if (result == aiSymbol) return 10 + depth;
        if (result == playerSymbol) return -10 - depth;
        if (result == 2) return 0;
    }

    if (depth == 0 || isBoardFull(board)) {
        return 0;
    }

    if (isMaximizing) {
        int bestScore = std::numeric_limits<int>::min();
        for (size_t i = 0; i < board.size(); ++i) {
            for (size_t j = 0; j < board[i].size(); ++j) {
                if (board[i][j] == -1) {
                    board[i][j] = aiSymbol;
                    int score = minimax(board, depth - 1, alpha, beta, false);
                    board[i][j] = -1;
                    bestScore = std::max(bestScore, score);
                    alpha = std::max(alpha, bestScore);
                    if (beta <= alpha) {
                        return bestScore;
                    }
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = std::numeric_limits<int>::max();
        for (size_t i = 0; i < board.size(); ++i) {
            for (size_t j = 0; j < board[i].size(); ++j) {
                if (board[i][j] == -1) {
                    board[i][j] = playerSymbol;
                    int score = minimax(board, depth - 1, alpha, beta, true);
                    board[i][j] = -1;
                    bestScore = std::min(bestScore, score);
                    beta = std::min(beta, bestScore);
                    if (beta <= alpha) {
                        return bestScore;
                    }
                }
            }
        }
        return bestScore;
    }
}

bool AI::isBoardFull(const Board& board) {
    for (const auto& row : board) {
        for (int cell : row) {
            if (cell == -1) return false;
        }
    }
    return true;
}
