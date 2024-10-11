#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maze_generator.h"

#define NUM_DIRECTIONS 4

Direction *shuffle_dirs() {
    static Direction dirs[] = {N, S, E, W};
    for (int i = 0; i < NUM_DIRECTIONS; i++) {
        int rand_index = rand() % NUM_DIRECTIONS;
        Direction temp = dirs[i];
        dirs[i] = dirs[rand_index];
        dirs[rand_index] = temp;
    }
    return dirs;
}

bool is_between(int v, int upper) {
    return (v >= 0) && (v < upper);
}

void generate_maze(MazeGenerator *mg, int cx, int cy) {
    Direction *dirs = shuffle_dirs();
    int x = mg->coordinates.x;
    int y = mg->coordinates.y;

    for (int i = 0; i < NUM_DIRECTIONS; i++) {
        int nx = cx, ny = cy;
        switch (dirs[i]) {
            case N: nx = cx; ny = cy - 1; break;
            case S: nx = cx; ny = cy + 1; break;
            case E: nx = cx + 1; ny = cy; break;
            case W: nx = cx - 1; ny = cy; break;
        }

        if (is_between(nx, x) && is_between(ny, y) && mg->maze[nx][ny] == 0) {
            mg->maze[cx][cy] |= dirs[i];
            mg->maze[nx][ny] |= (dirs[i] == N ? S : dirs[i] == S ? N : dirs[i] == E ? W : E);
            generate_maze(mg, nx, ny);
        }
    }
}

void maze_init(Maze *maze, Coordinates coordinates) {
    maze->base.coordinates = coordinates;
    int x = coordinates.x;
    int y = coordinates.y;

    maze->base.maze = (int **)malloc(x * sizeof(int *));
    if (maze->base.maze == NULL) {
        perror("Failed to allocate memory for maze");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < x; i++) {
        maze->base.maze[i] = (int *)calloc(y, sizeof(int));
        if (maze->base.maze[i] == NULL) {
            perror("Failed to allocate memory for maze row");
            exit(EXIT_FAILURE);
        }
    }

    srand(time(NULL));
    generate_maze(&maze->base, 0, 0);
}

void maze_free(Maze *maze) {
    for (int i = 0; i < maze->base.coordinates.x; i++) {
        free(maze->base.maze[i]);
    }
    free(maze->base.maze);
}

void display_maze(Maze *maze) {
    int x = maze->base.coordinates.x;
    int y = maze->base.coordinates.y;

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            printf((maze->base.maze[j][i] & N) ? "+   " : "+---");
        }
        printf("+\n");

        for (int j = 0; j < x; j++) {
            printf((maze->base.maze[j][i] & W) ? "    " : "|   ");
        }
        printf("|\n");
    }

    for (int j = 0; j < x; j++) {
        printf("+---");
    }
    printf("+\n");
}
