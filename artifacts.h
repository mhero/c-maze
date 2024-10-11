#ifndef ARTIFACTS_H
#define ARTIFACTS_H

#include <stdbool.h>

typedef struct {
    int x, y;
} Coordinates;

typedef struct {
    Coordinates coordinates;
    int **maze;
} MazeGenerator;

typedef struct {
    MazeGenerator base;
} Maze;

typedef enum {
    N = 1, S = 2, E = 4, W = 8
} Direction;

#endif