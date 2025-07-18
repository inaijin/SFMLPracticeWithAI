#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>

#include "Tile.h"

const char WALL_CHAR = '#';
const char EMPTY_CHAR = '.';
const char POWER_PELLET_CHAR = 'P';

const std::vector<std::string> MAP_LAYOUT_STRINGS = {
    "######################################################",
    "######################################################",
    "##..................................................##",
    "##..#########...########..##..#########..#######....##",
    "##..#########...########..##..#########..#######....##",
    "##..................................................##",
    "##..####..##..############..############..##..####..##",
    "##..####..##..############..############..##..####..##",
    "##........##..............................##........##",
    "######..######..##########..##########..######..######",
    "######..######..##########..##########..######..######",
    "##..................................................##",
    "##..##########..##..................##..##########..##",
    "##..##########..##..##############..##..##########..##",
    "##..............##..##############..##..............##",
    "##..............##..................##..............##",
    "##..##########..##..##############..##..##########..##",
    "##..##########..##..##############..##..##########..##",
    "##..............##..................##..............##",
    "##..............##..##############..##..............##",
    "##..##########..##..##############..##..##########..##",
    "##..##########..##..................##..##########..##",
    "##..................................................##",
    "######..######..##########..##########..######..######",
    "######..######..##########..##########..######..######",
    "##........##..............................##........##",
    "##..####..##..############..############..##..####..##",
    "##..####..##..############..############..##..####..##",
    "##..................................................##",
    "##..#########...########..##..#########..########...##",
    "##..#########...########..##..#########..########...##",
    "##..................................................##",
    "##...........P..........................P...........##",
    "######################################################",
};

std::vector<std::vector<TileType>> createTileMapFromStrings();

#endif // MAP_H