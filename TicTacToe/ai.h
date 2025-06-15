#ifndef AI_H
#define AI_H

#include <vector>
#include <string>
#include <utility>

#include "game.h"

class Game;

typedef std::vector<std::vector<int>> Board;

class AI {
private:
    int aiSymbol;
    int playerSymbol;
    std::string difficulty;
    Game* gameInstance;

public:
    AI(int aiSymbol, int playerSymbol, std::string difficulty, Game* gameInstance);

    void setDifficulty(std::string newDifficulty);
    std::pair<int, int> getMove(Board& board);

private:
    std::pair<int, int> getRandomMove(Board& board);
    std::pair<int, int> getBestMove(Board& board, int depth = std::numeric_limits<int>::max());

    int minimax(Board& board, int depth, int alpha, int beta, bool isMaximizing);

    bool isBoardFull(const Board& board);
};

#endif // AI_H