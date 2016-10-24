//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

#include <vector>
#include <stdint.h>

#define MAP_WIDTH 61
#define MAP_HEIGHT 61

// A simple structure to hold ordered pairs
struct aStrCoordinate {
    int x, y;
    float f, g;
};

// Define a class for a node
std::vector<aStrCoordinate> astar_path(aStrCoordinate&, aStrCoordinate&, uint8_t map[MAP_WIDTH][MAP_HEIGHT]);

bool contains(std::vector<aStrCoordinate>&, aStrCoordinate&);

std::vector<aStrCoordinate> getAdjacent(aStrCoordinate&, aStrCoordinate&, uint8_t map[MAP_WIDTH][MAP_HEIGHT]);

float heuristic(int, int, int, int);
