#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H

#include <stdbool.h>
#include "artifacts.h"

void maze_init(Maze *maze, Coordinates coordinates);
void maze_free(Maze *maze);
void generate_maze(MazeGenerator *mg, int cx, int cy);
void display_maze(Maze *maze);
bool is_between(int v, int upper);
Direction *shuffle_dirs();

#endif
