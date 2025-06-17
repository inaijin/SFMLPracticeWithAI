#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>

#include "Tile.h"

// Screen dimensions
const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 1200;
const int framePS = 120;

// Game Objets Diemnsions
const std::vector<float> ghost_diemensions = {30, 30};
const std::vector<float> pacman_diemensions = {30, 30};
const std::vector<float> tile_diemensions = {30, 30};

const float TILE_SIZE = 30.0f;

#endif // CONSTANTS_H