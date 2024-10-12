#include "./unity/src/unity.h"
#include "maze_generator.h"
#include <stdlib.h>

Maze maze;
Coordinates coords;

void setUp(void) {
    coords.x = 4;  
    coords.y = 4;
    maze.base.coordinates = coords;
    
    maze.base.maze = (int **)malloc(coords.x * sizeof(int *));
    for (int i = 0; i < coords.x; i++) {
        maze.base.maze[i] = (int *)calloc(coords.y, sizeof(int));
    }
}

void tearDown(void) {
    maze_free(&maze);
}

void test_maze_init(void) {
    for (int i = 0; i < coords.x; i++) {
        for (int j = 0; j < coords.y; j++) {
            TEST_ASSERT_EQUAL_INT(0, maze.base.maze[i][j]);
        }
    }
}


void test_maze_linked_cells(void) {
    for (int i = 0; i < coords.x; i++) {
        for (int j = 0; j < coords.y; j++) {
            if (maze.base.maze[i][j] & N && j > 0) {
                TEST_ASSERT_TRUE(maze.base.maze[i][j - 1] & S);
            }
            if (maze.base.maze[i][j] & S && j < coords.y - 1) {
                TEST_ASSERT_TRUE(maze.base.maze[i][j + 1] & N);
            }
            if (maze.base.maze[i][j] & E && i < coords.x - 1) {
                TEST_ASSERT_TRUE(maze.base.maze[i + 1][j] & W);
            }
            if (maze.base.maze[i][j] & W && i > 0) {
                TEST_ASSERT_TRUE(maze.base.maze[i - 1][j] & E);
            }
        }
    }
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_maze_init);
    RUN_TEST(test_maze_linked_cells);

    return UNITY_END();
}
