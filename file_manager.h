#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "artifacts.h"

void save_maze_data_to_file(Maze *maze, const char *filename);
void load_maze_data_from_file(Maze *maze, const char *filename);

#endif
